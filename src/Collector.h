
#ifndef __SMART3P_SOURCE_H
#define __SMART3P_SOURCE_H

#include "Unit.h"
#include <omnetpp.h>

namespace smart3p {

using namespace omnetpp;

/**
 * Generates messages; see NED file for more info.
 */
class Collector : public Unit
{
  private:
    simtime_t prevTime;
    cQueue dataQueue;
  public:
    Collector();
     virtual ~Collector();

  protected:
    virtual void initialize();
    virtual void timedHandleMessage(cMessage *msg);
};

}; // namespace

#endif
