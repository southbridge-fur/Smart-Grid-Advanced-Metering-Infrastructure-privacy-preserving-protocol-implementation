#ifndef INTEGER_H_
#define INTEGER_H_

#include <integer.h>
#include <omnetpp.h>

class cInteger : public omnetpp::cNamedObject, public CryptoPP::Integer
{
private:
    const char* className = "cInteger";
    const char* name;
    
public:
    cInteger(const char*);
    cInteger(const char*, CryptoPP::Integer*);
    cInteger(const char* n, int i);
    cInteger(cInteger*);
    virtual ~cInteger();

    const char* getClassName() const;
    const char* getName() const;
    void setName(const char*);
    
    cInteger* dup() const;

    CryptoPP::Integer* toInteger();
    
    void parsimPack(omnetpp::cCommBuffer* buffer) const;
    void parsimUnpack(omnetpp::cCommBuffer* buffer);
};

#endif
