#include "TrustedParty.h"
#include "UtilityCompany.h"

namespace SMImp {

TrustedParty::TrustedParty(Integer i) : Requester(i)
{
    static SHA1* shaone = new SHA1();
    init(i,shaone);
}
    
TrustedParty::TrustedParty(Integer i, SHA1* s) : Requester(i, s)
{
    init(i,s);
}

TrustedParty::~TrustedParty()
{
}

void TrustedParty::init(Integer i, SHA1* s)
{
    message = NULL;
    messageBytesRecieved = 0;
}
    
Packet TrustedParty::confirmSession(Integer req, Integer smId, Key smKey)
{ 
    R = req; //set private variable R
    //sessionKey;

    SHA256* sha256 = new SHA256();
    
    Integer hOne = concatAndHash(shaone,smId,smKey.partial);
    Integer gamma = ModularExponentiation(params.x,hOne,params.p);
    gamma = (gamma * (smKey.partial % params.p)) % params.p;

    Integer r = concatAndHash(sha256,sessionKey,R);
    Integer cOne = ModularExponentiation(params.g,r,params.p);

    Integer muR = ModularExponentiation(smKey.piece, r, params.p);
    Integer gammaR = ModularExponentiation(gamma, r, params.p);

    Integer temp = concatAndHash(sha256, muR, gammaR);
    
    HMACPayload payload;
    payload.c21 = 0;
    payload.c22 = 0;

    word32 tempWord = 0;
    for (int i=3;i>=0;i--) tempWord = tempWord*256 + temp.GetByte(i);

    std::bitset<32> byteone (tempWord);
    std::bitset<32> bytetwo (sessionKey.ConvertToLong()); //Both smKey and R are 32 bits
    for (int j=0;j<32;j++)
    {
	payload.c21.SetBit(j,byteone[j] != bytetwo[j]); //XORing "Mi"
    }
    
    tempWord = 0;
    for (int i=3;i>=0;i--) tempWord = tempWord*256 + temp.GetByte(i+4);

    std::bitset<32> bytethree (tempWord);
    std::bitset<32> bytefour (R.ConvertToLong());
    for (int j=0;j<32;j++)
    {
	payload.c22.SetBit(j,bytethree[j] != bytefour[j]); //XORing
    }
    //Now we have c1 and c2, time to run HMAC

    Integer timeStamp = time(new time_t()); //epoch
    payload.c1 = cOne;
    payload.id = 0;
    payload.timeStamp = timeStamp;
    //payload.hmac = generateHMAC(0,payload);

    Packet packet;
    packet.dest = smId;
    packet.pl = payload;
    return packet;
}

//TODO ask vitaly about this algorithm
bool TrustedParty::recieveData(Integer length, Integer c1, Integer c21, Integer c22, Integer smId)
{
    SHA256* sha256 = new SHA256();

    if (message == NULL || messageBytesRecieved >= length)
    {
	if (message != NULL) delete message;
	message = new char[length.ConvertToLong()];
	messageBytesRecieved = 0;
    }
//    start = std::chrono::high_resolution_clock::now();
//    std::cout << "TTP_data_transmission ";
    
    //time to decrypt
    Integer left = ModularExponentiation(c1,sessionKey,params.p);
    Integer right = ModularExponentiation(c1,1,params.p);
    
    Integer temp = concatAndHash(sha256, left,right);

    byte* subMessage = new byte[4]; //Mi
    //for (int j=0;j<8;j++) std::cout << int(temp[j]) << " ";
    //std::cout << std::endl;
    for (int j=0;j<4;j++)
    {
	std::bitset<8> outbyte;
	std::bitset<8> tempByte(temp.GetByte(j));
	for (int i=0;i<8;i++)
	{
	    outbyte[i] = (c21.GetBit((j*8)+i) != tempByte[i]);
	}
	subMessage[j] = outbyte.to_ulong();
    }

    Integer sigma;
    for (int j=0;j<4;j++)
    {
	std::bitset<8> tempByte(temp.GetByte(j+4));
	for (int k=0;k<8;k++) sigma.SetBit((j*8)+k, tempByte[k] != c22.GetBit((j*8)+k));
    }

    Integer hTwo = concatAndHash(sha256, btoi(subMessage,4), sigma);
    
    hTwo = ModularExponentiation(params.g, hTwo, params.p);
    //std::cout << hTwo << "\n" << c1 << std::endl;
    //std::cout << c1 << "\n" << hTwo << std::endl;
    //c1 should equal hTwo if not then fail
    
//std::cout << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
    
    if (c1 == hTwo)
    {
//	std::cout << "pass" << std::endl;
	for (int i=0;i<4;i++) message[messageBytesRecieved++] = subMessage[i];
	if (length == messageBytesRecieved)
	{
	    for (int h=0;h<messageBytesRecieved;h++)
		std::cout << message[h];
	    std::cout << std::endl;
	}
	return true;
    }
    return false;
//    else std::cout << "fail" << std::endl;
}

bool TrustedParty::recieveHMAC(Integer length, Integer c1, Integer c21, Integer c22, Integer smId, Key smKey, Integer r)
{
    SHA256* sha256 = new SHA256();
    if (message == NULL || messageBytesRecieved >= length)
    {
	if (message != NULL) delete message;
	message = new char[length.ConvertToLong()];
	messageBytesRecieved = 0;
    }
    
//    start = std::chrono::high_resolution_clock::now();
//    std::cout << "TTP_decrypt_session_key ";
    
    //time to decrypt
    Integer left = ModularExponentiation(c1,keys.priv.piece,params.p);
    Integer right = ModularExponentiation(c1,keys.priv.partial,params.p);

    Integer temp = concatAndHash(sha256, left, right);

    byte* subMessage = new byte[4]; //Mi
    //for (int j=0;j<8;j++) std::cout << int(temp[j]) << " ";
    //std::cout << std::endl;
    for (int j=0;j<4;j++)
    {
	std::bitset<8> outbyte;
	std::bitset<8> tempByte(temp.GetByte(j));
	for (int i=0;i<8;i++)
	{
	    outbyte[i] = (c21.GetBit((j*8)+i) != tempByte[i]);
	}
	subMessage[j] = outbyte.to_ulong();
    }

    Integer sigma;
    for (int j=0;j<4;j++)
    {
	std::bitset<8> tempByte(temp.GetByte(j+4));
	for (int k=0;k<8;k++) sigma.SetBit((j*8)+k, tempByte[k] != c22.GetBit((j*8)+k));
    }
    
    Integer hTwo = concatAndHash(sha256, btoi(subMessage,4), sigma);
    
    hTwo = ModularExponentiation(params.g, hTwo, params.p);
    //std::cout << c1 << "\n" << hTwo << std::endl;
    //c1 should equal hTwo if not then fail
//std::cout << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
    if (c1 == hTwo)
    {
	for (int i=0;i<4;i++) message[messageBytesRecieved++] = subMessage[i];
	if (length == messageBytesRecieved)
	{
	    //confirmSession(r, smId, smKey);
	    return true;
	}
    }
    return false;
}

};
