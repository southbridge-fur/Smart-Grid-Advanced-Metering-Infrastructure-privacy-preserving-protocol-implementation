#include "TrustedParty.h"
#include "SmartMeter.h"
#include "UtilityCompany.h"

namespace SMImp
{
    
UtilityCompany::UtilityCompany()
{
    rng = new NonblockingRng();

//    meterList = new List<SmartMeter>();
//    thirdPartyList = new List<TrustedParty>();

    SMList = new List<List<Integer> >();
    TTPList = new List<List<Integer> >();
    generateKey(Integer::Power2((8*SHA256::DIGESTSIZE)-1)+1, Integer::Power2(8*SHA256::DIGESTSIZE),1,2);
}

UtilityCompany::~UtilityCompany()
{
    delete rng;
    delete SMList;
    delete TTPList;
}

void UtilityCompany::setMasterKey(Integer p,Integer q,Integer g,Integer x)
{
    masterKey.p = p;
    masterKey.q = q;
    masterKey.g = g;
    masterKey.x = x;
}

/*
void UtilityCompany::setMeter(SmartMeter* m)
{
    Integer anonMeterId = rng->GenerateWord32();
    Integer* SMUCkey = new Integer(rng->GenerateWord32());
    meterList->add(m,m->getId().ConvertToLong());
    hmacKeys->add(SMUCkey,m->getId().ConvertToLong());
    m->setAnonId(anonMeterId);
    m->setHMACKey(*SMUCkey);
    anonIds->add(new Integer(m->getId()),anonMeterId.ConvertToLong());
}
*/
    
/*
void UtilityCompany::setParty(TrustedParty* t)
{
    thirdPartyList->add(t,t->getId().ConvertToLong());
}
*/

void UtilityCompany::registerSM(Integer* id)
{
    List<Integer>* data = new List<Integer>();
    
    SMList->add(data,id->ConvertToLong());
    data->add(id,0);
    data->add(new Integer(id->Plus(10000)),1); //todo, implement anonimization algorithm
    data->add(new Integer(rng->GenerateWord32()),2); //SMUCKey
//    data->add(new Integer(key,2);
//    data->add(new Integer(smGate),2);
//    data->add(new Integer(collGate),3);
}
    
void UtilityCompany::registerTTP(Integer* id)
{
    List<Integer>* data = new List<Integer>();
    
    TTPList->add(data,id->ConvertToLong());

    data->add(id,0);
//    data->add(key,1);
//    data->add(mu,2);
    //may need more
}

void UtilityCompany::addSMData(Integer* id, Integer* data)
{
    List<Integer>* list = SMList->get(id->ConvertToLong());
    list->add(data,list->size());
}
    
void UtilityCompany::addTTPData(Integer* id, Integer* data)
{
    List<Integer>* list = TTPList->get(id->ConvertToLong());
    list->add(data,list->size());
}

int UtilityCompany::getTTPSize(Integer* id)
{
    List<Integer>* list = TTPList->get(id->ConvertToLong());
    return list->size();
}
    
List<Integer>* UtilityCompany::getSMbyAnonId(Integer* id)
{
    Iterator<List<Integer> >* iter = SMList->iterator();
    while (iter->hasNext())
    {
	List<Integer>* curr = iter->next();
	if (id->Compare(Integer(*curr->get(1))) == 0) return curr;
    }
    return NULL;
}

List<Integer>* UtilityCompany::getSM(Integer id)
{
    return SMList->get(id.ConvertToLong());
}

List<Integer>* UtilityCompany::getTTP(Integer id)
{
    return TTPList->get(id.ConvertToLong());
}
/*
SmartMeter* UtilityCompany::getMeter(Integer id)
{
    meterList->get(id.ConvertToLong());
}

TrustedParty* UtilityCompany::getParty(Integer id)
{
    thirdPartyList->get(id.ConvertToLong());
}
*/

// As a one-time operation, UC has to establish the necessary cryptographic
// primitives and its private/public keys. UC generates two primes p and
// q such that q|p − 1. UC picks a generator g of Z ∗ p of order q. UC
// picks uniformly at random x ∈ Z ∗ q as its private key and computes y =
// g x mod p as its public key. UC selects hash functions H 1 : {0, 1} ∗ × Z ∗ p →
// Z ∗ q , H 2 : {0, 1} l 0 × {0, 1} l 1 → Z ∗ q and H 3 : Z ∗ p × Z ∗ p → {0, 1} l , where
// l = l 0 + l 1 ∈ N. UC keeps secret its master key, where masterKey =
// (p, q, g, x, H 1 , H 2 , H 3 ).

// 1) Generate two primes p and q such that (p - 1) is divisable by q. For example, p = 7 and q = 3, (p - 1) == 0 (mod q).
// 2) Pick generator g
// 3) Generate x as an integer of order q and compute y.
// 4) Shoose hashes, H1 and H2 == SHA-256, H3 == SHA-1 (bitwise, string/hex)
// 4.1) l == 160bits,
// 4.2) masterKey stores just p,q,g,x
// 5) Given ID, generate partial keys...

// 2^i for i={1,2,3,4,5}
// 2^i mod 9

// 2,4,5,7,8

bool UtilityCompany::generateKey(Integer q,
				 const Integer & max,
				 const Integer & equiv,
				 const Integer & mod)
{
    pSelector* ps = new pSelector();
    
    //http://www.cryptopp.com/docs/ref/nbtheory_8h.html
    //p is the starting value
    //max is the maximum value
    //equiv is the value which the prime will have once it is mod'ed with the mod parameter

    //this function returns true if x % mod == equiv where x is prime
    //equiv cannot be greater than or equal to mod
    
    //start = std::chrono::high_resolution_clock::now();
    bool first = FirstPrime(q,max,equiv,mod,ps);
//    std::cout << "Time to find first prime (q): " << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
    if (!first) return false;
    
    Integer p = Integer::Power2(2047)+1;
//    start = std::chrono::high_resolution_clock::now();
    bool second = FirstPrime(p,Integer::Power2(2048),1,q,ps);
    //  std::cout << "Time to find second prime (p): " << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
    if (!second) return false;

    //This may be done by setting g = h^((p–1)/q) mod p for some arbitrary h (1 < h < p−1), and trying again with a different h if the result comes out as 1. Most choices of h will lead to a usable g; commonly h=2 is used.
    Integer g = 0;
    Integer h = 2;
    do {g = ModularExponentiation(h++,((p-1)/q),p) ;} while (g == 1 && h < p-1) ;
    if (h == p-1) return false;
    //we have our primes, time to generate keys
    Integer x = Integer(*rng,1,q);
    //Public Key
    Integer y = ModularExponentiation(g, x, p);
    //std::cout << "uc_init " << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
    keys.priv.partial = x;
    keys.pub.partial = y;
    setMasterKey(p,q,g,x);
    return true;
}

Payload UtilityCompany::generatePartialKeys(Integer id)
{
    //std::cout << "uc_gen_keys ";
    //start = std::chrono::high_resolution_clock::now();
    //std::cout << "Generating Partial Keys" << std::endl;
    Integer s = Integer(*rng,1,masterKey.q);
    Integer* partialPublicKey = new Integer(ModularExponentiation(masterKey.g, s, masterKey.p));

    Integer hOne = concatAndHash(new SHA1(),id,*partialPublicKey);
			       
    //for (int i=0;i<5;i++) hOne = (hOne * 4294967296) + temp[i];
    hOne %= masterKey.q;
    hOne *= masterKey.x;
    hOne %= masterKey.q;
    hOne += s;
    hOne %= masterKey.q;
    
    Payload out;

    out.params.p = masterKey.p;
    out.params.q = masterKey.q;
    out.params.g = masterKey.g;
    out.params.x = this->keys.pub.partial;
    out.priv = hOne;
    out.pub = *partialPublicKey;
    //std::cout << std::chrono::duration_cast<std::chrono::duration<long double>>(std::chrono::high_resolution_clock::now() - start).count() << " " << out.params.q.ByteCount() + out.params.x.ByteCount() + out.params.p.ByteCount() + out.params.g.ByteCount() + out.priv.ByteCount() + out.pub.ByteCount() << std::endl;
    return out;
}

bool UtilityCompany::verifyHMAC(Integer key,HMACPayload pl)
{
    Integer HMACOutput = generateHMAC(key,pl);
    
    return HMACOutput.Compare(pl.hmac) == 0;
}

} // end namespace


//no longer required as the adapter will implement these
/*
void UtilityCompany::sendDataToTTP(Integer smId, char* d, Integer l, Integer dest)
{
    Packet data = meterList->get(anonIds->get(smId.ConvertToLong())->ConvertToLong())->sendDataToTTP(d,l,dest);
    ForwardDataToTTP(data.pl,data.dest,data.pl.id);
}
    
//It should be noted currently sessions keys can only be 4 bytes long
void UtilityCompany::sessionKeyExchange(Integer smId, Integer ttpId, char* m, Integer l)
{
    TrustedParty* party = thirdPartyList->get(ttpId.ConvertToLong());
    Packet data = meterList->get(anonIds->get(smId.ConvertToLong())->ConvertToLong())->sessionKeyExchange(m,l,ttpId,party->getPublicPartial(),party->getPublicMu());
    ForwardMessageToTTP(data.pl,data.dest,data.pl.id);
}
    
void UtilityCompany::ForwardDataToTTP(HMACPayload pl, Integer ttpId, Integer smId)
{
    if (verifyHMAC(pl)) thirdPartyList->get(ttpId.ConvertToLong())->recieveData(pl.messageLength, pl.c1, pl.c21, pl.c22,meterList->get(smId.ConvertToLong())->getAnonId());
}

void UtilityCompany::ForwardMessageToTTP(HMACPayload pl, Integer ttpId, Integer smId)
{
    if (verifyHMAC(pl))
    {
	SmartMeter* meter = meterList->get(smId.ConvertToLong());
	TrustedParty* party = thirdPartyList->get(ttpId.ConvertToLong());
	if (party->recieveHMAC(pl.messageLength, pl.c1, pl.c21, pl.c22, meter->getAnonId(), meter->getPublicKey(), pl.r))
	{
	    Packet data = party->confirmSession(pl.r,smId, meter->getPublicKey());
	    ForwardMessageToSM(data.pl,ttpId,meter);
	}
    }
}

void UtilityCompany::ForwardMessageToSM(HMACPayload pl, Integer ttpId, SmartMeter* meter)
{
    if (verifyHMAC(pl)) meter->recieveHMAC(pl.c1, pl.c21, pl.c22,ttpId);
}

void UtilityCompany::ForwardMessageToSM(HMACPayload pl, Integer ttpId, Integer smId)
{
    ForwardMessageToSM(pl,ttpId,meterList->get(anonIds->get(smId.ConvertToLong())->ConvertToLong()));
}

};
*/
