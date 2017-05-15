#ifndef TTPADAPTER_H_
#define TTPADAPTER_H_

#include "Adapter.h"

namespace SMImp {
    class TrustedParty;
};

//! Trusted Thrid Party Adapter
class TTPAdapter : public Adapter
{
private:
    //! Pointer to protocol implementation
    SMImp::TrustedParty* ttp;

public:
    /*!
      \param id Trusted Third Party ID
    */
    TTPAdapter(int id); //requires ID
    /*!
      \param id Trusted Third Party ID
      \param u Output unit class (used for debugging)
    */
    TTPAdapter(int id,smart3p::Unit* u); //requires ID
    ~TTPAdapter();

    /*!
      Registers Smart Meter with Trusted Thrid Party
    */
    void registerSM(omnetpp::cMessage*);

    /*!
      Begins the session key exchange phase.
      \return Queue of outgoing packets
    */
    omnetpp::cQueue* startSessionKeyExchange();

    /*!
      Finishes the session key exchange phase, forwarding the final state to the Smart Meter.
    */
    omnetpp::cMessage* finishSessionKeyExchange(omnetpp::cMessage*);

    /*!
      Registers info recievd from Utility Company regarding key generation.
    */
    void registerInfoFromUC(omnetpp::cMessage*);

    /*!
      Registers Trusted Thrid Party with Utility Company.
    */
    omnetpp::cMessage* registerAtUC();

    /*!
      Processes energy consumption data from Smart Meter.
    */
    void processDataFromSM(omnetpp::cMessage*);
};

#endif

