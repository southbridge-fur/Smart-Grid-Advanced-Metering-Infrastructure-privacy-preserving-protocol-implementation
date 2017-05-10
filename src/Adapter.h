#ifndef ADAPTER_H_
#define ADAPTER_H_
//Contains all the struct-to-message and message-to-struct methods
#include "crypto/examples.h"
#include <omnetpp.h>

#include "cInteger.h"
#include "integer.h"

//! DEBUG alias
/*! 
  An easy-to-use method of inserting debug messages.
  Propegates the message to the simulation output through provided the smart3p::Unit class.
  \sa Adapter(smart3p::Unit* o = NULL), print(char*) and print(char*, CryptoPP::Integer*)
*/
#define DEBUG(x) if (verbose) out->print(x);

namespace smart3p
{
    class Unit;
}

//! Adapter Class 
/*! 
  Abstract Adapter class to convert between types used in the Protocol Implementation and the Simulation.
  Most of the protocol functionality shouldn't occur here, as this is just a method to convert between types as well as pack/unpack packets and messages.
  This is designed to be extended and used by specific Adapters for each pair of classes to be "bridged".
  \sa SMAdapter, UCAdapter and TTPAdapter
 */
class Adapter
{
protected:
    //! Verbose flag
    /*!
      A flag to offer some control over debug and other verbose output.
     */
    bool verbose;

    //! Simulation smart3p::Unit Class
    /*!
      This is a pointer to the Simulation-level abstract smart3p::Unit class which provides debug output.
      Deprecated: Currently is also used as the output for emitting data thereby making its inclusion required. 
      \sa Adapter(smart3p::Unit* o = NULL), print(char*) and print(char*, CryptoPP::Integer*)
     */
    smart3p::Unit* out;
    
public:
    //! Constructor
    /*!
      Constructor for the Adapter.
      \param o Sets the output smart3p::Unit class. Sets the verbose flag to true if not NULL.
     */
    Adapter(smart3p::Unit* o = NULL);
    
    //! Destructor
    virtual ~Adapter();

    //! Simulation string output
    /*!
      Prints the char string to the simulation output. Intended for debugging.
      \sa Adapter(smart3p::Unit* o = NULL), print(char*) and print(char*, CryptoPP::Integer*)
     */
    void print(char*);
    
    //! Simulation CryptoPP::Integer output
    /*!
      Prints the provided CryptoPP::Integer to the simulation output as hex. Prepending the provided char string.
      Intended usage: print("A large number: ", new CryptoPP::Integer(1234566789));
      \sa Adapter(smart3p::Unit* o = NULL), print(char*) and print(char*, CryptoPP::Integer*)
     */
    void print(char*, CryptoPP::Integer*);

    //! Utility function to convert from CryptoPP::Integer to unsigned char array.
    /*!
      Converts CryptoPP::Integer to unsigned char array.
      Use CryptoPP::Integer.ByteCount() to get the size of the array.
      \param i CryptoPP::Integer to convert.
      \return Returns unsigned char array. Use CryptoPP::Integer.ByteCount() to get the size of the array.
      \sa btoi(unsigned char* b, int length) and itobConst(CryptoPP::Integer i)
     */
    static unsigned char* itob(CryptoPP::Integer i) //Cryptopp::Integer to unsigned char array
    {
	unsigned char* output = new unsigned char[i.ByteCount()];
	for (unsigned int j=0;j<i.ByteCount();j++) output[j] = i.GetByte(j);
	return output;
    }

    //! Const variation of itob(CryptoPP::Integer i).
    static const char* itobConst(CryptoPP::Integer i) 
    {
	unsigned char* temp = itob(i);
        const char* output = reinterpret_cast<const char*>(temp);
	
	return output;
    }
    
    //! Utility function to convert from unsigned character array to CryptoPP::Integer.
    /*!
      Converts from unsigned character array to CryptoPP::Integer.
      \param b unsigned char array.
      \param length Total length of the array.
      \return Returns new instance of CryptoPP::Integer.
      \sa itob(CryptoPP::Integer i) and btoi(const char* b, int length)
     */
    static CryptoPP::Integer btoi(unsigned char* b, int length) //unsigned char array to Cryptopp::Integer
    {
	CryptoPP::Integer output = 0;
	for (unsigned int i=0;i<length;i++) output.SetByte(i,int(b[i]));
	return output;
    }
    
    //! Const variation of btoi(unsigned char* b, int length).
    static CryptoPP::Integer btoi(const char* b, int length)
    {
	unsigned char* temp = new unsigned char[length];

	for (int i=0; i<length; i++) temp[i] = b[i];

	return btoi(temp,length);
    }
};

#endif
