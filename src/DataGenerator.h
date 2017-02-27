
#ifndef __SMART3P_DATAGENERATOR_H_
#define __SMART3P_DATAGENERATOR_H_

#include <omnetpp.h>
#include <map>
#include <queue>

namespace smart3p {

using namespace omnetpp;

class DataGenerator : public omnetpp::cSimpleModule
{
  private:
    bool* readyList;
    
    bool sendDataToSmartMeters();
    bool readData();
    cMessage *timer;
    int smCounter;
    // map<ID, energy_measurements>
    std::map<int, std::queue<double> > ECdata;
    std::queue<double>* outputQueue;

    void sendDataToSmartMeter(cMessage *msg);
    
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

} //namespace

#endif
