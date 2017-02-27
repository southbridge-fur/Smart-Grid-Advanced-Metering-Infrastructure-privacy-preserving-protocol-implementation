#include "Adapter.h"

#include "MKPacket_m.h"          //Master Key
#include "KPPacket_m.h"          //Key Pair
#include "KeyPacket_m.h"         //Key
#include "HMACPayloadPacket_m.h" //HMACPayload
#include "PayloadPacket_m.h"     //Payload

#include <omnetpp.h>
#include <stdlib.h> //atoi
#include <stdio.h> //sprintf

#include "Unit.h"

Adapter::Adapter(smart3p::Unit* o)
{
    out = o;
    verbose = (out != NULL);
}

Adapter::~Adapter()
{
    out = NULL;
}

void Adapter::print(char* m)
{
    DEBUG(m);
}

void Adapter::print(char* s, CryptoPP::Integer* i)
{
    char* debug = new char[256+(i->MinEncodedSize()*2)];

    sprintf(debug,"%s",s);
    
    for (int j=0; j<i->MinEncodedSize(); j++)
    {
	sprintf(debug,"%s%x",debug,i->GetByte(j));
    }


    //sprintf(debug,"%s\t%llu",s,i->ConvertToLong());
    
    DEBUG(debug);
}
