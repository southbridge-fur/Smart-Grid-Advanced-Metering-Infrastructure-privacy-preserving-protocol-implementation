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

#ifndef UNIT_H_
#define UNIT_H_

#include <omnetpp.h>

namespace smart3p {

using namespace omnetpp;

//! Abstract class for the simulation
/*!
  An abstract class designed to be extended by the nodes within the simulation.
*/
class Unit : public cSimpleModule
{
  public:
    //! Default constrcutor
    Unit();
    virtual ~Unit();

    /*!
      Used by Adapter classes to print messages to the simulation screen.
      \param s String to print.
      \sa Adapter::print(char*)
     */
    void print(char* s);
    
  protected:
    /*!
      cMessage used to signal a timeout event.
      \sa waitForDelivery
     */
    cMessage *timeoutEvent;
    /*! 
      Amount of time to wait for the delivery of an outgoing message.
      \sa timeoutEvent
    */
    double waitForDelivery;

    /*! 
      Unused, simply prints te message name.
      \param msg Input message to be handled.
    */
    virtual void timedHandleMessage(cMessage *msg);
    
    //! Main message handler
    /*!
      Main message handler.
      \param msg Input message to be handled.
      \sa smart3P::SmartMeter::handleMessage(cMessage *msg), smart3P::UtilityCompany::handleMessage(cMessage *msg), smart3P::TrustedThirdParty::handleMessage(cMessage *msg) and smart3P::Collector::handleMessage(cMessage *msg)
    */
    void handleMessage(cMessage *msg);
};

} /* namespace smart3p */

#endif /* UNIT_H_ */
