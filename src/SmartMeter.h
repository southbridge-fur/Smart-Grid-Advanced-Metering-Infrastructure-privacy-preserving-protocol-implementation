
#ifndef __SMART3P_SMARTMETER_H
#define __SMART3P_SMARTMETER_H
#include "Unit.h"
#include <omnetpp.h>


class SMAdapter;

namespace smart3p {

using namespace omnetpp;

/**
 * Message sink; see NED file for more info.
 */
class SmartMeter : public Unit
{
  private:
    // state
    simtime_t lastArrival;
    long int smID;
    cQueue *energyDataQueue;
    cMessage *startSendingEnergyData;

    // statistics
    simsignal_t stackSizeSignal;
    simsignal_t sessionKeyDecryptionTimeSignal;
    simsignal_t sessionKeyEncryptionTimeSignal;
    simsignal_t dataEncryptionTimeSignal;
    
    cDoubleHistogram iaTimeHistogram;
    cOutVector arrivalsVector;

    // functionality
    void smartMeterInit(cMessage *msg);
    void registerAtUC();
    void registerInfoFromUC(cMessage *msg);
    void startSessionKeyExchange(cMessage *msg);
    void endOfSessionKeyExchange(cMessage *msg);
    void sendEnergyConsumption(cMessage *msg);
    void sendQueueDataToCollector();

    // adapter
    SMAdapter* sm;

  protected:
    virtual void initialize();
    virtual void timedHandleMessage(cMessage *msg);
    virtual void finish();

public:
    //emit
    void log(simsignal_t id, double value); //simsignal_t is just type def'ed as an int
    void log(char* tag, double value);
};

}; // namespace

#endif
