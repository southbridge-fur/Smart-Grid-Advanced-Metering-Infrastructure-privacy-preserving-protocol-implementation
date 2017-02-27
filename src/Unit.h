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

class Unit : public cSimpleModule
{
  public:
    Unit();
    virtual ~Unit();

    void print(char*);
  protected:
    cMessage *timeoutEvent;
    double waitForDelivery;

    virtual void timedHandleMessage(cMessage *msg);
    void handleMessage(cMessage *msg);
};

} /* namespace smart3p */

#endif /* UNIT_H_ */
