#ifndef TTPADAPTER_H_
#define TTPADAPTER_H_

#include "Adapter.h"

namespace SMImp {
    class TrustedParty;
};

class TTPAdapter : public Adapter
{
private:
    SMImp::TrustedParty* ttp;

public:
    TTPAdapter(int id); //requires ID
    TTPAdapter(int id,smart3p::Unit*); //requires ID
    ~TTPAdapter();

    void registerSM(omnetpp::cMessage*);
    
    omnetpp::cQueue* startSessionKeyExchange();
    omnetpp::cMessage* finishSessionKeyExchange(omnetpp::cMessage*);
    
    void registerInfoFromUC(omnetpp::cMessage*);
    omnetpp::cMessage* registerAtUC();

    void processDataFromSM(omnetpp::cMessage*);
};

#endif

