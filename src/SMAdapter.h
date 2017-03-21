#ifndef SMADAPTER_H_
#define SMADAPTER_H_

#include "Adapter.h"

namespace SMImp {
    class SmartMeter;
};

namespace smart3p {
    class SmartMeter;
}

class SMAdapter : public Adapter
{
private:
    SMImp::SmartMeter* sm;
    
public:
    SMAdapter(long int); //Requires ID
    SMAdapter(long int, smart3p::Unit*); 
    ~SMAdapter();

    void registerInfoFromUC(omnetpp::cMessage *msg);

    cInteger* getId();
    cInteger* getAnonId();

    omnetpp::cQueue* startSessionKeyExchange(omnetpp::cMessage* msg);

    bool endOfSessionKeyExchange(omnetpp::cMessage *msg);
    omnetpp::cMessage* sendEnergyConsumption(omnetpp::cMessage *msg);

    void log(char*,double);
};

#endif
