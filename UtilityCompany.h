#ifndef __SMIMP_UTILITYCOMPANY_H_
#define __SMIMP_UTILITYCOMPANY_H_

#include "examples.h";
#include "Requester.h";

namespace SMImp {
    
class UtilityCompany
{
private:
    KeyPair keys;
    SHA1* shaone;

    MasterKey params;
    
    List<SmartMeter>* meterList;
    List<TrustedParty>* thirdPartyList;
    List<Integer>* anonIds;
    List<Integer>* hmacKeys;

    MasterKey masterKey;
    NonblockingRng* rng;

    void setMasterKey(Integer,Integer,Integer,Integer);

    bool verifyHMAC(HMACPayload);
public:
    UtilityCompany(SHA1*);
    ~UtilityCompany();
    bool generateKey(Integer, const Integer&, const Integer&, const Integer&);

    void setMeter(SmartMeter*);
    void setParty(TrustedParty*);

    void sendDataToTTP(Integer,char*,Integer,Integer);
    void sessionKeyExchange(Integer,Integer,char*,Integer); //It should be noted currently sessions keys can only be 4 bytes long
    void ForwardDataToTTP(HMACPayload, Integer,Integer);
    void ForwardMessageToTTP(HMACPayload, Integer,Integer);
    void ForwardMessageToSM(HMACPayload, Integer,Integer);
    void ForwardMessageToSM(HMACPayload, Integer,SmartMeter*);

    SmartMeter* getMeter(Integer);
    TrustedParty* getParty(Integer);
    
    Payload generatePartialKeys(Integer);
};

};
#endif
