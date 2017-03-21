#ifndef __SMIMP_UTILITYCOMPANY_H_
#define __SMIMP_UTILITYCOMPANY_H_

#include "examples.h"
#include "Requester.h"
#include "sha.h"

namespace SMImp
{

class UtilityCompany
{
private:
    KeyPair keys;
    CryptoPP::SHA1* shaone;

    MasterKey params;
/*    
    List<SmartMeter>* meterList;
    List<TrustedParty>* thirdPartyList;
    List<Integer>* anonIds;
    List<Integer>* hmacKeys;
*/
    List<List<Integer> >* SMList;
    List<List<Integer> >* TTPList;
    
    MasterKey masterKey;
    NonblockingRng* rng;

    void setMasterKey(Integer,Integer,Integer,Integer);

public:

    UtilityCompany(SHA1*);
    UtilityCompany();
    ~UtilityCompany();
    
    bool generateKey(Integer, const Integer&, const Integer&, const Integer&);

    Payload generatePartialKeys(Integer);
    
    bool verifyHMAC(Integer,HMACPayload);

    /*
    void setMeter(SmartMeter*);
    void setParty(TrustedParty*);
    */

    void registerSM(Integer* id);
    void registerTTP(Integer* id);

    List<Integer>* getSMbyAnonId(Integer);
    List<Integer>* getSM(Integer);
    List<Integer>* getTTP(Integer);

    void addSMData(Integer* id, Integer* data);
    void addTTPData(Integer* id, Integer* data);
    int getTTPSize(Integer* id);
	
    List<Integer>* getSMbyAnonId(Integer* id);
    /*
    void sendDataToTTP(Integer,char*,Integer,Integer);
    void sessionKeyExchange(Integer,Integer,char*,Integer); //It should be noted currently sessions keys can only be 4 bytes long
    void ForwardDataToTTP(HMACPayload, Integer,Integer);
    void ForwardMessageToTTP(HMACPayload, Integer,Integer);
    void ForwardMessageToSM(HMACPayload, Integer,Integer);
    void ForwardMessageToSM(HMACPayload, Integer,SmartMeter*);
    */
    /*
    SmartMeter* getMeter(Integer);
    TrustedParty* getParty(Integer);
    */
    
};

};
#endif
