#ifndef SMADAPTER_H_
#define SMADAPTER_H_

#include "Adapter.h"

namespace SMImp {
    class SmartMeter;
};

namespace smart3p {
    class SmartMeter;
}

//! Smart Meter Adapter
class SMAdapter : public Adapter
{
private:
    //! Pointer to protocol implementation
    SMImp::SmartMeter* sm;
    
public:
    /*!
      \param i Smart Meter ID
    */
    SMAdapter(long int i); //Requires ID
    /*!
      \param i Smart Meter ID
      \param u Output unit class (used for debugging)
      \sa log(char*, double), addSimTime(double)
    */
    SMAdapter(long int i, smart3p::Unit* u); 
    ~SMAdapter();

    /*!
      Registers key data from Utility Company.
    */
    void registerInfoFromUC(omnetpp::cMessage *msg);

    /*!
      Gets the ID from the underlying protocol Smart Meter
    */
    cInteger* getId();

    /*!
      Gets the Anonymous ID from the underlying protocol Smart Meter
    */
    cInteger* getAnonId();

    /*!
      Starts the session key generation.
      \return Queue of packets to be sent to Trusted Thrid Party.
    */
    omnetpp::cQueue* startSessionKeyExchange(omnetpp::cMessage* msg);

    /*!
      Finishes the session key exchange phase.
      \return tells if the final session key passed verification.
    */
    bool endOfSessionKeyExchange(omnetpp::cMessage *msg);

    /*!
      Sends encrypted energy use data to Trusted Thrid Party.
    */
    omnetpp::cMessage* sendEnergyConsumption(omnetpp::cMessage *msg);

    /*!
      Emits statistical data.
    */
    void log(char*,double);

    /*! 
      Adds time to the simulation
    */
    void addSimTime(double);
};

#endif
