#include "Requester.h"
#include "UtilityCompany.h"

namespace SMImp {

Requester::Requester(Integer i)
{
    static SHA1* shaone = new SHA1();
    init(i,shaone);
}
    
Requester::Requester(Integer i, SHA1* s)
{
    init(i,s);
}

Requester::~Requester()
{
}

void Requester::init(Integer i, SHA1* s)
{
    id = i;
    shaone = s;
    rng = new NonblockingRng();    
}
    
Integer Requester::getPublicMu()
{
    return keys.pub.piece;
}

Integer Requester::getPublicPartial()
{
    return keys.pub.partial;
}

Key Requester::getPublicKey()
{
    return keys.pub;
}

Integer Requester::getId()
{
    return id;
}

bool Requester::getPartials(Integer i, Payload pl)
{
    //Payload pl = uc->generatePartialKeys(id);

    //std::cout << "Authenticating request" << std::endl;
    //Verify
    //std::cout << "sm_verify_gen_keys ";
    //start = std::chrono::high_resolution_clock::now();

    Integer hOne = concatAndHash(shaone,i,pl.pub);

    //PP R · y H 1 (id R ,PP R )
    Integer* rightTemp = new Integer(ModularExponentiation(pl.params.x,hOne,pl.params.p));

    Integer* leftTemp = new Integer(pl.pub % pl.params.p);

    Integer* right = new Integer(((*rightTemp)*(*leftTemp)) % pl.params.p);

    Integer* left = new Integer(ModularExponentiation(pl.params.g,pl.priv,pl.params.p));
/*
    std::cout << "Left: " << *left << " Right:" << *right << std::endl;
    std::cout << "These " << (((*left) == (*right)) ? "match!" : "do not match!") << std::endl;
*/
    bool verify = (left->Compare(*right) == 0);

    delete rightTemp;
    delete leftTemp;
    delete right;
    delete left;
    
    if (verify)
    {
	params = pl.params;
	keys.priv.partial = pl.priv;
	keys.pub.partial = pl.pub;
    }
    
    return verify;
}

bool Requester::generateKeys(Payload pl)
{
    if (!getPartials(id,pl)) return false;
    keys.priv.piece = Integer(*rng,1,params.q);
    keys.pub.piece = ModularExponentiation(params.g, keys.priv.piece, params.p);
    return true;
    //std::cout << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << " " <<  params.q.ByteCount() + params.x.ByteCount() + params.p.ByteCount() + params.g.ByteCount() + keys.priv.partial.ByteCount() + keys.priv.piece.ByteCount() + keys.pub.partial.ByteCount() + keys.pub.piece.ByteCount() << std::endl;
}

};
