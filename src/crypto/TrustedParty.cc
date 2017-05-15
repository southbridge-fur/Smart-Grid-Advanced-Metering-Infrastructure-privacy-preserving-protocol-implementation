#include "TrustedParty.h"
#include "UtilityCompany.h"
#include "../TTPAdapter.h"

#define DEBUG(x,y) if (verbose) out->print(x,y)

namespace SMImp {
    
TrustedParty::TrustedParty(Integer i,TTPAdapter* o) : Requester(i)
{
    out = o;
    init();
    verbose = true;
}

TrustedParty::TrustedParty(Integer i) : Requester(i)
{
    out = NULL;
    init();
    verbose = false;
}
    
TrustedParty::~TrustedParty()
{
    delete SMList;
}

void TrustedParty::init()
{
    message = NULL;
    messageBytesRecieved = 0;
    SMList = new List<List<Integer> >();
}
    
void TrustedParty::registerSM(int id)
{
    List<Integer>* list = new List<Integer>();

    list->add(new Integer(id),0);
    
    SMList->add(list,id);
}

char* getMessage()
{
    return message;
}
    
void TrustedParty::addDataToSM(int id, Integer* data)
{
    List<Integer>* l = SMList->get(id);
    l->add(data,l->size());
}

List<Integer>* TrustedParty::getSM(int id)
{
    return SMList->get(id);
}

List<Integer>* TrustedParty::getRandomSM()
{
    return SMList->getRandom();
}

Iterator<List<Integer> >* TrustedParty::getSMIterator()
{
    return SMList->iterator();
}
    
Packet TrustedParty::confirmSession(Integer req, Integer smId, Key smKey)
{  
    List<Integer>* sm = SMList->get(smId.ConvertToLong());
    /*
    DEBUG("smId",&smId);
    DEBUG("partial",&smKey.partial);
    DEBUG("piece",&smKey.piece);
    */
    sm->add(new Integer(req),3); //set private variable R

    SHA256* sha256 = new SHA256();
    int digestSize = sha256->DigestSize();

    Integer hOne = concatAndHash(shaone, smId, smKey.partial); 

    Integer gamma = ModularExponentiation(params.x,hOne,params.p);
    gamma = (gamma * smKey.partial) % params.p;
    
    byte* sigmaBytes = new byte[digestSize-req.ByteCount()];
    rng->GenerateBlock(sigmaBytes,digestSize-req.ByteCount());

    Integer sigma = *(new Integer(sigmaBytes, digestSize-req.ByteCount()));

    Integer subMessage = Integer(req);

    HMACPayload payload;

    Integer r = concatAndHash(sha256,subMessage, sigma);
    payload.c1 = ModularExponentiation(params.g,r,params.p);
	
    Integer muR = ModularExponentiation(smKey.piece, r, params.p);
    Integer gammaR = ModularExponentiation(gamma, r, params.p);

    Integer hThree = concatAndHash(sha256, muR, gammaR);

    payload.c2 = 0;

    for (int j=0;j<subMessage.ByteCount()*8;j++)
    {
	payload.c2.SetBit(j,subMessage.GetBit(j) != hThree.GetBit(j));
    }
	
    for (int j=0;j<sigma.ByteCount()*8;j++)
    {
	payload.c2.SetBit(j+subMessage.ByteCount()*8,sigma.GetBit(j) != hThree.GetBit(j+subMessage.ByteCount()*8));
    }

    //Now we have c1 and c2, time to run HMAC

    Integer timeStamp = time(new time_t()); //epoch
    payload.id = id;
    payload.timeStamp = timeStamp;
    payload.hmac = generateHMAC(smId,payload);

    Packet packet;
    packet.dest = smId;
    packet.pl = payload;
    return packet;
}


Integer TrustedParty::recieveData(Integer length, Integer c1, Integer c2, Integer smId, Integer timeStamp)
{
    List<Integer>* sm = SMList->get(smId.ConvertToLong());

    Integer sessionKey = *sm->get(3);

    SHA256* sha256 = new SHA256();
    int digestSize = sha256->DigestSize();

//    start = std::chrono::high_resolution_clock::now();
//    std::cout << "TTP_decrypt_session_key ";
    
    //time to decrypt
    DEBUG("sessionKey",&sessionKey);
    DEBUG("timeStamp",&timeStamp);
    
    Integer left = ModularExponentiation(c1,sessionKey,params.p);
    Integer right = ModularExponentiation(c1,timeStamp,params.p);

    Integer temp = concatAndHash(sha256, left, right);

    Integer mi = 0;
    
    for (int j=0;j<c2.ByteCount()*8;j++)
    {
	mi.SetBit(j,temp.GetBit(j) != c2.GetBit(j));
    }

    DEBUG("c2",&c2);
    DEBUG("mi",&mi);
    
    Integer subMessage = 0;
    for (int i=0;i<mi.ByteCount();i++)
    {
	subMessage.SetByte(i,mi.GetByte(i));
    }
    
    Integer hTwo = hashInteger(sha256,mi);
    
    hTwo = ModularExponentiation(params.g, hTwo, params.p);

    if (c1.Compare(hTwo) == 0)
    {
	return subMessage;
    }
    
    return -1;
}

bool TrustedParty::recieveHMAC(Integer length, Integer c1, Integer c2, Integer smId, Key smKey, Integer r)
{
    SHA256* sha256 = new SHA256();
    int digestSize = sha256->DigestSize();

    List<Integer>* sm = SMList->get(smId.ConvertToLong());

    Integer* mes = sm->get(1);

    if (mes == NULL || mes->ByteCount() >= length)
    {
	if (mes != NULL) delete mes;
	mes = new Integer();
	sm->add(mes,1);
    }
    
//    start = std::chrono::high_resolution_clock::now();
//    std::cout << "TTP_decrypt_session_key ";
    
    //time to decrypt
    Integer left = ModularExponentiation(c1,keys.priv.piece,params.p);
    Integer right = ModularExponentiation(c1,keys.priv.partial,params.p);

    Integer temp = concatAndHash(sha256, left, right);
    
    Integer mi = 0;
    
    for (int j=0;j<c2.ByteCount()*8;j++)
    {
	mi.SetBit(j,temp.GetBit(j) != c2.GetBit(j));
    }

    //DEBUG("mi",&mi);
    
    Integer subMessage = 0;
    for (int i=0;i<4;i++)
    {
	subMessage.SetByte(i,mi.GetByte(i));
    }
    
    //DEBUG("message", &subMessage);

    Integer hTwo = hashInteger(sha256,mi);
    
    hTwo = ModularExponentiation(params.g, hTwo, params.p);
    //std::cout << c1 << "\n" << hTwo << std::endl;
    //c1 should equal hTwo if not then fail
//std::cout << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
/*    
    DEBUG("c1",&c1);
    DEBUG("hTwo",&hTwo);
*/
    if (c1.Compare(hTwo) == 0)
    {
	for (int i=0;i<4;i++) mes->SetByte(mes->ByteCount(),subMessage.GetByte(i));
	if (length <= mes->ByteCount())
	{
	    DEBUG("Session key",mes);
	    sessionKey = mes; 
	    return true;
	}
	//DEBUG("length",&length);
	//DEBUG("messageBytesRecieved",new Integer(mes->ByteCount()));
    }
    return false;
}

};
