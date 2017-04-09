#include "TTPAdapter.h"
#include "SMPacket_m.h"
#include "crypto/TrustedParty.h"
#include "cInteger.h"
#include <stdlib.h>     /* atof */

#ifndef SMPacket
#include <SMPacket_m.h>
#endif

TTPAdapter::TTPAdapter(int id) : Adapter()
{
    ttp = new SMImp::TrustedParty(CryptoPP::Integer(id));
}

TTPAdapter::TTPAdapter(int id, smart3p::Unit* o) : Adapter(o)
{
    ttp = new SMImp::TrustedParty(CryptoPP::Integer(id),this);
}

TTPAdapter::~TTPAdapter()
{
    delete ttp;
}

omnetpp::cQueue* TTPAdapter::startSessionKeyExchange()
{
    //List<CryptoPP::Integer>* sm = ttp->getRandomSM();

    omnetpp::cQueue* queue = new omnetpp::cQueue();
    Iterator<List<CryptoPP::Integer> >* iter = ttp->getSMIterator();

    while (iter->hasNext())
    {
	//need to include the id of the smart meter we want
	omnetpp::cMessage* msg = new omnetpp::cMessage("sessionKeyStartFromTTP");
	smart3p::SMPacket* p = new smart3p::SMPacket("packet");
	msg->addObject(p);

	List<CryptoPP::Integer>* sm = iter->next();
	
	p->setId(ttp->getId().ConvertToLong());
	p->addObject(new ::cInteger("smid",sm->get(0)));
	p->addObject(new ::cInteger("mu",new CryptoPP::Integer(ttp->getPublicMu())));
	p->addObject(new ::cInteger("partial",new CryptoPP::Integer(ttp->getPublicPartial())));

	queue->insert(msg);
    }
    
    return queue;
}

omnetpp::cMessage* TTPAdapter::finishSessionKeyExchange(omnetpp::cMessage* msg)
{    
    smart3p::SMPacket* p = omnetpp::check_and_cast<smart3p::SMPacket*> (msg->removeObject("packet"));
    
    CryptoPP::Integer req = *dynamic_cast<CryptoPP::Integer*>(p->getObject("r"));
    CryptoPP::Integer id = *dynamic_cast<CryptoPP::Integer*>(p->getObject("id")); //SM id (anon id)

    CryptoPP::Integer partial = *dynamic_cast<CryptoPP::Integer*>(p->getObject("partial"));
    CryptoPP::Integer mu = *dynamic_cast<CryptoPP::Integer*>(p->getObject("mu"));

    SMImp::Key key;
    key.partial = partial;
    key.piece = mu;

    CryptoPP::Integer length = *dynamic_cast<CryptoPP::Integer*>(p->getObject("messageLength"));
    CryptoPP::Integer c1 = *dynamic_cast<CryptoPP::Integer*>(p->getObject("c1"));
    CryptoPP::Integer c2 = *dynamic_cast<CryptoPP::Integer*>(p->getObject("c2"));

    if(!ttp->recieveHMAC(length,c1,c2,id,key,req))
    {
	return NULL;	
    }

    SMImp::Packet output = ttp->confirmSession(req,id,key);

    omnetpp::cMessage* m = new omnetpp::cMessage("sessionKey");
    smart3p::SMPacket* pac = new smart3p::SMPacket("packet");
    m->addObject(pac);

    SMImp::HMACPayload hmac = output.pl;

    pac->addObject(new ::cInteger("id", &hmac.id));
    pac->addObject(new ::cInteger("smId", &id)); 
    pac->addObject(new ::cInteger("hmac", &hmac.hmac));
    pac->addObject(new ::cInteger("c1", &hmac.c1));
    pac->addObject(new ::cInteger("c2", &hmac.c2));
    pac->addObject(new ::cInteger("timeStamp", &hmac.timeStamp));

    pac->addObject(new ::cInteger("messageLength", &length));
    pac->addObject(new ::cInteger("r", &req));
    pac->addObject(new ::cInteger("dest",&output.dest));
    
    return m;
}

void TTPAdapter::registerSM(omnetpp::cMessage *msg)
{
    smart3p::SMPacket* p = omnetpp::check_and_cast<smart3p::SMPacket*> (msg->getObject("packet"));
    ttp->registerSM(p->getId());
}

omnetpp::cMessage* TTPAdapter::registerAtUC()
{
    omnetpp::cMessage* message = new omnetpp::cMessage("registerFromTTP");
    smart3p::SMPacket* p = new smart3p::SMPacket("packet");
    message->addObject(p);
    
    p->setId(ttp->getId().ConvertToLong());
    
    return message;
}
    
void TTPAdapter::registerInfoFromUC(omnetpp::cMessage* msg)
{
    smart3p::SMPacket* p = omnetpp::check_and_cast<smart3p::SMPacket*> (msg->getObject("packet"));
    
    SMImp::Payload payload;
    payload.params.p = *dynamic_cast<CryptoPP::Integer*> (p->getObject("p"));
    payload.params.q = *dynamic_cast<CryptoPP::Integer*> (p->getObject("q"));
    payload.params.g = *dynamic_cast<CryptoPP::Integer*> (p->getObject("g"));
    payload.params.x = *dynamic_cast<CryptoPP::Integer*> (p->getObject("x"));
    payload.priv = *dynamic_cast<CryptoPP::Integer*> (p->getObject("priv"));
    payload.pub = *dynamic_cast<CryptoPP::Integer*> (p->getObject("pub"));
    
    ttp->generateKeys(payload);
}

void TTPAdapter::processDataFromSM(omnetpp::cMessage* msg)
{
    smart3p::SMPacket* p = omnetpp::check_and_cast<smart3p::SMPacket*> (msg->getObject("packet"));

    CryptoPP::Integer length = *dynamic_cast<CryptoPP::Integer*>(p->getObject("messageLength"));
    CryptoPP::Integer c1 = *dynamic_cast<CryptoPP::Integer*>(p->getObject("c1"));
    CryptoPP::Integer c2 = *dynamic_cast<CryptoPP::Integer*>(p->getObject("c2"));
    CryptoPP::Integer smId = *dynamic_cast<CryptoPP::Integer*>(p->getObject("id"));
    CryptoPP::Integer timeStamp = *dynamic_cast<CryptoPP::Integer*>(p->getObject("timeStamp"));
    
    CryptoPP::Integer out = ttp->recieveData(length,c1,c2,smId,timeStamp);
    
    delete msg;
    
    if (!out.Compare(-1))
    {
	if (verbose) print("Failed verifying data");
	return;
    }

    char* buffer = new char[out.ByteCount()];
    for (int i=0;i<out.ByteCount();i++)
    {
	buffer[i] = out.GetByte(i);
    }
    
    double output = atof(buffer);

    sprintf(buffer, "Data from SM#%d: %f", smId.ConvertToLong(),output);

    if (verbose) print(buffer);
}
