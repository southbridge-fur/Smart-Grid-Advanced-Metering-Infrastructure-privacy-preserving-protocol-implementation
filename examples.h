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
    byte* hmac;
    Integer hmacLength;
    Integer c1;
    Integer c21;
    Integer c22;
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
    Integer blockLength = hash->BlockSize();
    if (length <= 0 || blockLength <= 0) return 0;
    
//check length of array and see if it is a multiple of the input length
    if ((Integer(length) % blockLength) != 0)
    {
	int newLength = length + (blockLength.ConvertToLong() - (length%blockLength.ConvertToLong()));
	byte* newInput = new byte[newLength];
	for (unsigned int i=0;i<newLength;i++) newInput[i] = '0';
	for (unsigned int i=0;i<length;i++) newInput[i] = input[i];
	free(input);
	input = newInput;
	length = newLength;   
    }
//make sure to use recursion if array is too large, include padding algorithm
    Integer output = 0;
    if (length > blockLength)
    {
	byte* currentString = new byte[blockLength.ConvertToLong()];
	for (unsigned int i=0;i<blockLength.ConvertToLong();i++) currentString[i] = input[i];
	byte* newInput = new byte[length-blockLength.ConvertToLong()];
	for (unsigned int i=0;i<length-blockLength;i++) newInput[i] = input[i+blockLength.ConvertToLong()];
	output = generateHash(hash, newInput, length-blockLength.ConvertToLong());
	free(input);
	input = currentString;
    }
//generate hash
    Integer newOutput = 0;
    hash->Restart();
    hash->Update(input,blockLength.ConvertToLong());
    byte* outputString = new byte[hash->DigestSize()];
    for (unsigned int i=0;i<hash->DigestSize();i++) outputString[i] = 0;
    hash->Final(outputString);
    for (unsigned int i=0;i<hash->DigestSize();i++)
    {
	std::bitset<8> byte (outputString[i]);
	for (unsigned int j=0;j<8;j++) output.SetBit((i*8)+j, output.GetBit((i*8)+j) != byte[j]);
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

static byte* generateHMAC(Integer key, HMACPayload pl)
{
    int length = pl.c1.ByteCount() + pl.c22.ByteCount() + pl.c21.ByteCount() + pl.id.ByteCount() + pl.timeStamp.ByteCount();
    //verify HMAC
    byte* HMACInput = new byte[length];
    int j =0;
    for ( ;j<pl.c1.ByteCount(); j++) HMACInput[j] = pl.c1.GetByte(j);
    for (unsigned int h=0; h<pl.c21.ByteCount(); h++) HMACInput[j++] = pl.c21.GetByte(h);
    for (unsigned int h=0; h<pl.c22.ByteCount(); h++) HMACInput[j++] = pl.c22.GetByte(h);
    for (unsigned int h=0; h<pl.id.ByteCount(); h++) HMACInput[j++] = pl.id.GetByte(h);
    for (unsigned int h=0; h<pl.timeStamp.ByteCount(); h++) HMACInput[j++] = pl.timeStamp.GetByte(h);

    HMAC<Weak::MD2>* hmac = new HMAC<Weak::MD2>(itob(key),key.ByteCount());
    hmac->Restart();
    hmac->Update(HMACInput,length);
    byte* digest = new byte[hmac->DigestSize()];
    hmac->Final(digest);
    byte* output = new byte[hmac->DigestSize()+1];
    output[0] = hmac->DigestSize();
    for (unsigned int i=1;i<=hmac->DigestSize();i++)output[i] = digest[i-1];
    return output;
}

};

#endif
