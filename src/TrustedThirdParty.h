//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __SMART3P_TRUSTEDTHIRDPARTY_H_
#define __SMART3P_TRUSTEDTHIRDPARTY_H_

#include "Unit.h"
#include <omnetpp.h>
#include "TTPAdapter.h"

namespace smart3p {

using namespace omnetpp;

//! Trusted Thrid Party for the simulation.
class TrustedThirdParty : public Unit
{
  private:
    //! Adpater pointer
    TTPAdapter* ttp;

    /*!
      Registers smart3p::SmartMeter with the Trusted third party, passing the msg on to the Adapter
      \sa TTPAdapter::registerSM(cMessage *msg)
     */
    void registerSM(cMessage *msg);

    /*!
      Registers this Trusted Thrid Party with the Utiity Company
    */
    void registerAtUC(cMessage *msg);

    /*!
      Processes (decrypts and verifies) the data coming from the Smart Meter.
     */
    void processDataFromSM(cMessage *msg);

    /*! 
      Register key data coming from the Utility Company.
    */
    void registerInfoFromUC(cMessage *msg);

    /*! 
      Initiates the Session Key Exchange Phase
    */
    void startSessionKeyExchange();

    /*! 
      Called when recieving the session key from Smart Meter
    */
    void finishSessionKeyExchange(cMessage *msg);
    
  protected:
    virtual void initialize();

    //! Default message handler
    virtual void timedHandleMessage(cMessage *msg);

public:
    //! Print debug messages
    void print(char*);
};

} //namespace

#endif
