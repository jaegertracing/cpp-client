/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Dependency_H
#define Dependency_H

#include <thrift/TDispatchProcessor.h>
#include "dependency_types.h"

namespace jaegertracing { namespace thrift {

class DependencyIf {
 public:
  virtual ~DependencyIf() {}
  virtual void getDependenciesForTrace(Dependencies& _return, const std::string& traceId) = 0;
  virtual void saveDependencies(const Dependencies& dependencies) = 0;
};

class DependencyIfFactory {
 public:
  typedef DependencyIf Handler;

  virtual ~DependencyIfFactory() {}

  virtual DependencyIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(DependencyIf* /* handler */) = 0;
};

class DependencyIfSingletonFactory : virtual public DependencyIfFactory {
 public:
  DependencyIfSingletonFactory(const boost::shared_ptr<DependencyIf>& iface) : iface_(iface) {}
  virtual ~DependencyIfSingletonFactory() {}

  virtual DependencyIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(DependencyIf* /* handler */) {}

 protected:
  boost::shared_ptr<DependencyIf> iface_;
};

class DependencyNull : virtual public DependencyIf {
 public:
  virtual ~DependencyNull() {}
  void getDependenciesForTrace(Dependencies& /* _return */, const std::string& /* traceId */) {
    return;
  }
  void saveDependencies(const Dependencies& /* dependencies */) {
    return;
  }
};


class Dependency_getDependenciesForTrace_args {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

  Dependency_getDependenciesForTrace_args(const Dependency_getDependenciesForTrace_args&);
  Dependency_getDependenciesForTrace_args& operator=(const Dependency_getDependenciesForTrace_args&);
  Dependency_getDependenciesForTrace_args() : traceId() {
  }

  virtual ~Dependency_getDependenciesForTrace_args() throw();
  std::string traceId;

  void __set_traceId(const std::string& val);

  bool operator == (const Dependency_getDependenciesForTrace_args & rhs) const
  {
    if (!(traceId == rhs.traceId))
      return false;
    return true;
  }
  bool operator != (const Dependency_getDependenciesForTrace_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Dependency_getDependenciesForTrace_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const Dependency_getDependenciesForTrace_args& obj);
};


class Dependency_getDependenciesForTrace_pargs {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};


  virtual ~Dependency_getDependenciesForTrace_pargs() throw();
  const std::string* traceId;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const Dependency_getDependenciesForTrace_pargs& obj);
};

typedef struct _Dependency_getDependenciesForTrace_result__isset {
  _Dependency_getDependenciesForTrace_result__isset() : success(false) {}
  bool success :1;
} _Dependency_getDependenciesForTrace_result__isset;

class Dependency_getDependenciesForTrace_result {
 public:

  static const char* ascii_fingerprint; // = "2FD0AAACF989C5BB020BD559E1DD111E";
  static const uint8_t binary_fingerprint[16]; // = {0x2F,0xD0,0xAA,0xAC,0xF9,0x89,0xC5,0xBB,0x02,0x0B,0xD5,0x59,0xE1,0xDD,0x11,0x1E};

  Dependency_getDependenciesForTrace_result(const Dependency_getDependenciesForTrace_result&);
  Dependency_getDependenciesForTrace_result& operator=(const Dependency_getDependenciesForTrace_result&);
  Dependency_getDependenciesForTrace_result() {
  }

  virtual ~Dependency_getDependenciesForTrace_result() throw();
  Dependencies success;

  _Dependency_getDependenciesForTrace_result__isset __isset;

  void __set_success(const Dependencies& val);

  bool operator == (const Dependency_getDependenciesForTrace_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Dependency_getDependenciesForTrace_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Dependency_getDependenciesForTrace_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const Dependency_getDependenciesForTrace_result& obj);
};

typedef struct _Dependency_getDependenciesForTrace_presult__isset {
  _Dependency_getDependenciesForTrace_presult__isset() : success(false) {}
  bool success :1;
} _Dependency_getDependenciesForTrace_presult__isset;

class Dependency_getDependenciesForTrace_presult {
 public:

  static const char* ascii_fingerprint; // = "2FD0AAACF989C5BB020BD559E1DD111E";
  static const uint8_t binary_fingerprint[16]; // = {0x2F,0xD0,0xAA,0xAC,0xF9,0x89,0xC5,0xBB,0x02,0x0B,0xD5,0x59,0xE1,0xDD,0x11,0x1E};


  virtual ~Dependency_getDependenciesForTrace_presult() throw();
  Dependencies* success;

  _Dependency_getDependenciesForTrace_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const Dependency_getDependenciesForTrace_presult& obj);
};

typedef struct _Dependency_saveDependencies_args__isset {
  _Dependency_saveDependencies_args__isset() : dependencies(false) {}
  bool dependencies :1;
} _Dependency_saveDependencies_args__isset;

class Dependency_saveDependencies_args {
 public:

  static const char* ascii_fingerprint; // = "1A1CA83CD19B491397D2DC6C82B8DFC0";
  static const uint8_t binary_fingerprint[16]; // = {0x1A,0x1C,0xA8,0x3C,0xD1,0x9B,0x49,0x13,0x97,0xD2,0xDC,0x6C,0x82,0xB8,0xDF,0xC0};

  Dependency_saveDependencies_args(const Dependency_saveDependencies_args&);
  Dependency_saveDependencies_args& operator=(const Dependency_saveDependencies_args&);
  Dependency_saveDependencies_args() {
  }

  virtual ~Dependency_saveDependencies_args() throw();
  Dependencies dependencies;

  _Dependency_saveDependencies_args__isset __isset;

  void __set_dependencies(const Dependencies& val);

  bool operator == (const Dependency_saveDependencies_args & rhs) const
  {
    if (!(dependencies == rhs.dependencies))
      return false;
    return true;
  }
  bool operator != (const Dependency_saveDependencies_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Dependency_saveDependencies_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const Dependency_saveDependencies_args& obj);
};


class Dependency_saveDependencies_pargs {
 public:

  static const char* ascii_fingerprint; // = "1A1CA83CD19B491397D2DC6C82B8DFC0";
  static const uint8_t binary_fingerprint[16]; // = {0x1A,0x1C,0xA8,0x3C,0xD1,0x9B,0x49,0x13,0x97,0xD2,0xDC,0x6C,0x82,0xB8,0xDF,0xC0};


  virtual ~Dependency_saveDependencies_pargs() throw();
  const Dependencies* dependencies;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const Dependency_saveDependencies_pargs& obj);
};

class DependencyClient : virtual public DependencyIf {
 public:
  DependencyClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  DependencyClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void getDependenciesForTrace(Dependencies& _return, const std::string& traceId);
  void send_getDependenciesForTrace(const std::string& traceId);
  void recv_getDependenciesForTrace(Dependencies& _return);
  void saveDependencies(const Dependencies& dependencies);
  void send_saveDependencies(const Dependencies& dependencies);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class DependencyProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<DependencyIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (DependencyProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_getDependenciesForTrace(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_saveDependencies(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  DependencyProcessor(boost::shared_ptr<DependencyIf> iface) :
    iface_(iface) {
    processMap_["getDependenciesForTrace"] = &DependencyProcessor::process_getDependenciesForTrace;
    processMap_["saveDependencies"] = &DependencyProcessor::process_saveDependencies;
  }

  virtual ~DependencyProcessor() {}
};

class DependencyProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  DependencyProcessorFactory(const ::boost::shared_ptr< DependencyIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< DependencyIfFactory > handlerFactory_;
};

class DependencyMultiface : virtual public DependencyIf {
 public:
  DependencyMultiface(std::vector<boost::shared_ptr<DependencyIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~DependencyMultiface() {}
 protected:
  std::vector<boost::shared_ptr<DependencyIf> > ifaces_;
  DependencyMultiface() {}
  void add(boost::shared_ptr<DependencyIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void getDependenciesForTrace(Dependencies& _return, const std::string& traceId) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getDependenciesForTrace(_return, traceId);
    }
    ifaces_[i]->getDependenciesForTrace(_return, traceId);
    return;
  }

  void saveDependencies(const Dependencies& dependencies) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->saveDependencies(dependencies);
    }
    ifaces_[i]->saveDependencies(dependencies);
  }

};

}} // namespace

#endif
