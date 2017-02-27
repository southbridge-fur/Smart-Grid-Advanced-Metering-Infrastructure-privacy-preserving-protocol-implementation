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

#include <Unit.h>

namespace smart3p {

Unit::Unit()
{
    // TODO Auto-generated constructor stub
    timeoutEvent = new cMessage("timeoutEvent");
    waitForDelivery = 5; // Wait for n seconds before re-sending the packet
}

Unit::~Unit()
{
    // TODO Auto-generated destructor stub
    drop(timeoutEvent);
    delete timeoutEvent;
}

void Unit::print(char* m)
{
    EV << m << endl;
}
    
void Unit::handleMessage(cMessage *cMsg)
{
    // beginTime
    bubble(cMsg->getName());

    timedHandleMessage(cMsg);
    // endTime
    // value = endTime - beginTime
    // save value with the corresponding message
}

void Unit::timedHandleMessage(cMessage *cMsg)
{
    EV << "Inside timed handle message with: " << cMsg->getName() << endl;
}

} /* namespace smart3p */
