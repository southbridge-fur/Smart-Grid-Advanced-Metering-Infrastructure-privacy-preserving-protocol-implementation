#include "SmartMeter.h"
#include "UtilityCompany.h"
#include "TrustedParty.h"

//namespce to help section out both SmartMeter classes
namespace SMImp {

void SmartMeter::generateKeys(Payload pl)
{
    if (!getPartials(anonId, pl)) return;
    keys.priv.piece = Integer(*rng,1,params.q);
    keys.pub.piece = ModularExponentiation(params.g, keys.priv.piece, params.p);

    //std::cout << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << " " <<  params.q.ByteCount() + params.x.ByteCount() + params.p.ByteCount() + params.g.ByteCount() + keys.priv.partial.ByteCount() + keys.priv.piece.ByteCount() + keys.pub.partial.ByteCount() + keys.pub.piece.ByteCount() << std::endl;
}

SmartMeter::SmartMeter(Integer i) : Requester (i)
{
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
}

Packet SmartMeter::sendDataToTTP(char* m, Integer l, Integer ttpId) //message here is the data which will be sent.
{
    SHA256* sha256 = new SHA256();
    
    Integer hOne = hashInteger(shaone, sessionKey);
    Integer gamma = ModularExponentiation(params.x,hOne,params.p);
    gamma = (gamma * (1 % params.p)) % params.p;

    int length = l.ConvertToLong();
    char* message = m;
    
    if (l % 4)
    {
	length = l.ConvertToLong() + (4-(l.ConvertToLong()%4)); //add to length what we need to get a multiple of 4
	message = new char[l.ConvertToLong()];    
	for (int i=0;i<length;i++) message[i] = char('0');
	for (int i=0;i<l;i++) message[i] = m[i];
    }
    
    for (int i=0;i<length/4;i++)
    {
	//start = std::chrono::high_resolution_clock::now();
	//std::cout << "SM_data_transmission ";
	
	word32 tempWord = 0;
	for (int j=0;j<4;j++) tempWord = tempWord*256 + int(message[j+(i*4)]);

	Integer timeStamp = time(new time_t()); //epoch
	Integer r = concatAndHash(sha256, tempWord, timeStamp);
	
	Integer cOne = ModularExponentiation(params.g,r,params.p);
	
	Integer gammaR = ModularExponentiation(gamma, r, params.p);
	Integer muR = ModularExponentiation(1, r, params.p);

	Integer temp = concatAndHash(sha256,muR,gammaR);

	HMACPayload payload;
	payload.c21 = 0;
	payload.c22 = 0;
	//l is 8 bytes
	//temp is 8 bytes long
	//l0 and l1 are both 4 bytes long
	for (int j=0;j<4;j++)
	{
	    std::bitset<8> byteMij ((byte)(message[j+(i*4)]));//getting really creative with these variable names here
	    std::bitset<8> byteone (temp.GetByte(j));
	    for (int k=0;k<8;k++)
	    {
		payload.c21.SetBit((j*8)+k,byteone[k] != byteMij[k]); //XORing Mi
	    }
	}
	//std::cout << payload.c21 << std::endl;
	for (int j=0;j<4;j++)
	{
	    std::bitset<8> byteTwo(temp.GetByte(j+4));
	    for (int k=0;k<8;k++) payload.c22.SetBit((j*8)+k, timeStamp.GetBit((j*8)+k) != (byte)byteTwo[k]);
	}
	//Now we have c1 and c2, time to run HMAC
	
	payload.c1 = cOne;
	payload.id = id;
	payload.timeStamp = timeStamp;	
	payload.hmac = generateHMAC(hmacKey,payload);
	payload.messageLength = length;
	
	//std::cout << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << R.ByteCount() + ttpId.ByteCount() << std::endl;
	//uc->ForwardDataToTTP(payload,ttpId,id);
	Packet packet;
	packet.dest = ttpId;
	packet.pl = payload;
	return packet;
    }
}

Packet SmartMeter::sessionKeyExchange(char* m, Integer l, Integer trustedPartyId, Integer trustedPartyKey, Integer trustedPartyMu)
{
    SHA256* sha256 = new SHA256();

    R = rng->GenerateWord32(); 

    // Integer trustedPartyKey = t->getPublicPartial();
    // Integer trustedPartyMu = t->getPublicMu();
    // Integer trustedPartyId = t->getId();
    //std::cout << trustedPartyKey << "\n" << trustedPartyMu << "\n" << trustedPartyId << std::endl;
    
    Integer hOne = concatAndHash(shaone, trustedPartyId, trustedPartyKey);

    Integer gamma = ModularExponentiation(params.x,hOne,params.p);
    gamma = (gamma * (trustedPartyKey % params.p)) % params.p;
    int length = l.ConvertToLong();
    char* message = m;
    
    if (l % 4)
    {
	length = l.ConvertToLong() + (4-(l.ConvertToLong()%4)); //add to length what we need to get a multiple of 4
	message = new char[l.ConvertToLong()];    
	for (int i=0;i<length;i++) message[i] = char('0');
	for (int i=0;i<l;i++) message[i] = m[i];
    }
    
    for (int i=0;i<length/4;i++)
    {
	//start = std::chrono::high_resolution_clock::now();
	//std::cout << "sm_encrypt_session_key ";

	word32 tempWord = 0;
	Integer sigma = rng->GenerateWord32(); //A full 4 bytes

	for (int j=0;j<4;j++) tempWord = tempWord*256 + int(message[j+(i*4)]);
		
	Integer r = concatAndHash(sha256,tempWord, sigma);
	//std::cout << r << std::endl;
	
	Integer cOne = ModularExponentiation(params.g,r,params.p);
	
	Integer gammaR = ModularExponentiation(gamma, r, params.p);
	Integer muR = ModularExponentiation(trustedPartyMu, r, params.p);

	Integer temp = concatAndHash(sha256, muR, gammaR);
	//create bit arrays of temp and r
	//for (int j=0;j<8;j++) std::cout << int(temp[j]) << " ";
	//std::cout << std::endl;
	HMACPayload payload;
	payload.c21 = 0;
	payload.c22 = 0;
	//l is 8 bytes
	//temp is 8 bytes long
	//l0 and l1 are both 4 bytes long
	for (int j=0;j<4;j++)
	{
	    std::bitset<8> byteMij ((byte)(message[j+(i*4)]));//getting really creative with these variable names here
	    std::bitset<8> byteone (temp.GetByte(j));
	    for (int k=0;k<8;k++)
	    {
		payload.c21.SetBit((j*8)+k,byteone[k] != byteMij[k]); //XORing Mi
	    }
	}
	//std::cout << payload.c21 << std::endl;
	for (int j=0;j<4;j++)
	{
	    std::bitset<8> byteTwo(temp.GetByte(j+4));
	    for (int k=0;k<8;k++) payload.c22.SetBit((j*8)+k, sigma.GetBit((j*8)+k) != byteTwo[k]);
	}
	//Now we have c1 and c2, time to run HMAC
	
	Integer timeStamp = time(new time_t()); //epoch
	payload.c1 = cOne;
	payload.id = id;
	payload.timeStamp = timeStamp;
	payload.r = R;	
	payload.hmac = generateHMAC(hmacKey,payload);
	payload.messageLength = length;

	//std::cout << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << " " << R.ByteCount() + trustedPartyId.ByteCount() << std::endl;
	
	Packet packet;
	packet.dest = trustedPartyId;
	packet.pl = payload;
	return packet;
    }
}

bool SmartMeter::recieveHMAC(Integer c1, Integer c21, Integer c22, Integer ttpId)
{
    SHA256* sha256 = new SHA256();
    //time to decrypt
    Integer left = ModularExponentiation(c1,keys.priv.piece,params.p);
    Integer right = ModularExponentiation(c1,keys.priv.partial,params.p);

    Integer temp = concatAndHash(sha256, left, right);

    sessionKey = 0;
    word32 tempWord = 0;
    for (int i=3;i>=0;i--) tempWord = tempWord*256 + temp.GetByte(i);
    std::bitset<32> tempByte(tempWord);
    for (int j=0;j<32;j++)
    {
	sessionKey.SetBit(j,(c21.GetBit(j) != tempByte[j]));
    }

    Integer r = 0;
    tempWord = 0;
    
    for (int i=3;i>=0;i--) tempWord = tempWord*256 + temp.GetByte(i+4);
    std::bitset<32> tempByteTwo(tempWord);
    for (int j=0;j<32;j++)
    {
	r.SetBit(j, tempByteTwo[j] != c22.GetBit(j));
    }

    Integer hTwo = concatAndHash(sha256,sessionKey,R);

    hTwo = ModularExponentiation(params.g, hTwo, params.p);
    std::cout << c1 << "\n" << hTwo << std::endl;
    //c1 should equal hTwo if not then fail
    if (c1 != hTwo)
    {
	return false;
    }
    return true;
}

}; //namespace
