#ifndef __SMIMP_REQUESTER_H_
#define __SMIMP_REQUESTER_H_

#include "examples.h"

namespace SMImp {

class Requester
{
private:
    void init(Integer, SHA1*);
    
public:
    KeyPair keys;
    MasterKey params;
    NonblockingRng* rng;
    Integer id;
    SHA1* shaone;

    Integer mu;
    Integer R;
    Integer sessionKey;
    bool getPartials(Integer, Payload);
    
    Requester(Integer, SHA1*);
    Requester(Integer);
    ~Requester();

    Integer getId();
    bool generateKeys(Payload);
    Key getPublicKey();
    Integer getPublicPartial();
    Integer getPublicMu();

};

};

#endif
