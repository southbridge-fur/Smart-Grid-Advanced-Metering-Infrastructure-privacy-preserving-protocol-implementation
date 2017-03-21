#ifndef UCADAPTER_H_
#define UCADAPTER_H_

#include "Adapter.h"

namespace SMImp {
    class UtilityCompany;
};

namespace smart3p {
    class UtilityCompany;
};

class UCAdapter : public Adapter
{
private:
    SMImp::UtilityCompany* uc;
    
public:
    UCAdapter(smart3p::Unit*); 
    UCAdapter(); 
    ~UCAdapter();

    omnetpp::cMessage* registerSM(omnetpp::cMessage*);
    omnetpp::cMessage* registerTTP(omnetpp::cMessage *msg);
    void finishRegisteringTTP(omnetpp::cMessage *msg);
    
    omnetpp::cMessage* sessionKeyStartFromTTP(omnetpp::cMessage *msg);
    bool sessionKeyExchangeFromTTP(omnetpp::cMessage *msg);
    bool sessionKeyExchangeFromSM(omnetpp::cMessage *msg);
    bool energyConsumptionProcessing(omnetpp::cMessage *msg);
};

#endif
