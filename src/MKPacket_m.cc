//
// Generated file, do not edit! Created by nedtool 5.0 from MKPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "MKPacket_m.h"

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

Register_Class(MKPacket);

MKPacket::MKPacket(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->id = 0;
    this->value = 0;
    this->smGateID = 0;
    this->collGateID = 0;
    this->pSize = 0;
    this->qSize = 0;
    this->gSize = 0;
    this->xSize = 0;
}

MKPacket::MKPacket(const MKPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

MKPacket::~MKPacket()
{
}

MKPacket& MKPacket::operator=(const MKPacket& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void MKPacket::copy(const MKPacket& other)
{
    this->id = other.id;
    this->value = other.value;
    this->smGateID = other.smGateID;
    this->collGateID = other.collGateID;
    this->pSize = other.pSize;
    this->pBytes = other.pBytes;
    this->qSize = other.qSize;
    this->qBytes = other.qBytes;
    this->gSize = other.gSize;
    this->gBytes = other.gBytes;
    this->xSize = other.xSize;
    this->xBytes = other.xBytes;
}

void MKPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->id);
    doParsimPacking(b,this->value);
    doParsimPacking(b,this->smGateID);
    doParsimPacking(b,this->collGateID);
    doParsimPacking(b,this->pSize);
    doParsimPacking(b,this->pBytes);
    doParsimPacking(b,this->qSize);
    doParsimPacking(b,this->qBytes);
    doParsimPacking(b,this->gSize);
    doParsimPacking(b,this->gBytes);
    doParsimPacking(b,this->xSize);
    doParsimPacking(b,this->xBytes);
}

void MKPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->id);
    doParsimUnpacking(b,this->value);
    doParsimUnpacking(b,this->smGateID);
    doParsimUnpacking(b,this->collGateID);
    doParsimUnpacking(b,this->pSize);
    doParsimUnpacking(b,this->pBytes);
    doParsimUnpacking(b,this->qSize);
    doParsimUnpacking(b,this->qBytes);
    doParsimUnpacking(b,this->gSize);
    doParsimUnpacking(b,this->gBytes);
    doParsimUnpacking(b,this->xSize);
    doParsimUnpacking(b,this->xBytes);
}

int MKPacket::getId() const
{
    return this->id;
}

void MKPacket::setId(int id)
{
    this->id = id;
}

double MKPacket::getValue() const
{
    return this->value;
}

void MKPacket::setValue(double value)
{
    this->value = value;
}

int MKPacket::getSmGateID() const
{
    return this->smGateID;
}

void MKPacket::setSmGateID(int smGateID)
{
    this->smGateID = smGateID;
}

int MKPacket::getCollGateID() const
{
    return this->collGateID;
}

void MKPacket::setCollGateID(int collGateID)
{
    this->collGateID = collGateID;
}

int MKPacket::getPSize() const
{
    return this->pSize;
}

void MKPacket::setPSize(int pSize)
{
    this->pSize = pSize;
}

const char * MKPacket::getPBytes() const
{
    return this->pBytes.c_str();
}

void MKPacket::setPBytes(const char * pBytes)
{
    this->pBytes = pBytes;
}

int MKPacket::getQSize() const
{
    return this->qSize;
}

void MKPacket::setQSize(int qSize)
{
    this->qSize = qSize;
}

const char * MKPacket::getQBytes() const
{
    return this->qBytes.c_str();
}

void MKPacket::setQBytes(const char * qBytes)
{
    this->qBytes = qBytes;
}

int MKPacket::getGSize() const
{
    return this->gSize;
}

void MKPacket::setGSize(int gSize)
{
    this->gSize = gSize;
}

const char * MKPacket::getGBytes() const
{
    return this->gBytes.c_str();
}

void MKPacket::setGBytes(const char * gBytes)
{
    this->gBytes = gBytes;
}

int MKPacket::getXSize() const
{
    return this->xSize;
}

void MKPacket::setXSize(int xSize)
{
    this->xSize = xSize;
}

const char * MKPacket::getXBytes() const
{
    return this->xBytes.c_str();
}

void MKPacket::setXBytes(const char * xBytes)
{
    this->xBytes = xBytes;
}

class MKPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    MKPacketDescriptor();
    virtual ~MKPacketDescriptor();

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

Register_ClassDescriptor(MKPacketDescriptor);

MKPacketDescriptor::MKPacketDescriptor() : omnetpp::cClassDescriptor("smart3p::MKPacket", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

MKPacketDescriptor::~MKPacketDescriptor()
{
    delete[] propertynames;
}

bool MKPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MKPacket *>(obj)!=nullptr;
}

const char **MKPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *MKPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int MKPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 12+basedesc->getFieldCount() : 12;
}

unsigned int MKPacketDescriptor::getFieldTypeFlags(int field) const
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

const char *MKPacketDescriptor::getFieldName(int field) const
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
        "pSize",
        "pBytes",
        "qSize",
        "qBytes",
        "gSize",
        "gBytes",
        "xSize",
        "xBytes",
    };
    return (field>=0 && field<12) ? fieldNames[field] : nullptr;
}

int MKPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+0;
    if (fieldName[0]=='v' && strcmp(fieldName, "value")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "smGateID")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "collGateID")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "pSize")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "pBytes")==0) return base+5;
    if (fieldName[0]=='q' && strcmp(fieldName, "qSize")==0) return base+6;
    if (fieldName[0]=='q' && strcmp(fieldName, "qBytes")==0) return base+7;
    if (fieldName[0]=='g' && strcmp(fieldName, "gSize")==0) return base+8;
    if (fieldName[0]=='g' && strcmp(fieldName, "gBytes")==0) return base+9;
    if (fieldName[0]=='x' && strcmp(fieldName, "xSize")==0) return base+10;
    if (fieldName[0]=='x' && strcmp(fieldName, "xBytes")==0) return base+11;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *MKPacketDescriptor::getFieldTypeString(int field) const
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

const char **MKPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *MKPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int MKPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    MKPacket *pp = (MKPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string MKPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MKPacket *pp = (MKPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getId());
        case 1: return double2string(pp->getValue());
        case 2: return long2string(pp->getSmGateID());
        case 3: return long2string(pp->getCollGateID());
        case 4: return long2string(pp->getPSize());
        case 5: return oppstring2string(pp->getPBytes());
        case 6: return long2string(pp->getQSize());
        case 7: return oppstring2string(pp->getQBytes());
        case 8: return long2string(pp->getGSize());
        case 9: return oppstring2string(pp->getGBytes());
        case 10: return long2string(pp->getXSize());
        case 11: return oppstring2string(pp->getXBytes());
        default: return "";
    }
}

bool MKPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    MKPacket *pp = (MKPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setId(string2long(value)); return true;
        case 1: pp->setValue(string2double(value)); return true;
        case 2: pp->setSmGateID(string2long(value)); return true;
        case 3: pp->setCollGateID(string2long(value)); return true;
        case 4: pp->setPSize(string2long(value)); return true;
        case 5: pp->setPBytes((value)); return true;
        case 6: pp->setQSize(string2long(value)); return true;
        case 7: pp->setQBytes((value)); return true;
        case 8: pp->setGSize(string2long(value)); return true;
        case 9: pp->setGBytes((value)); return true;
        case 10: pp->setXSize(string2long(value)); return true;
        case 11: pp->setXBytes((value)); return true;
        default: return false;
    }
}

const char *MKPacketDescriptor::getFieldStructName(int field) const
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

void *MKPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    MKPacket *pp = (MKPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace smart3p

