
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

struct MeterData
{
    int anonymID;
    int smGate;
    int collGate;
    std::string secretSMtoUCkey;
};

/**
 * Simulates Utility Company
 */
class UtilityCompany : public Unit
{
  public:
    UtilityCompany();
    ~UtilityCompany();

  private:
    void addPacketToDB(SMPacket *p);
    void smartMeterInit(cMessage *msg);
    void registerSM(cMessage *msg);
    void registerTTP(cMessage *msg);
    void registerSMWithTTP(cMessage *msg);
    void sessionKeyStartFromTTP(cMessage *msg);
    void sessionKeyExchangeFromTTP(cMessage *msg);
    void sessionKeyExchangeFromSM(cMessage *msg);
    void energyConsumptionProcessing(cMessage *msg);
    
    simtime_t prevTime;
    cArray *data;
    std::map<int, MeterData> meters; //not used

    ::UCAdapter* uc;

protected:
    virtual void initialize();
    virtual void timedHandleMessage(cMessage *msg);
};

} //namespace

#endif
