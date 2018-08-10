#ifndef __SMIMP_UTILITYCOMPANY_H_
#define __SMIMP_UTILITYCOMPANY_H_

#include "examples.h"
#include "Requester.h"
#include "sha.h"

namespace SMImp
{

    //! Utility Company protocol-level implementation.
class UtilityCompany
{
private:
    //! Public and private keys for Utility Company.
    KeyPair keys;
    //! SHA1 generator.
    CryptoPP::SHA1* shaone;

/*    
    List<SmartMeter>* meterList;
    List<TrustedParty>* thirdPartyList;
    List<Integer>* anonIds;
    List<Integer>* hmacKeys;
*/
    //! Local list of representations of Smart Meters.
    List<List<Integer> >* SMList;
    //! Local list of representations of Trusted Third Parties.
    List<List<Integer> >* TTPList;

    //! Key generation parameters.
    /*! 
      Destributed to all Trusted Third Parties and Smart Meters, anything which extends SMImp::Requester.
    */
    MasterKey masterKey;

    //! Random number generator used to generate cryptographic keys.
    NonblockingRng* rng;

    //! Helper function to set the masterKey
    void setMasterKey(Integer p, Integer q, Integer g, Integer x);

public:

    UtilityCompany(SHA1*);
    UtilityCompany();
    ~UtilityCompany();

    /*!
      Utilizes [CryptoPP's nbtheory](https://www.cryptopp.com/docs/ref/nbtheory_8h.html#aaef9ef9567713cd9935e468309ebcc9d) to generate paramters for use in key generation.

      Heavy comments are utilized in the source file. It is recommended to read through this function in UtilityCompany.cc
    */
    bool generateKey(Integer q, const Integer& max, const Integer& equiv, const Integer& mod);

    /*!
      Generates partial private and public keys given the ID.
      \param id ID of the Requester object to generate a pair of keys for.
    */
    Payload generatePartialKeys(Integer id);

    /*!
      Verifies the HMAC of the given payload.
      \param id ID of the device to verify the message from.
      \param payload Payload containing the message to be verified.
    */
    bool verifyHMAC(Integer id,HMACPayload payload);

    /*!
      Registers Smart Meter with internal list of Smart Meter representations.
    */
    void registerSM(Integer* id);
    
    /*!
      Registers Trusted Third Party with internal list of Trusted Third Party representations.
    */
    void registerTTP(Integer* id);

    /*!
      Gets Smart Meter representation by a given anonymous ID.
      \param id The anonymous ID to search for.
      \return If found, returns the local Smart Meter representation. Returns NULL otherwise.
    */
    List<Integer>* getSMbyAnonId(Integer id);
	
    /*!
      Gets Smart Meter representation by a given ID.
      \param id The ID to search for.
      \return If found, returns the local Smart Meter representation. Returns NULL otherwise.
    */
    List<Integer>* getSM(Integer id);
    
    /*!
      Gets Trusted Third Party representation by a given ID.
      \param id The ID to search for.
      \return If found, returns the local Trusted Third Party representation. Returns NULL otherwise.
    */
    List<Integer>* getTTP(Integer id);

    /*!
      Adds arbitrary data to the local Smart Meter representation.
      \param id ID of the Smart Meter to add data to.
      \param data Data to add to the local Smart Meter representation.
    */
    void addSMData(Integer* id, Integer* data);

    /*!
      Adds arbitrary data to the local Trusted Third Party representation.
      \param id ID of the Trusted Third Party to add data to.
      \param data Data to add to the local Trusted Third Party representation.
    */
    void addTTPData(Integer* id, Integer* data);

    /*!
      Gets the count of elements in the Trusted Third Party local representation.
    */
    int getTTPSize(Integer* id);
};

};
#endif
