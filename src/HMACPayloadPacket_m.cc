//
// Generated file, do not edit! Created by nedtool 5.0 from HMACPayloadPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "HMACPayloadPacket_m.h"

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

Register_Class(HMACPayloadPacket);

HMACPayloadPacket::HMACPayloadPacket(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->id = 0;
    this->value = 0;
    this->smGateID = 0;
    this->collGateID = 0;
    this->messageLength = 0;
    this->hmacSize = 0;
    this->c1Size = 0;
    this->c21Size = 0;
    this->c22Size = 0;
    this->idSize = 0;
    this->rSize = 0;
    this->timeStampSize = 0;
}

HMACPayloadPacket::HMACPayloadPacket(const HMACPayloadPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

HMACPayloadPacket::~HMACPayloadPacket()
{
}

HMACPayloadPacket& HMACPayloadPacket::operator=(const HMACPayloadPacket& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void HMACPayloadPacket::copy(const HMACPayloadPacket& other)
{
    this->id = other.id;
    this->value = other.value;
    this->smGateID = other.smGateID;
    this->collGateID = other.collGateID;
    this->messageLength = other.messageLength;
    this->hmacSize = other.hmacSize;
    this->hmac = other.hmac;
    this->c1Size = other.c1Size;
    this->c1Bytes = other.c1Bytes;
    this->c21Size = other.c21Size;
    this->c21Bytes = other.c21Bytes;
    this->c22Size = other.c22Size;
    this->c22Bytes = other.c22Bytes;
    this->idSize = other.idSize;
    this->idBytes = other.idBytes;
    this->rSize = other.rSize;
    this->rBytes = other.rBytes;
    this->timeStampSize = other.timeStampSize;
    this->timeStampBytes = other.timeStampBytes;
}

void HMACPayloadPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->id);
    doParsimPacking(b,this->value);
    doParsimPacking(b,this->smGateID);
    doParsimPacking(b,this->collGateID);
    doParsimPacking(b,this->messageLength);
    doParsimPacking(b,this->hmacSize);
    doParsimPacking(b,this->hmac);
    doParsimPacking(b,this->c1Size);
    doParsimPacking(b,this->c1Bytes);
    doParsimPacking(b,this->c21Size);
    doParsimPacking(b,this->c21Bytes);
    doParsimPacking(b,this->c22Size);
    doParsimPacking(b,this->c22Bytes);
    doParsimPacking(b,this->idSize);
    doParsimPacking(b,this->idBytes);
    doParsimPacking(b,this->rSize);
    doParsimPacking(b,this->rBytes);
    doParsimPacking(b,this->timeStampSize);
    doParsimPacking(b,this->timeStampBytes);
}

void HMACPayloadPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->id);
    doParsimUnpacking(b,this->value);
    doParsimUnpacking(b,this->smGateID);
    doParsimUnpacking(b,this->collGateID);
    doParsimUnpacking(b,this->messageLength);
    doParsimUnpacking(b,this->hmacSize);
    doParsimUnpacking(b,this->hmac);
    doParsimUnpacking(b,this->c1Size);
    doParsimUnpacking(b,this->c1Bytes);
    doParsimUnpacking(b,this->c21Size);
    doParsimUnpacking(b,this->c21Bytes);
    doParsimUnpacking(b,this->c22Size);
    doParsimUnpacking(b,this->c22Bytes);
    doParsimUnpacking(b,this->idSize);
    doParsimUnpacking(b,this->idBytes);
    doParsimUnpacking(b,this->rSize);
    doParsimUnpacking(b,this->rBytes);
    doParsimUnpacking(b,this->timeStampSize);
    doParsimUnpacking(b,this->timeStampBytes);
}

int HMACPayloadPacket::getId() const
{
    return this->id;
}

void HMACPayloadPacket::setId(int id)
{
    this->id = id;
}

double HMACPayloadPacket::getValue() const
{
    return this->value;
}

void HMACPayloadPacket::setValue(double value)
{
    this->value = value;
}

int HMACPayloadPacket::getSmGateID() const
{
    return this->smGateID;
}

void HMACPayloadPacket::setSmGateID(int smGateID)
{
    this->smGateID = smGateID;
}

int HMACPayloadPacket::getCollGateID() const
{
    return this->collGateID;
}

void HMACPayloadPacket::setCollGateID(int collGateID)
{
    this->collGateID = collGateID;
}

int HMACPayloadPacket::getMessageLength() const
{
    return this->messageLength;
}

void HMACPayloadPacket::setMessageLength(int messageLength)
{
    this->messageLength = messageLength;
}

int HMACPayloadPacket::getHmacSize() const
{
    return this->hmacSize;
}

void HMACPayloadPacket::setHmacSize(int hmacSize)
{
    this->hmacSize = hmacSize;
}

const char * HMACPayloadPacket::getHmac() const
{
    return this->hmac.c_str();
}

void HMACPayloadPacket::setHmac(const char * hmac)
{
    this->hmac = hmac;
}

int HMACPayloadPacket::getC1Size() const
{
    return this->c1Size;
}

void HMACPayloadPacket::setC1Size(int c1Size)
{
    this->c1Size = c1Size;
}

const char * HMACPayloadPacket::getC1Bytes() const
{
    return this->c1Bytes.c_str();
}

void HMACPayloadPacket::setC1Bytes(const char * c1Bytes)
{
    this->c1Bytes = c1Bytes;
}

int HMACPayloadPacket::getC21Size() const
{
    return this->c21Size;
}

void HMACPayloadPacket::setC21Size(int c21Size)
{
    this->c21Size = c21Size;
}

const char * HMACPayloadPacket::getC21Bytes() const
{
    return this->c21Bytes.c_str();
}

void HMACPayloadPacket::setC21Bytes(const char * c21Bytes)
{
    this->c21Bytes = c21Bytes;
}

int HMACPayloadPacket::getC22Size() const
{
    return this->c22Size;
}

void HMACPayloadPacket::setC22Size(int c22Size)
{
    this->c22Size = c22Size;
}

const char * HMACPayloadPacket::getC22Bytes() const
{
    return this->c22Bytes.c_str();
}

void HMACPayloadPacket::setC22Bytes(const char * c22Bytes)
{
    this->c22Bytes = c22Bytes;
}

int HMACPayloadPacket::getIdSize() const
{
    return this->idSize;
}

void HMACPayloadPacket::setIdSize(int idSize)
{
    this->idSize = idSize;
}

const char * HMACPayloadPacket::getIdBytes() const
{
    return this->idBytes.c_str();
}

void HMACPayloadPacket::setIdBytes(const char * idBytes)
{
    this->idBytes = idBytes;
}

int HMACPayloadPacket::getRSize() const
{
    return this->rSize;
}

void HMACPayloadPacket::setRSize(int rSize)
{
    this->rSize = rSize;
}

const char * HMACPayloadPacket::getRBytes() const
{
    return this->rBytes.c_str();
}

void HMACPayloadPacket::setRBytes(const char * rBytes)
{
    this->rBytes = rBytes;
}

int HMACPayloadPacket::getTimeStampSize() const
{
    return this->timeStampSize;
}

void HMACPayloadPacket::setTimeStampSize(int timeStampSize)
{
    this->timeStampSize = timeStampSize;
}

const char * HMACPayloadPacket::getTimeStampBytes() const
{
    return this->timeStampBytes.c_str();
}

void HMACPayloadPacket::setTimeStampBytes(const char * timeStampBytes)
{
    this->timeStampBytes = timeStampBytes;
}

class HMACPayloadPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    HMACPayloadPacketDescriptor();
    virtual ~HMACPayloadPacketDescriptor();

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

Register_ClassDescriptor(HMACPayloadPacketDescriptor);

HMACPayloadPacketDescriptor::HMACPayloadPacketDescriptor() : omnetpp::cClassDescriptor("smart3p::HMACPayloadPacket", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

HMACPayloadPacketDescriptor::~HMACPayloadPacketDescriptor()
{
    delete[] propertynames;
}

bool HMACPayloadPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HMACPayloadPacket *>(obj)!=nullptr;
}

const char **HMACPayloadPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *HMACPayloadPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int HMACPayloadPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 19+basedesc->getFieldCount() : 19;
}

unsigned int HMACPayloadPacketDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<19) ? fieldTypeFlags[field] : 0;
}

const char *HMACPayloadPacketDescriptor::getFieldName(int field) const
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
        "messageLength",
        "hmacSize",
        "hmac",
        "c1Size",
        "c1Bytes",
        "c21Size",
        "c21Bytes",
        "c22Size",
        "c22Bytes",
        "idSize",
        "idBytes",
        "rSize",
        "rBytes",
        "timeStampSize",
        "timeStampBytes",
    };
    return (field>=0 && field<19) ? fieldNames[field] : nullptr;
}

int HMACPayloadPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='v' && strcmp(fieldName, "value")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "smGateID")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "collGateID")==0) return base+3;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageLength")==0) return base+4;
    if (fieldName[0]=='h' && strcmp(fieldName, "hmacSize")==0) return base+5;
    if (fieldName[0]=='h' && strcmp(fieldName, "hmac")==0) return base+6;
    if (fieldName[0]=='c' && strcmp(fieldName, "c1Size")==0) return base+7;
    if (fieldName[0]=='c' && strcmp(fieldName, "c1Bytes")==0) return base+8;
    if (fieldName[0]=='c' && strcmp(fieldName, "c21Size")==0) return base+9;
    if (fieldName[0]=='c' && strcmp(fieldName, "c21Bytes")==0) return base+10;
    if (fieldName[0]=='c' && strcmp(fieldName, "c22Size")==0) return base+11;
    if (fieldName[0]=='c' && strcmp(fieldName, "c22Bytes")==0) return base+12;
    if (fieldName[0]=='i' && strcmp(fieldName, "idSize")==0) return base+13;
    if (fieldName[0]=='i' && strcmp(fieldName, "idBytes")==0) return base+14;
    if (fieldName[0]=='r' && strcmp(fieldName, "rSize")==0) return base+15;
    if (fieldName[0]=='r' && strcmp(fieldName, "rBytes")==0) return base+16;
    if (fieldName[0]=='t' && strcmp(fieldName, "timeStampSize")==0) return base+17;
    if (fieldName[0]=='t' && strcmp(fieldName, "timeStampBytes")==0) return base+18;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *HMACPayloadPacketDescriptor::getFieldTypeString(int field) const
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
        "int",
        "string",
        "int",
        "string",
        "int",
        "string",
        "int",
        "string",
        "int",
        "string",
        "int",
        "string",
        "int",
        "string",
    };
    return (field>=0 && field<19) ? fieldTypeStrings[field] : nullptr;
}

const char **HMACPayloadPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *HMACPayloadPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int HMACPayloadPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    HMACPayloadPacket *pp = (HMACPayloadPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string HMACPayloadPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    HMACPayloadPacket *pp = (HMACPayloadPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getId());
        case 1: return double2string(pp->getValue());
        case 2: return long2string(pp->getSmGateID());
        case 3: return long2string(pp->getCollGateID());
        case 4: return long2string(pp->getMessageLength());
        case 5: return long2string(pp->getHmacSize());
        case 6: return oppstring2string(pp->getHmac());
        case 7: return long2string(pp->getC1Size());
        case 8: return oppstring2string(pp->getC1Bytes());
        case 9: return long2string(pp->getC21Size());
        case 10: return oppstring2string(pp->getC21Bytes());
        case 11: return long2string(pp->getC22Size());
        case 12: return oppstring2string(pp->getC22Bytes());
        case 13: return long2string(pp->getIdSize());
        case 14: return oppstring2string(pp->getIdBytes());
        case 15: return long2string(pp->getRSize());
        case 16: return oppstring2string(pp->getRBytes());
        case 17: return long2string(pp->getTimeStampSize());
        case 18: return oppstring2string(pp->getTimeStampBytes());
        default: return "";
    }
}

bool HMACPayloadPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    HMACPayloadPacket *pp = (HMACPayloadPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setId(string2long(value)); return true;
        case 1: pp->setValue(string2double(value)); return true;
        case 2: pp->setSmGateID(string2long(value)); return true;
        case 3: pp->setCollGateID(string2long(value)); return true;
        case 4: pp->setMessageLength(string2long(value)); return true;
        case 5: pp->setHmacSize(string2long(value)); return true;
        case 6: pp->setHmac((value)); return true;
        case 7: pp->setC1Size(string2long(value)); return true;
        case 8: pp->setC1Bytes((value)); return true;
        case 9: pp->setC21Size(string2long(value)); return true;
        case 10: pp->setC21Bytes((value)); return true;
        case 11: pp->setC22Size(string2long(value)); return true;
        case 12: pp->setC22Bytes((value)); return true;
        case 13: pp->setIdSize(string2long(value)); return true;
        case 14: pp->setIdBytes((value)); return true;
        case 15: pp->setRSize(string2long(value)); return true;
        case 16: pp->setRBytes((value)); return true;
        case 17: pp->setTimeStampSize(string2long(value)); return true;
        case 18: pp->setTimeStampBytes((value)); return true;
        default: return false;
    }
}

const char *HMACPayloadPacketDescriptor::getFieldStructName(int field) const
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

void *HMACPayloadPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    HMACPayloadPacket *pp = (HMACPayloadPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace smart3p

