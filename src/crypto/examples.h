//Class references for Crypto++: http://www.cryptopp.com/docs/ref/index.html

#ifndef __SMIMP_EXAMPLES_H_
#define __SMIMP_EXAMPLES_H_

#include <iostream>
#include <stdlib.h> //atoi, itoa
#include <math.h>   //pow
#include <bitset>   //bitset
//#include <chrono>   //C++11 timing

#include "list.h"

//http://www.cryptopp.com/docs/ref/nbtheory_8h.html
#include "nbtheory.h"
#include "osrng.h"
#include "integer.h"
#include "hmac.h"
#include "sha.h"
#include "gfpcrypt.h"


#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "md2.h"

namespace SMImp {

using namespace CryptoPP;

struct MasterKey
{
    Integer p;
    Integer q;
    Integer g;
    Integer x;
};

struct Key
{
    Integer piece;
    Integer partial;
};

struct KeyPair
{
    Key priv; //Private key
    Key pub;  //Public key
};

struct Payload
{
    MasterKey params;
    Integer priv;
    Integer pub;
};

struct HMACPayload
{
    Integer messageLength;
    Integer hmac;
    Integer c1;
    Integer c2;
    Integer id;
    Integer timeStamp;
    Integer r;
};

struct Packet
{
    Integer dest;
    HMACPayload pl;
};

class UtilityCompany;
class TrustedParty;
class SmartMeter;


class pSelector : public PrimeSelector //Required for selecting primes
{
private:
    Integer p;
    
public:
    pSelector()
    {
	p=0;
    }
    ~pSelector()
    {}

    void setP(Integer newp)
    {
	p = newp;
    }
    
    bool IsAcceptable(const Integer &candidate) const
    {
	return IsPrime(candidate) ; //First run through, since p will not be set yet
    }
};

//TODO: Public helper functions (will wrap up in an abstract class or namespace
static byte* itob(Integer i) //Cryptopp::Integer to byte array
{
    byte* output = new byte[i.ByteCount()];
    for (unsigned int j=0;j<i.ByteCount();j++) output[j] = i.GetByte(j);
    return output;
}

static Integer btoi(byte* b, int length) //byte array to Cryptopp::Integer
{
    Integer output = 0;
    for (unsigned int i=0;i<length;i++) output.SetByte(i,int(b[i]));
    return output;
}

//meant to be used as a general hashing algorithm, takes in any sized input and outputs an Integer of size equal to the digest size
static Integer generateHash(HashTransformation* hash, byte* input, int length)
{
    hash->Restart();
    hash->Update(input,length);

    byte* outputString = new byte[hash->DigestSize()];
    hash->Final(outputString);

    Integer output = 0;

    for (unsigned int i=0;i<hash->DigestSize();i++)
    {
	output.SetByte(i,outputString[i]);
    }

    return output;    
}

static Integer concatAndHash(HashTransformation* hash, Integer one, Integer two)
{
    byte* input = new byte[one.ByteCount() + two.ByteCount()];
    for (unsigned int i=0;i<(one.ByteCount() + two.ByteCount());i++) input[i] = 0;
        
    for (unsigned int i=0;i<one.ByteCount();i++) input[i] = one.GetByte(i);
    for (unsigned int i=0;i<two.ByteCount();i++) input[i+one.ByteCount()] = two.GetByte(i);
    
    return generateHash(hash, input, one.ByteCount()+two.ByteCount());
}

static Integer hashInteger(HashTransformation* hash, Integer i)
{
    return generateHash(hash,itob(i),i.ByteCount());
}

static Integer generateHMAC(Integer key, HMACPayload pl)
{
    //verify HMAC
    HMAC<Weak::MD2>* hmac = new HMAC<Weak::MD2>(itob(key),key.ByteCount());
    hmac->Update(itob(pl.c1),pl.c1.ByteCount());
    hmac->Update(itob(pl.c2),pl.c2.ByteCount());
    hmac->Update(itob(pl.id),pl.id.ByteCount());
    hmac->Update(itob(pl.timeStamp),pl.timeStamp.ByteCount());

    int length = hmac->DigestSize();

    byte* digest = new byte[length];
    hmac->Final(digest);

    Integer output = Integer(digest,hmac->DigestSize());
    
    return output;
}

};

#endif
