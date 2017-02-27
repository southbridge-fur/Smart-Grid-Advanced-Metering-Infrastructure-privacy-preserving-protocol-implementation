#include "Collector.h"

#ifndef SMPacket
#include <SMPacket_m.h>
#endif

namespace smart3p {

Define_Module(Collector);

Collector::Collector()
{

}

Collector::~Collector()
{

}

void Collector::initialize()
{
    prevTime = simTime();
}

void Collector::timedHandleMessage(cMessage *msg)
{
    if (msg == NULL)
    {
	EV << "Recieved a NULL Message!" << endl;
	return;
    }
    
    SMPacket *p = check_and_cast<SMPacket*> (msg->getObject("packet"));

    // If the new energy consumption message has a bit error flag set
    // then discard the message and do not do anything else about it
    // The smart meter will have to re-send the packet from its own queue
    if (p->hasBitError())
    {
        EV << "Packer error in gate " << msg->getArrivalGate()->getIndex() << " connected with a Smart Meter" << endl;
        delete msg;
        return;
    }

    // Direction: SM --> UC
    // Receiving a message from generator, passed by the smart meter
    // Or receiving a registration message from SM to UC
    // Or receiving a request for a session key exchange
    if (!strcmp(msg->getName(), "smartMeterInit") ||
            !strcmp(msg->getName(), "registerFromSM") ||
            !strcmp(msg->getName(), "sessionKeyExchange"))
    {
        p->setSmGateID(msg->getArrivalGate()->getIndex());
        send(msg, "ucLine$o");

        return;
    }
    // Direction: SM <-- UC
    // Receiving a ready or register message from the utility company for SM
    // Or a session key from TTP to SM
    else if (!strcmp(msg->getName(), "ready") ||
	     !strcmp(msg->getName(), "registerInfoFromUC") ||
	     !strcmp(msg->getName(), "sessionKeyStartFromTTP") ||
	     !strcmp(msg->getName(), "sessionKey"))
    {
        // Pass the message along to the smart meter
        cGate* g = gate("radio$o", p->getSmGateID());
        send(msg, g);

        return;
    }

    // Sending the acknowledgment of receiving the packet
    // with the energy consumption data
    cMessage *ack = new cMessage("ACK");
    cGate* g = gate("radio$o", msg->getArrivalGate()->getIndex());
    send(ack, g);


    // Receiving a message with energy consumption
    dataQueue.insert(msg);
    if (simTime() >= prevTime + par("sendInterval").doubleValue())
    {
	/*
	while (!dataQueue.isEmpty())
	{
	    cMessage* out = check_and_cast<cMessage*>(dataQueue.pop());
	    send(out, "ucLine$o"); //the absolute madman
	}
	*/
	
        cMessage *job = new cMessage("Data_dumping");

        cQueue *dataToSend = new cQueue("dataToUC");

        while (!dataQueue.isEmpty())
        {
            dataToSend->insert(dataQueue.pop());
        }
	
	job->addObject(dataToSend);
        send(job, "ucLine$o");
        prevTime = simTime();
    }
}

}; // namespace
