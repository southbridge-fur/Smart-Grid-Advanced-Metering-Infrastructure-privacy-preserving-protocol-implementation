#ifndef __SMIMP_SMARTMETER_H_
#define __SMIMP_SMARTMETER_H_

#include "examples.h"
#include "Requester.h"

namespace SMImp {
    
class SmartMeter : public Requester
{
private:
    Integer hmacKey;
    Integer anonId;

public:
    
    SmartMeter(Integer, CryptoPP::SHA1*);
    SmartMeter(Integer);
    virtual ~SmartMeter();

    void setHMACKey(Integer);
    void generateKeys(Payload);

    void setAnonId(Integer);
    Integer getAnonId();
    Packet sendDataToTTP(char*,Integer,Integer);
    Packet sessionKeyExchange(char*,Integer,Integer,Integer,Integer);
    bool recieveHMAC(Integer c1, Integer c21, Integer c22, Integer ttpId);
    
};

};
#endif
