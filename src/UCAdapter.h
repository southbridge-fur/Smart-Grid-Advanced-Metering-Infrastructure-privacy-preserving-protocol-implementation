#ifndef UCADAPTER_H_
#define UCADAPTER_H_

#include "Adapter.h"

namespace SMImp {
    class UtilityCompany;
};

namespace smart3p {
    class UtilityCompany;
};

//! Utility Company Adapter
class UCAdapter : public Adapter
{
private:
    //! Pointer to protocol implementation
    SMImp::UtilityCompany* uc;
    
public:
    /*!
      \param u Output unit class (used for debugging)
    */
    UCAdapter(smart3p::Unit* u);
    UCAdapter(); 
    ~UCAdapter();

    /*!
      Registers Smart Meter with Utility Company.
    */
    omnetpp::cMessage* registerSM(omnetpp::cMessage*);

    /*!
      Registers Trusted Third Party with Utility Company.
    */
    omnetpp::cMessage* registerTTP(omnetpp::cMessage *msg);

    /*!
      Finalizes Trusted Third Party registration.
    */
    void finishRegisteringTTP(omnetpp::cMessage *msg);

    /*!
      Passes session key start signal to the lower-level protocol implementation.
    */
    omnetpp::cMessage* sessionKeyStartFromTTP(omnetpp::cMessage *msg);

    /*!
      Passes session key exchange data from Trusted Thrid Party to lower-level protocol implementation.
    */
    bool sessionKeyExchangeFromTTP(omnetpp::cMessage *msg);
    /*!
      Passes session key exchange data from Smart Meter to lower-level protocol implementation.
    */
    bool sessionKeyExchangeFromSM(omnetpp::cMessage *msg);

    /*!
      Passes energy consuption data packets to lower-level protocol implementation for HMAC verification.
      \return Indicates if verification failed or not (false if failed).
    */
    bool energyConsumptionProcessing(omnetpp::cMessage *msg);
};

#endif
