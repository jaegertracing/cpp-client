/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Agent_H
#define Agent_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "agent_types.h"

namespace jaegertracing { namespace agent { namespace thrift {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class AgentIf {
 public:
  virtual ~AgentIf() {}
  virtual void emitBatch(const  ::jaegertracing::thrift::Batch& batch) = 0;
};

class AgentIfFactory {
 public:
  typedef AgentIf Handler;

  virtual ~AgentIfFactory() {}

  virtual AgentIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(AgentIf* /* handler */) = 0;
};

class AgentIfSingletonFactory : virtual public AgentIfFactory {
 public:
  AgentIfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<AgentIf>& iface) : iface_(iface) {}
  virtual ~AgentIfSingletonFactory() {}

  virtual AgentIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(AgentIf* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<AgentIf> iface_;
};

class AgentNull : virtual public AgentIf {
 public:
  virtual ~AgentNull() {}
  void emitBatch(const  ::jaegertracing::thrift::Batch& /* batch */) {
    return;
  }
};

typedef struct _Agent_emitBatch_args__isset {
  _Agent_emitBatch_args__isset() : batch(false) {}
  bool batch :1;
} _Agent_emitBatch_args__isset;

class Agent_emitBatch_args {
 public:

  Agent_emitBatch_args(const Agent_emitBatch_args&);
  Agent_emitBatch_args& operator=(const Agent_emitBatch_args&);
  Agent_emitBatch_args() {
  }

  virtual ~Agent_emitBatch_args() throw();
   ::jaegertracing::thrift::Batch batch;

  _Agent_emitBatch_args__isset __isset;

  void __set_batch(const  ::jaegertracing::thrift::Batch& val);

  bool operator == (const Agent_emitBatch_args & rhs) const
  {
    if (!(batch == rhs.batch))
      return false;
    return true;
  }
  bool operator != (const Agent_emitBatch_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Agent_emitBatch_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Agent_emitBatch_pargs {
 public:


  virtual ~Agent_emitBatch_pargs() throw();
  const  ::jaegertracing::thrift::Batch* batch;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class AgentClient : virtual public AgentIf {
 public:
  AgentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  AgentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void emitBatch(const  ::jaegertracing::thrift::Batch& batch);
  void send_emitBatch(const  ::jaegertracing::thrift::Batch& batch);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class AgentProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<AgentIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (AgentProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_emitBatch(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  AgentProcessor(::apache::thrift::stdcxx::shared_ptr<AgentIf> iface) :
    iface_(iface) {
    processMap_["emitBatch"] = &AgentProcessor::process_emitBatch;
  }

  virtual ~AgentProcessor() {}
};

class AgentProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  AgentProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< AgentIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< AgentIfFactory > handlerFactory_;
};

class AgentMultiface : virtual public AgentIf {
 public:
  AgentMultiface(std::vector<apache::thrift::stdcxx::shared_ptr<AgentIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~AgentMultiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<AgentIf> > ifaces_;
  AgentMultiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<AgentIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void emitBatch(const  ::jaegertracing::thrift::Batch& batch) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->emitBatch(batch);
    }
    ifaces_[i]->emitBatch(batch);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class AgentConcurrentClient : virtual public AgentIf {
 public:
  AgentConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  AgentConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void emitBatch(const  ::jaegertracing::thrift::Batch& batch);
  void send_emitBatch(const  ::jaegertracing::thrift::Batch& batch);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

}}} // namespace

#endif
