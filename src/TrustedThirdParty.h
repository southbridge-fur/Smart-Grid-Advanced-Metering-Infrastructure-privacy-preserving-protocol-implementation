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

/**
 * TODO - Generated class
 */
class TrustedThirdParty : public Unit
{
  private:
    TTPAdapter* ttp;

    void registerSM(cMessage *msg);
    void registerAtUC(cMessage *msg);
    void processDataFromSM(cMessage *msg);
    void registerInfoFromUC(cMessage *msg);
    void startSessionKeyExchange();
    void finishSessionKeyExchange(cMessage *msg);
  protected:
    virtual void initialize();
    virtual void timedHandleMessage(cMessage *msg);
public:
    void print(char*);
};

} //namespace

#endif
