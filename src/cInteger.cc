#include "cInteger.h"

cInteger::cInteger(const char* n) : omnetpp::cNamedObject(n), CryptoPP::Integer()
{
    name = n;
}

cInteger::cInteger(const char* n, CryptoPP::Integer* i) : omnetpp::cNamedObject(n), CryptoPP::Integer(*i)
{
    name = n;
}

cInteger::cInteger(const char* n, int i) : omnetpp::cNamedObject(n), CryptoPP::Integer(i)
{
    name = n;
}

cInteger::cInteger(cInteger* i) : omnetpp::cNamedObject(*dynamic_cast<omnetpp::cNamedObject*>(i)),
    CryptoPP::Integer(*dynamic_cast<CryptoPP::Integer*>(i))
{
    name = i->getName();
}

cInteger::~cInteger()
{
}

const char* cInteger::getClassName() const
{
    return className;
}
const char* cInteger::getName() const
{
    return name;
}

void cInteger::setName(const char* s)
{
    name = s;
}

cInteger* cInteger::dup() const
{
    return new cInteger(const_cast<cInteger*> (this));
}

CryptoPP::Integer* cInteger::toInteger()
{
    return dynamic_cast<CryptoPP::Integer*> (this);
}

void cInteger::parsimPack(omnetpp::cCommBuffer* buffer) const
{
    if (buffer == NULL) return;
    
    unsigned char d;
    for (int i =0; i< this->ByteCount(); i++)
    {
	d = this->GetByte(i);
	buffer->pack(d);
    }
}

void cInteger::parsimUnpack(omnetpp::cCommBuffer* buffer)
{
    if (buffer == NULL) return;

    unsigned char d;
    int count = 0;
    while (!buffer->isBufferEmpty())
    {
	buffer->unpack(d);
	this->SetByte(count++,d);
    }
}
    
