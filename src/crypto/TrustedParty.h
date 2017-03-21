#ifndef __SMIMP_TRUSTEDPARTY_H_
#define __SMIMP_TRUSTEDPARTY_H_

#include "examples.h"
#include "Requester.h"

class TTPAdapter;

namespace SMImp {

class TrustedParty : public Requester
{
private:
    void init();

    bool verbose;
    TTPAdapter* out;
    
    List<List<Integer> >* SMList;
    
    char* message;
    int messageBytesRecieved;
    
public:
    TrustedParty(Integer);
    TrustedParty(Integer,TTPAdapter*);
    virtual ~TrustedParty();
    
    char* getMessage();
	
    void registerSM(int);
    void addDataToSM(int,Integer*);
    List<Integer>* getSM(int id);
    List<Integer>* getRandomSM();
    Iterator<List<Integer> >* getSMIterator();
	
    Packet confirmSession(Integer,Integer,Key);

    Integer recieveData(Integer length, Integer c1, Integer c2, Integer id, Integer timeStamp);
    bool recieveHMAC(Integer length, Integer c1, Integer c2, Integer id, Key smKey, Integer r);
    
};

};

#endif
