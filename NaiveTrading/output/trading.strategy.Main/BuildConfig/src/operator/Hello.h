// eJydjz1vwkAMhuW_1gjrfXcKAlI20kVD5UKUkA6PVmOQq4jtdTFD66wkEFiaEvNjD_07yPJWBluVadBBSqhyTJ79sWLUMEZpwIZkppGTzplL7PYVu6_103_0ty6yxU4_069O6dF1exn26TFdZXXnVzG450I1rqdMND5HeI6vCIuuxgLDtvqino_1Mtsegd2p6KSUVXKAjsmKZqA9a7IB8G8p9NkrwkAC2EyQBi8MH_0EhyODmUew_0NRsHw9r3z3Hv_0ZbJ7ZZoRfAFdfG1p
/* Additional includes go here */


#ifndef SPL_OPER_INSTANCE_HELLO_H_
#define SPL_OPER_INSTANCE_HELLO_H_

#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/ParameterValue.h>
#include <SPL/Runtime/Operator/OperatorContext.h>
#include <SPL/Runtime/Operator/OperatorMetrics.h>
#include <SPL/Runtime/Operator/Port/AutoPortMutex.h>
#include <SPL/Runtime/Operator/State/StateHandler.h>
#include <SPL/Runtime/ProcessingElement/PE.h>
#include <SPL/Runtime/Type/SPLType.h>
#include <SPL/Runtime/Utility/CV.h>
using namespace UTILS_NAMESPACE;

#include "../type/BeJwrMUozLSjKTE7NtCguKUosSU2vBABHEgdp.h"

#include <bitset>

#define MY_OPERATOR Hello$OP
#define MY_BASE_OPERATOR Hello_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMUozLSjKTE7NtCguKUosSU2vBABHEgdp IPort0Type;
    typedef SPL::BeJwrMUozLSjKTE7NtCguKUosSU2vBABHEgdp OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    inline void tupleLogic(Tuple & tuple, uint32_t port);
    void processRaw(Tuple & tuple, uint32_t port);
    
    inline void punctLogic(Punctuation const & punct, uint32_t port);
    void processRaw(Punctuation const & punct, uint32_t port);
    void punctPermitProcessRaw(Punctuation const & punct, uint32_t port);
    void punctNoPermitProcessRaw(Punctuation const & punct, uint32_t port);
    
    inline void submit(Tuple & tuple, uint32_t port)
    {
        Operator::submit(tuple, port);
    }
    inline void submit(Punctuation const & punct, uint32_t port)
    {
        Operator::submit(punct, port);
    }
    
    
    
    
    
protected:
    Mutex $svMutex;
    typedef std::bitset<2> OPortBitsetType;
    OPortBitsetType $oportBitset;
    Mutex $fpMutex;
    void checkpointStateVariables(NetworkByteBuffer & opstate) const;
    void restoreStateVariables(NetworkByteBuffer & opstate);
    void checkpointStateVariables(Checkpoint & ckpt);
    void resetStateVariables(Checkpoint & ckpt);
    void resetStateVariablesToInitialState();
    bool hasStateVariables() const;
    void resetToInitialStateRaw();
    void checkpointRaw(Checkpoint & ckpt);
    void resetRaw(Checkpoint & ckpt);
private:
    static bool globalInit_;
    static bool globalIniter();
    ParameterMapType paramValues_;
    ParameterMapType& getParameters() { return paramValues_;}
    void addParameterValue(std::string const & param, ConstValueHandle const& value)
    {
        ParameterMapType::iterator it = paramValues_.find(param);
        if (it == paramValues_.end())
            it = paramValues_.insert (std::make_pair (param, ParameterValueListType())).first;
        it->second.push_back(&ParameterValue::create(value));
    }
    void addParameterValue(std::string const & param)
    {
        ParameterMapType::iterator it = paramValues_.find(param);
        if (it == paramValues_.end())
            it = paramValues_.insert (std::make_pair (param, ParameterValueListType())).first;
        it->second.push_back(&ParameterValue::create());
    }
};


class MY_OPERATOR : public MY_BASE_OPERATOR 
{
public:
  // Constructor
  MY_OPERATOR();

  // Destructor
  virtual ~MY_OPERATOR(); 

  // Notify port readiness
  void allPortsReady(); 

  // Notify pending shutdown
  void prepareToShutdown(); 

  // Processing for source and threaded operators   
  void process(uint32_t idx);
    
  // Tuple processing for mutating ports 
  void process(Tuple & tuple, uint32_t port);
    
  // Tuple processing for non-mutating ports
  void process(Tuple const & tuple, uint32_t port);

  // Punctuation processing
  void process(Punctuation const & punct, uint32_t port);
private:
  // Members
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_HELLO_H_


