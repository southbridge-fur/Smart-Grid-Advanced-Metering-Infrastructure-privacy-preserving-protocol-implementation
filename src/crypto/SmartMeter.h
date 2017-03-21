#ifndef __SMIMP_SMARTMETER_H_
#define __SMIMP_SMARTMETER_H_

#include "examples.h"
#include "Requester.h"

class SMAdapter;

namespace SMImp {
    
class SmartMeter : public Requester
{
private:
    Integer hmacKey;
    Integer anonId;
    Integer sessionKey;
    
    bool verbose;
    ::SMAdapter* out;

public:
    SmartMeter(Integer, CryptoPP::SHA1*);
    SmartMeter(Integer, ::SMAdapter*);
    SmartMeter(Integer);
    virtual ~SmartMeter();

    void setHMACKey(Integer);
    bool generateKeys(Payload);

    void setAnonId(Integer);
    Integer getAnonId();
    Packet* sendDataToTTP(Integer);
    Packet* sessionKeyExchange(char*,Integer,Integer,Integer,Integer);
    bool recieveHMAC(Integer c1, Integer c2, Integer ttpId);
    
};

};
#endif
