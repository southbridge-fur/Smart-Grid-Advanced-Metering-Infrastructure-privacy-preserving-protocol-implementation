//
// Generated file, do not edit! Created by nedtool 5.0 from KPPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "KPPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace smart3p {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(KPPacket);

KPPacket::KPPacket(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->id = 0;
    this->value = 0;
    this->smGateID = 0;
    this->collGateID = 0;
    this->privatePieceSize = 0;
    this->privatePartialSize = 0;
    this->publicPieceSize = 0;
    this->publicPartialSize = 0;
}

KPPacket::KPPacket(const KPPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

KPPacket::~KPPacket()
{
}

KPPacket& KPPacket::operator=(const KPPacket& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void KPPacket::copy(const KPPacket& other)
{
    this->id = other.id;
    this->value = other.value;
    this->smGateID = other.smGateID;
    this->collGateID = other.collGateID;
    this->privatePieceSize = other.privatePieceSize;
    this->privatePieceBytes = other.privatePieceBytes;
    this->privatePartialSize = other.privatePartialSize;
    this->privatePartialBytes = other.privatePartialBytes;
    this->publicPieceSize = other.publicPieceSize;
    this->publicPieceBytes = other.publicPieceBytes;
    this->publicPartialSize = other.publicPartialSize;
    this->publicPartialBytes = other.publicPartialBytes;
}

void KPPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->id);
    doParsimPacking(b,this->value);
    doParsimPacking(b,this->smGateID);
    doParsimPacking(b,this->collGateID);
    doParsimPacking(b,this->privatePieceSize);
    doParsimPacking(b,this->privatePieceBytes);
    doParsimPacking(b,this->privatePartialSize);
    doParsimPacking(b,this->privatePartialBytes);
    doParsimPacking(b,this->publicPieceSize);
    doParsimPacking(b,this->publicPieceBytes);
    doParsimPacking(b,this->publicPartialSize);
    doParsimPacking(b,this->publicPartialBytes);
}

void KPPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->id);
    doParsimUnpacking(b,this->value);
    doParsimUnpacking(b,this->smGateID);
    doParsimUnpacking(b,this->collGateID);
    doParsimUnpacking(b,this->privatePieceSize);
    doParsimUnpacking(b,this->privatePieceBytes);
    doParsimUnpacking(b,this->privatePartialSize);
    doParsimUnpacking(b,this->privatePartialBytes);
    doParsimUnpacking(b,this->publicPieceSize);
    doParsimUnpacking(b,this->publicPieceBytes);
    doParsimUnpacking(b,this->publicPartialSize);
    doParsimUnpacking(b,this->publicPartialBytes);
}

int KPPacket::getId() const
{
    return this->id;
}

void KPPacket::setId(int id)
{
    this->id = id;
}

double KPPacket::getValue() const
{
    return this->value;
}

void KPPacket::setValue(double value)
{
    this->value = value;
}

int KPPacket::getSmGateID() const
{
    return this->smGateID;
}

void KPPacket::setSmGateID(int smGateID)
{
    this->smGateID = smGateID;
}

int KPPacket::getCollGateID() const
{
    return this->collGateID;
}

void KPPacket::setCollGateID(int collGateID)
{
    this->collGateID = collGateID;
}

int KPPacket::getPrivatePieceSize() const
{
    return this->privatePieceSize;
}

void KPPacket::setPrivatePieceSize(int privatePieceSize)
{
    this->privatePieceSize = privatePieceSize;
}

const char * KPPacket::getPrivatePieceBytes() const
{
    return this->privatePieceBytes.c_str();
}

void KPPacket::setPrivatePieceBytes(const char * privatePieceBytes)
{
    this->privatePieceBytes = privatePieceBytes;
}

int KPPacket::getPrivatePartialSize() const
{
    return this->privatePartialSize;
}

void KPPacket::setPrivatePartialSize(int privatePartialSize)
{
    this->privatePartialSize = privatePartialSize;
}

const char * KPPacket::getPrivatePartialBytes() const
{
    return this->privatePartialBytes.c_str();
}

void KPPacket::setPrivatePartialBytes(const char * privatePartialBytes)
{
    this->privatePartialBytes = privatePartialBytes;
}

int KPPacket::getPublicPieceSize() const
{
    return this->publicPieceSize;
}

void KPPacket::setPublicPieceSize(int publicPieceSize)
{
    this->publicPieceSize = publicPieceSize;
}

const char * KPPacket::getPublicPieceBytes() const
{
    return this->publicPieceBytes.c_str();
}

void KPPacket::setPublicPieceBytes(const char * publicPieceBytes)
{
    this->publicPieceBytes = publicPieceBytes;
}

int KPPacket::getPublicPartialSize() const
{
    return this->publicPartialSize;
}

void KPPacket::setPublicPartialSize(int publicPartialSize)
{
    this->publicPartialSize = publicPartialSize;
}

const char * KPPacket::getPublicPartialBytes() const
{
    return this->publicPartialBytes.c_str();
}

void KPPacket::setPublicPartialBytes(const char * publicPartialBytes)
{
    this->publicPartialBytes = publicPartialBytes;
}

class KPPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    KPPacketDescriptor();
    virtual ~KPPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(KPPacketDescriptor);

KPPacketDescriptor::KPPacketDescriptor() : omnetpp::cClassDescriptor("smart3p::KPPacket", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

KPPacketDescriptor::~KPPacketDescriptor()
{
    delete[] propertynames;
}

bool KPPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<KPPacket *>(obj)!=nullptr;
}

const char **KPPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *KPPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int KPPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 12+basedesc->getFieldCount() : 12;
}

unsigned int KPPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<12) ? fieldTypeFlags[field] : 0;
}

const char *KPPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "id",
        "value",
        "smGateID",
        "collGateID",
        "privatePieceSize",
        "privatePieceBytes",
        "privatePartialSize",
        "privatePartialBytes",
        "publicPieceSize",
        "publicPieceBytes",
        "publicPartialSize",
        "publicPartialBytes",
    };
    return (field>=0 && field<12) ? fieldNames[field] : nullptr;
}

int KPPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='v' && strcmp(fieldName, "value")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "smGateID")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "collGateID")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "privatePieceSize")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "privatePieceBytes")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "privatePartialSize")==0) return base+6;
    if (fieldName[0]=='p' && strcmp(fieldName, "privatePartialBytes")==0) return base+7;
    if (fieldName[0]=='p' && strcmp(fieldName, "publicPieceSize")==0) return base+8;
    if (fieldName[0]=='p' && strcmp(fieldName, "publicPieceBytes")==0) return base+9;
    if (fieldName[0]=='p' && strcmp(fieldName, "publicPartialSize")==0) return base+10;
    if (fieldName[0]=='p' && strcmp(fieldName, "publicPartialBytes")==0) return base+11;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *KPPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
        "int",
        "int",
        "int",
        "string",
        "int",
        "string",
        "int",
        "string",
        "int",
        "string",
    };
    return (field>=0 && field<12) ? fieldTypeStrings[field] : nullptr;
}

const char **KPPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *KPPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int KPPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    KPPacket *pp = (KPPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string KPPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    KPPacket *pp = (KPPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getId());
        case 1: return double2string(pp->getValue());
        case 2: return long2string(pp->getSmGateID());
        case 3: return long2string(pp->getCollGateID());
        case 4: return long2string(pp->getPrivatePieceSize());
        case 5: return oppstring2string(pp->getPrivatePieceBytes());
        case 6: return long2string(pp->getPrivatePartialSize());
        case 7: return oppstring2string(pp->getPrivatePartialBytes());
        case 8: return long2string(pp->getPublicPieceSize());
        case 9: return oppstring2string(pp->getPublicPieceBytes());
        case 10: return long2string(pp->getPublicPartialSize());
        case 11: return oppstring2string(pp->getPublicPartialBytes());
        default: return "";
    }
}

bool KPPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    KPPacket *pp = (KPPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setId(string2long(value)); return true;
        case 1: pp->setValue(string2double(value)); return true;
        case 2: pp->setSmGateID(string2long(value)); return true;
        case 3: pp->setCollGateID(string2long(value)); return true;
        case 4: pp->setPrivatePieceSize(string2long(value)); return true;
        case 5: pp->setPrivatePieceBytes((value)); return true;
        case 6: pp->setPrivatePartialSize(string2long(value)); return true;
        case 7: pp->setPrivatePartialBytes((value)); return true;
        case 8: pp->setPublicPieceSize(string2long(value)); return true;
        case 9: pp->setPublicPieceBytes((value)); return true;
        case 10: pp->setPublicPartialSize(string2long(value)); return true;
        case 11: pp->setPublicPartialBytes((value)); return true;
        default: return false;
    }
}

const char *KPPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *KPPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    KPPacket *pp = (KPPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace smart3p

