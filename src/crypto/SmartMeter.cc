#include "SmartMeter.h"
#include "UtilityCompany.h"
#include "TrustedParty.h"
#include "../SMAdapter.h"

#define DEBUG(x,y) if (verbose) out->print(x,y);

//namespce to help section out both SmartMeter classes
namespace SMImp {

bool SmartMeter::generateKeys(Payload pl)
{
    if (!getPartials(anonId, pl)) return false;

    keys.priv.piece = Integer(*rng,1,params.q);
    keys.pub.piece = ModularExponentiation(params.g, keys.priv.piece, params.p);

    /*
    DEBUG("After partials\nid:",&id);
    DEBUG("anonid",&anonId);
    DEBUG("p",&params.p);
    DEBUG("q",&params.q);
    DEBUG("g",&params.g);
    DEBUG("x",&params.x);
    DEBUG("priv.piece",&keys.priv.piece);
    DEBUG("pub.piece",&keys.pub.piece);
    */
    
    return true;

    //std::cout << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << " " <<  params.q.ByteCount() + params.x.ByteCount() + params.p.ByteCount() + params.g.ByteCount() + keys.priv.partial.ByteCount() + keys.priv.piece.ByteCount() + keys.pub.partial.ByteCount() + keys.pub.piece.ByteCount() << std::endl;
}
 
SmartMeter::SmartMeter(Integer i) : Requester (i)
{
    verbose = false;
}

SmartMeter::SmartMeter(Integer i, SMAdapter* s) : Requester (i)
{
    verbose = true;
    out = s;
}
   
SmartMeter::SmartMeter(Integer i, SHA1* s) : Requester (i, s)
{
}

SmartMeter::~SmartMeter()
{
}
    
Integer SmartMeter::getAnonId()
{
    return anonId;
}

void SmartMeter::setAnonId(Integer a)
{
    anonId = a;
}

void SmartMeter::setHMACKey(Integer i)
{
    hmacKey = i;
    //DEBUG("UCSM-Key",&hmacKey);
}

Packet* SmartMeter::sendDataToTTP(Integer data) //message here is the data which will be sent.
{
    //it is important to note that we assume the data to be transfered has a byte count less than
    //sha256's digest size minus the byte count of the timestamp
    
    SHA256* sha256 = new SHA256();
    int digestSize = sha256->DigestSize(); 

    auto start = std::chrono::high_resolution_clock::now();

    Integer hOne = hashInteger(shaone,sessionKey);

    Integer gamma = ModularExponentiation(params.x,hOne,params.p);
    gamma = (gamma * sessionKey) % params.p;
    
    Integer subMessage = data;
    Integer timeStamp = time(new time_t()); //epoch

    HMACPayload payload;

    Integer r = concatAndHash(sha256,subMessage, timeStamp);
    payload.c1 = ModularExponentiation(params.g,r,params.p);
	
    Integer muR = ModularExponentiation(timeStamp, r, params.p);
    Integer gammaR = ModularExponentiation(gamma, r, params.p);

    Integer hThree = concatAndHash(sha256, muR, gammaR);

    payload.c2 = 0;

    DEBUG("sessionKey",&sessionKey);
    DEBUG("timestamp",&timeStamp);
    
    for (int j=0;j<subMessage.ByteCount()*8;j++)
    {
	payload.c2.SetBit(j,subMessage.GetBit(j) != hThree.GetBit(j));
    }
	
    for (int j=0;j<timeStamp.ByteCount()*8;j++)
    {
	payload.c2.SetBit(j+subMessage.ByteCount()*8,timeStamp.GetBit(j) != hThree.GetBit(j+subMessage.ByteCount()*8));
    }
    
    DEBUG("c2",&payload.c2);
    DEBUG("message", &subMessage);

    payload.id = id;
    payload.timeStamp = timeStamp;
    payload.r = R;
    payload.messageLength = subMessage.ByteCount();
    payload.hmac = generateHMAC(hmacKey,payload);
	
    out->log("dataEncryptionTime",std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count());

    Packet* packet = new Packet;
    packet->pl = payload;
    return packet;
}

Packet* SmartMeter::sessionKeyExchange(char* m, Integer l, Integer trustedPartyId, Integer trustedPartyKey, Integer trustedPartyMu)
{
    SHA256* sha256 = new SHA256();
    int digestSize = sha256->DigestSize();

    R = rng->GenerateWord32(); 
    
    Integer hOne = concatAndHash(shaone, trustedPartyId, trustedPartyKey);

    Integer gamma = ModularExponentiation(params.x,hOne,params.p);
    gamma = (gamma * trustedPartyKey) % params.p;
    
    int length = l.ConvertToLong();
    char* message = m;

    if (l % 4)
    {
	length = l.ConvertToLong() + (4-(l.ConvertToLong()%4)); //add to length what we need to get a multiple of 4
	message = new char[l.ConvertToLong()];    
	for (int i=0;i<length;i++) message[i] = char('0');
	for (int i=0;i<l;i++) message[i] = m[i];
    }

    
    Packet* packets = new Packet[length/4];
    int pos = 0;

    for (int i=0;i<(length/4);i++)
    {
	auto start = std::chrono::high_resolution_clock::now();
	//std::cout << "sm_encrypt_session_key ";

	byte* sigmaBytes = new byte[digestSize-4];
	rng->GenerateBlock(sigmaBytes,digestSize-4);

	Integer sigma = *(new Integer(sigmaBytes, digestSize-4));

	Integer subMessage = 0;

	for (int j=0;j<4;j++) subMessage.SetByte(j,(unsigned char)message[j+(i*4)]);

	HMACPayload payload;

	Integer r = concatAndHash(sha256,subMessage, sigma);
	payload.c1 = ModularExponentiation(params.g,r,params.p);
	
	Integer muR = ModularExponentiation(trustedPartyMu, r, params.p);
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

	// DEBUG("c2",&payload.c2);
	// DEBUG("message", &subMessage);

	Integer timeStamp = time(new time_t()); //epoch
	
	payload.id = id;
	payload.timeStamp = timeStamp;
	payload.r = R;

	payload.hmac = generateHMAC(hmacKey,payload);
	

	payload.messageLength = length;

	out->log("sessionKeyEncryptionTime",std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count());
	
	Packet packet;
	packet.dest = trustedPartyId;
	packet.pl = payload;
	packets[pos++] = packet;
    }

    return packets;
}

bool SmartMeter::recieveHMAC(Integer c1, Integer c2, Integer ttpId)
{
    SHA256* sha256 = new SHA256();
    //time to decrypt

    auto start = std::chrono::high_resolution_clock::now();

    Integer left = ModularExponentiation(c1,keys.priv.piece,params.p);
    Integer right = ModularExponentiation(c1,keys.priv.partial,params.p);

    Integer temp = concatAndHash(sha256, left, right);
    Integer mi = 0;
    
    for (int j=0;j<c2.ByteCount()*8;j++)
    {
	mi.SetBit(j,temp.GetBit(j) != c2.GetBit(j));
    }

//    DEBUG("mi",&mi);
    
    Integer subMessage = 0;
    for (int i=0;i<4;i++)
    {
	subMessage.SetByte(i,mi.GetByte(i));
    }
    
//    DEBUG("message", &subMessage);

    Integer hTwo = hashInteger(sha256,mi);
    
    hTwo = ModularExponentiation(params.g, hTwo, params.p);

//    DEBUG("c1",&c1);
//    DEBUG("hTwo",&hTwo);

    out->log("sessionKeyDecryptionTime",std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count());
    
    //c1 should equal hTwo if not then fail
    if (c1.Compare(hTwo) == 0)
    {
	sessionKey = subMessage;
	return true;
    }
    return false;
}

}; //namespace
