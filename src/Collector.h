
#ifndef __SMART3P_SOURCE_H
#define __SMART3P_SOURCE_H

#include "Unit.h"
#include <omnetpp.h>

namespace smart3p {

using namespace omnetpp;

//! Collector for smart3p::SmartMeter
/*!
  Collects messages smart3p::SmartMeter and forwards them to the smart3p::UtilityCompany.
*/
class Collector : public Unit
{
  private:
    /*!
      Previous time a message was sent.
     */
    simtime_t prevTime;
    /*!
      Queue of data to send to smart3p::UtilityCompany.
     */
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
