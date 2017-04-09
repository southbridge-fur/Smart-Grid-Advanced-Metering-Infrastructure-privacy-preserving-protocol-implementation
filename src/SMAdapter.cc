#include "SMAdapter.h"
#include "SMPacket_m.h"
#include "crypto/SmartMeter.h"
#include "cInteger.h"
#include <stdlib.h>     /* atof */

#include "SmartMeter.h"

#ifndef MKPacket
#include <MKPacket_m.h>
#endif
#ifndef SMPacket
#include <SMPacket_m.h>
#endif

SMAdapter::SMAdapter(long int id) : Adapter()
{
    sm = new SMImp::SmartMeter(CryptoPP::Integer(id));
}

SMAdapter::SMAdapter(long int id, smart3p::Unit* o) : Adapter(o)
{
    sm = new SMImp::SmartMeter(CryptoPP::Integer(id),this);
}

SMAdapter::~SMAdapter()
{
    delete sm;
}

void SMAdapter::addSimTime(double time)
{
    dynamic_cast<smart3p::SmartMeter*>(out)->addSimTime(time);
}

void SMAdapter::log(char* tag, double value)
{
    dynamic_cast<smart3p::SmartMeter*>(out)->log(tag,value);
}

//void smartMeterInit(cMessage *msg);
cInteger* SMAdapter::getAnonId()
{
    return new ::cInteger("anonid", new CryptoPP::Integer(sm->getAnonId()));
}

cInteger* SMAdapter::getId()
{
    return new ::cInteger("id", new CryptoPP::Integer(sm->getId()));
}

void SMAdapter::registerInfoFromUC(omnetpp::cMessage *msg)
{
    //generate keys
    //get hmac, and anon id
    //anonid, SMUCKey, p, q, g, x, priv, pub
    smart3p::SMPacket *p = omnetpp::check_and_cast<smart3p::SMPacket*> (msg->getObject("packet"));
    
    sm->setAnonId(*dynamic_cast<CryptoPP::Integer*> (p->getObject("anonid")));
    sm->setHMACKey(*dynamic_cast<CryptoPP::Integer*> (p->getObject("SMUCKey")));

    SMImp::Payload payload;
    payload.params.p = *dynamic_cast<CryptoPP::Integer*> (p->getObject("p"));
    payload.params.q = *dynamic_cast<CryptoPP::Integer*> (p->getObject("q"));
    payload.params.g = *dynamic_cast<CryptoPP::Integer*> (p->getObject("g"));
    payload.params.x = *dynamic_cast<CryptoPP::Integer*> (p->getObject("x"));
    payload.priv = *dynamic_cast<CryptoPP::Integer*> (p->getObject("priv"));
    payload.pub = *dynamic_cast<CryptoPP::Integer*> (p->getObject("pub"));
    
    if (!sm->generateKeys(payload))
    {
	if (verbose) print("Partial verification failed");
    }
    else
    {
	if (verbose) print("Partial verification succeeded");
    }
}

//void registerAtUC(cMessage *msg); //will need later

omnetpp::cQueue* SMAdapter::startSessionKeyExchange(omnetpp::cMessage *msg)
{
    //get msg, pull out the session key m, it's length, and the trusted third party id, key, and mu
    smart3p::SMPacket* data = dynamic_cast<smart3p::SMPacket*> (msg->getObject("packet"));
    
    //char* message = const_cast<char*>(data->getPBytes());
    //CryptoPP::Integer* m = dynamic_cast<CryptoPP::Integer*> (msg->getObject("message"));
    CryptoPP::Integer* id = new CryptoPP::Integer(data->getId());
    CryptoPP::Integer* key = new CryptoPP::Integer(*dynamic_cast<CryptoPP::Integer*> (data->getObject("partial")));
    CryptoPP::Integer* mu = new CryptoPP::Integer(*dynamic_cast<CryptoPP::Integer*> (data->getObject("mu")));

    //will need to be randomly generated
    byte* message = new byte[8];
    for (int i=0;i<8;i++) message[i] = rand()%256;
    int length = 8;

    SMImp::Packet* payloads = sm->sessionKeyExchange((char*)message,length,*id,*key,*mu);
        
    if (length % 4)
    {
	length = (length + (4-(length%4)));
    }
    
    omnetpp::cQueue* queue = new omnetpp::cQueue("sessionKeyExchange");
    
    for (int i=0; i<length/4; i++)
    {
	SMImp::Packet payload = payloads[i];
	omnetpp::cMessage* m = new omnetpp::cMessage("sessionKeyExchange");
	smart3p::SMPacket* p = new smart3p::SMPacket("packet");
	m->addObject(p);
	
	p->setId(id->ConvertToLong());

	SMImp::HMACPayload hmac = payload.pl;

	//print("hmac",&hmac.hmac);
	
	p->addObject(new ::cInteger("id",new CryptoPP::Integer(sm->getId())));
	p->addObject(new ::cInteger("ttpid", id));
	p->addObject(new ::cInteger("partial", new CryptoPP::Integer(sm->getPublicPartial())));
	p->addObject(new ::cInteger("mu", new CryptoPP::Integer(sm->getPublicMu())));
 	p->addObject(new ::cInteger("messageLength", &hmac.messageLength));
	p->addObject(new ::cInteger("hmac", &hmac.hmac));
	p->addObject(new ::cInteger("c1", &hmac.c1));
	p->addObject(new ::cInteger("c2", &hmac.c2));
	p->addObject(new ::cInteger("timeStamp", &hmac.timeStamp));
	p->addObject(new ::cInteger("r", &hmac.r));

	if (false)
	{
	    int totalBytes =0;
	    omnetpp::cArray items = p->getParList();
	    int size = items.size();
	    
	    for (int j=0; j<size; j++)
	    {
		int byteCount = dynamic_cast<CryptoPP::Integer*>(items[j])->ByteCount();
		totalBytes += byteCount;
		print(const_cast<char*>(items[j]->getName()),new CryptoPP::Integer(byteCount));
	    }
	    
	    print("Total Bytes",new CryptoPP::Integer(totalBytes));
	}

	queue->insert(m);
    }
    
    delete msg;
    
    return queue;
}

bool SMAdapter::endOfSessionKeyExchange(omnetpp::cMessage *msg)
{
    smart3p::SMPacket* data = dynamic_cast<smart3p::SMPacket*> (msg->getObject("packet"));

    CryptoPP::Integer* c1 = new CryptoPP::Integer(*dynamic_cast<CryptoPP::Integer*>(data->getObject("c1")));
    CryptoPP::Integer* c2 = new CryptoPP::Integer(*dynamic_cast<CryptoPP::Integer*>(data->getObject("c2")));
    CryptoPP::Integer* ttpId = new CryptoPP::Integer(*dynamic_cast<CryptoPP::Integer*>(data->getObject("id")));

    return sm->recieveHMAC(*c1,*c2,*ttpId);
}

omnetpp::cMessage* SMAdapter::sendEnergyConsumption(omnetpp::cMessage *msg)
{
    smart3p::SMPacket* pac = dynamic_cast<smart3p::SMPacket*> (msg->getObject("packet"));

    double data = pac->getValue();
    char* buffer = new char[sizeof(double)];
    sprintf(buffer,"%f",data);
    
    CryptoPP::Integer input = 0;
    for (int i=0;i<sizeof(double);i++)
    {
	input.SetByte(i,buffer[i]);
    }
    
    SMImp::Packet* payload = sm->sendDataToTTP(input);
    
    omnetpp::cMessage* m = new omnetpp::cMessage("data-packet");
    smart3p::SMPacket* p = new smart3p::SMPacket("packet");
    m->addObject(p);

    SMImp::HMACPayload hmac = payload->pl;

    p->addObject(new ::cInteger("messageLength", &hmac.messageLength));
    p->addObject(new ::cInteger("id", &hmac.id));
    p->addObject(new ::cInteger("hmac", &hmac.hmac));
    p->addObject(new ::cInteger("c1", &hmac.c1));
    p->addObject(new ::cInteger("c2", &hmac.c2));
    p->addObject(new ::cInteger("timeStamp", &hmac.timeStamp));

    if (verbose)
    {
	int totalBytes =0;
	omnetpp::cArray items = p->getParList();
	int size = items.size();

	for (int j=0; j<size; j++)
	{
	    int byteCount = dynamic_cast<CryptoPP::Integer*>(items[j])->ByteCount();
	    totalBytes += byteCount;
	    print(const_cast<char*>(items[j]->getName()),new CryptoPP::Integer(byteCount));
	}
	    
	print("Total Bytes",new CryptoPP::Integer(totalBytes));
    }
    
    return m;
}
