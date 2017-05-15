#ifndef __SMIMP_TRUSTEDPARTY_H_
#define __SMIMP_TRUSTEDPARTY_H_

#include "examples.h"
#include "Requester.h"

class TTPAdapter;

namespace SMImp {

    //! Trusted Third Party protocol implementation.
    /*!
      Most variables have been named after their respective names given in the original research paper available [here](https://www.researchgate.net/publication/305077004_Secure_and_efficient_protection_of_consumer_privacy_in_Advanced_Metering_Infrastructure_supporting_fine-grained_data_analysis). See section 5 (Page 7) for the beginning of the protocol implementation.
    */
class TrustedParty : public Requester
{
private:
    void init();
    
    //! Verbose flag, used for debugging
    bool verbose;
    //! Pointer to adapter, only used for debugging
    /*!
      \sa Adapter::print(char*)
     */
    TTPAdapter* out;

    //! List of IDs of available Smart Meters
    /*!
    **Note**: All IDs used for Smart Meter identification are their anonymous IDs since Trusted Third Party only has access to those thereby requiring all anonymous IDs to be unique.
    \sa addDataToSM(int id, Integer* data), getSM(int id), getRandomSM() and getSMIterator().
    */
    List<List<Integer> >* SMList;

    //! Current Message
    /*!
      Since messages can arrive accross multiple packets, this array points to the current message being recieved.
      
      **Currently unused** as the current message per Smart Meter is stored under that Smart Meter's local representation.
      \sa messageBytesRecieved
    */
    char* message;

    //! Message Bytes Recieved
    /*!
      Current count of message bytes recieved.
      \sa message
    */
    int messageBytesRecieved;
    
public:
    TrustedParty(Integer);
    /*!
      For debugging.
    */
    TrustedParty(Integer,TTPAdapter*);
    virtual ~TrustedParty();

    /*!
      Helper function for the Adapter to queuery the current message.
      \return message
      \sa message.
    */
    char* getMessage();

    /*! 
      Adds Smart Meter's id to the SMList.
    */
    void registerSM(int);

    /*!
      Adds arbitrary data to the local Smart Meter representation identified by id.
      \param id ID of the Smart Meter to add data to.
      \param data Data to add to the local Smart Meter representation.
    */
    void addDataToSM(int id, Integer* data);

    /*!
      Gets local Smart Meter representation by ID
      \param id Smart Meter ID to retrieve.
      \return Local Smart Meter representation of arbitrary data.
    */
    List<Integer>* getSM(int id);
    /*!
      Gets a random Smart Meter representation for use with session key exchange.
      \return Local Smart Meter representation of arbitrary data.
    */
    List<Integer>* getRandomSM();
    /*!
      Get an iterator to iterate over all available Smart Meters.
      \return Iterator to iterate with.
    */
    Iterator<List<Integer> >* getSMIterator();

    /*!
      Recieves session key exchange data from Smart Meter.
      \param req Shared secret R for use with future encryption.
      \param smId ID (anonymous) for identifying the Smart Meter (used by getSM(int id)).
      \param smKey Public key of the Smart Meter.
      \return Packet to be sent back to the Smart Meter.
     */
    Packet confirmSession(Integer req,Integer smId, Key smKey);

    /*!
      Finishes the Session Key exchange phase for the Trusted Third Party.
      \param length Total length of the session key. Unlike recieveHMAC(Integer length, Integer c1, Integer c2, Integer id, Key smKey, Integer r) the sum of the lengths of c1 and c2 may be less than the length of the entire session key.
      \param c1 Part 1 of the encrypted Session Key.
      \param c2 Part 2 of the encrypted Session Key.
      \param smId ID (anonymous) of the Smart Meter the Session Key originated from.
      \param smKey Public key of Smart Meter.
      \param r shared-secret used for message verification.
      \return Returns true if session key passed verification, false otherwise.
     */
    bool recieveHMAC(Integer length, Integer c1, Integer c2, Integer smId, Key smKey, Integer r);

    /*!
      Recieve, verify and decrypt energy usage data.
      \param length Length of the message (unused as it is equivalent to the sum of the lengths of c1 and c2)
      \param c1 Part 1 of the encrypted energy usage data.
      \param c2 Part 2 of the encrypted energy usage data.
      \param smId ID (anonymous) of the Smart Meter the data originated from.
      \param timeStamp Timestamp of the data.
      \return -1 if failed to verify. Any other value is the byte-encoded string of the data, see TTPAdapter::processDataFromSM(omnetpp::cMessage* msg)
    */
    Integer recieveData(Integer length, Integer c1, Integer c2, Integer smId, Integer timeStamp);
    
};

};

#endif
