#ifndef CINTEGER_H_
#define CINTEGER_H_

#include <integer.h>
#include <omnetpp.h>

//! A hybrid class between omnetpp::cNamedObject and CryptoPP::Integer
/*!
  Designed to allow the passing of CrypoPP::Integer into messages and packets to make implementing adapters easier. 
 */
class cInteger : public omnetpp::cNamedObject, public CryptoPP::Integer
{
private:
    //! Name of the class.
    /*!
      Required by omnetpp::cNamedObject.
     */
    const char* className = "cInteger";
    
    //! Instance name.
    /*!
      Used to identify a particular instance.
      \sa cInteger(const char*), cInteger(const char*, CryptoPP::Integer*), cInteger(const char* n, int i), getName() and setName(const char*).
     */
    const char* name;
    
public:
    //! Constructor
    /*!
      Value is dependant upon the default behavour for CryptoPP::Integer when instantiated without a value. 
      \param n Instance name.
      \sa cInteger(cInteger*), cInteger(const char*, CryptoPP::Integer*) and cInteger(const char* n, int i)
     */
    cInteger(const char* n);
    
    //! Constructor
    /*!
      \param n Instance name.
      \param i copies provided CryptoPP::Integer.
      \sa cInteger(const char* n), cInteger(cInteger*), and cInteger(const char* n, int i)
     */
    cInteger(const char* n, CryptoPP::Integer* i);
    
    //! Constructor
    /*!
      \param n Instance name.
      \param i Value
      \sa cInteger(const char* n), cInteger(cInteger*), and cInteger(const char*, CryptoPP::Integer*)
     */
    cInteger(const char* n, int i);
    
    //! Constructor
    /*!
      Copy constructor.
      \sa cInteger(const char* n), cInteger(const char*, CryptoPP::Integer*) and cInteger(const char* n, int i)
    */
    cInteger(cInteger* i);
    
    //! Destructor
    virtual ~cInteger();

    /*!
      \return Returns className.
      \sa className
    */
    const char* getClassName() const;
    
    /*!
      \return Returns instance name.
      \sa setName(const char*).
     */
    const char* getName() const;
    
    /*!
      Sets the name of the instance.
      \param c const char string to change the name to.
      \sa getName()
    */
    void setName(const char* c);

    //! Duplicate
    /*!
      Provides a duplication of the class (via the copy constructor).
      \return A new copy of this instance.
    */
    cInteger* dup() const;

    /*!
      dynamic casts to a CryptoPP::Integer
     */
    CryptoPP::Integer* toInteger();

    /*!
      Packs the class into an omnetpp::cCommBuffer allowing for parallelization.
      \param buffer The buffer to pack into.
     */
    void parsimPack(omnetpp::cCommBuffer* buffer) const;

    /*!
      Unpacks the class from an omnetpp::cCommBuffer allowing for parallelization.
      \param buffer The buffer to pack from.
    */
    void parsimUnpack(omnetpp::cCommBuffer* buffer);
};

#endif
