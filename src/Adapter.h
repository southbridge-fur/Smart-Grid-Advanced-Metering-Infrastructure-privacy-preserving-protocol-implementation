#ifndef ADAPTER_H_
#define ADAPTER_H_
//Contains all the struct-to-message and message-to-struct methods
#include "crypto/examples.h"
#include <omnetpp.h>

#include "cInteger.h"
#include "integer.h"

#define DEBUG(x) if (verbose) out->print(x);

namespace smart3p
{
    class Unit;
}

class Adapter
{
protected:
    bool verbose;
    smart3p::Unit* out;
    
public:

    Adapter(smart3p::Unit* o = NULL);
    virtual ~Adapter();

    void print(char*);
    void print(char*, CryptoPP::Integer*);
    
    static unsigned char* itob(CryptoPP::Integer i) //Cryptopp::Integer to unsigned char array
    {
	unsigned char* output = new unsigned char[i.ByteCount()];
	for (unsigned int j=0;j<i.ByteCount();j++) output[j] = i.GetByte(j);
	return output;
    }

    static const char* itobConst(CryptoPP::Integer i) 
    {
	unsigned char* temp = itob(i);
        const char* output = reinterpret_cast<const char*>(temp);
	
	return output;
    }

    static CryptoPP::Integer btoi(unsigned char* b, int length) //unsigned char array to Cryptopp::Integer
    {
	CryptoPP::Integer output = 0;
	for (unsigned int i=0;i<length;i++) output.SetByte(i,int(b[i]));
	return output;
    }

    static CryptoPP::Integer btoi(const char* b, int length)
    {
	unsigned char* temp = new unsigned char[length];

	for (int i=0; i<length; i++) temp[i] = b[i];

	return btoi(temp,length);
    }
};

#endif
