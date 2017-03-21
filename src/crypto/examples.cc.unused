//This file is a set of examples regarding various designs for methods needed in cryptography
//Created by: Daniel Tyler
//Most of this was greated through experementation with much of the crypto++ library
//Class references: http://www.cryptopp.com/docs/ref/index.html

//#include "examples.h"

#include "SmartMeter.h"
#include "UtilityCompany.h"
#include "TrustedParty.h"
#include "Requester.h"

//auto start = std::chrono::high_resolution_clock::now();

using namespace SMImp;

int main (int argc, char** argv)
{
    static SHA1* shaone = new SHA1();
    UtilityCompany* uc = new UtilityCompany(shaone);
    //generateKey returns false if it cannot generate both p and q, true otherwise.
    if (argc == 5)
    {
	if (!uc->generateKey(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]))) //to test out the FirstPrime function
	    return 1;
    }
    else if (!uc->generateKey(Integer::Power2(511), Integer::Power2(512), 5, 6)) //These numbers were arbitrarily chosen and can be specified on the command line
	return 1;
    
    Integer smId = 10000;
    SmartMeter* sm = new SmartMeter(smId,shaone);
    uc->setMeter(sm);

    sm->generateKeys(uc->generatePartialKeys(sm->getAnonId()));

    TrustedParty* tp = new TrustedParty(10001,shaone);
    tp->generateKeys(uc->generatePartialKeys(tp->getId()));
    uc->setParty(tp);

    //send message
    char* message = "asdf";
    int length = 4;

    uc->sessionKeyExchange(sm->getAnonId(),tp->getId(),message,length);

    char* data = "1234";
    int dataLength = 4;
    uc->sendDataToTTP(sm->getAnonId(),data,dataLength,tp->getId());
    
    delete uc, sm, tp;
    
    return 0;
}
