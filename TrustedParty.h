#ifndef __SMIMP_TRUSTEDPARTY_H_
#define __SMIMP_TRUSTEDPARTY_H_

#include "examples.h";
#include "Requester.h";

namespace SMImp {

class TrustedParty : public Requester
{
private:
    void init(Integer,SHA1*);
    
    char* message;
    int messageBytesRecieved;
    
public:
    TrustedParty(Integer,SHA1*);
    TrustedParty(Integer);
    virtual ~TrustedParty();

    Packet confirmSession(Integer,Integer,Key);

    bool recieveData(Integer length, Integer c1, Integer c21, Integer c22, Integer id);
    bool recieveHMAC(Integer length, Integer c1, Integer c21, Integer c22, Integer id, Key smKey, Integer r);
    
};

};

#endif
