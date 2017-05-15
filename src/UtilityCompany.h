
#ifndef __SMART3P_UTILITYCOMPANY_H_
#define __SMART3P_UTILITYCOMPANY_H_

#include "Unit.h"
#include <omnetpp.h>
#include <vector>
//#include <cqueue.h>
#include <string>

#include "UCAdapter.h"

#ifndef SMPacket
#include <SMPacket_m.h>
#endif

namespace smart3p {

using namespace omnetpp;

//! Unused
struct MeterData
{
    int anonymID;
    int smGate;
    int collGate;
    std::string secretSMtoUCkey;
};

//! Utility Company class for the simulation
class UtilityCompany : public Unit
{
  public:
    UtilityCompany();
    ~UtilityCompany();

  private:
    /*!
      Adds incoming packet to the packet database.

      **Currently unused** but will be utilized in the future for better security simulations.
     */
    void addPacketToDB(SMPacket *p);

    /*!
      Initiates the smart3p::SmartMeter
    */
    void smartMeterInit(cMessage *msg);

    /*! 
      Registers incoming data from smart3p::SmartMeter
    */
    void registerSM(cMessage *msg);

    /*!
      Registers incoming data from smart3p::TrustedThridParty
    */
    void registerTTP(cMessage *msg);

    /*! 
      Passes through registration data from the smart3p::SmartMeter intended for smart3p::TrustedThridParty.
    */
    void registerSMWithTTP(cMessage *msg);

    /*! 
      Pass-through function for session key start signal originating from Trusted Third Party.
    */
    void sessionKeyStartFromTTP(cMessage *msg);

    /*!
      Pass-through function for session key exchange data originating from Trusted Thrid Party.
    */
    void sessionKeyExchangeFromTTP(cMessage *msg);

    /*!
      Pass-through function for session key exchange data originating from Smart Meter.
    */
    void sessionKeyExchangeFromSM(cMessage *msg);

    /*!
      Energy Data processing and forwarding.
     */
    void energyConsumptionProcessing(cMessage *msg);
    
    simtime_t prevTime;
    cArray *data;

    //! Currently unused
    std::map<int, MeterData> meters; //not used

    //! Adapter pointer
    ::UCAdapter* uc;

protected:
    virtual void initialize();

    //! Default message handler.
    virtual void timedHandleMessage(cMessage *msg);
};

} //namespace

#endif
