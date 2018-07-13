// eJzFkN9Lw0AMgMm_1Mny_0H91Q6GM3X1xblOvQPQYb2xvrXblmLd1fb_0cmwnwSH0YIhATyfQkHLK2rRMcBmaoxjs2lytA60KCm0DATQvLYkkzoaQjZ2_1aYmt26eHzIeVkd1hvfmU3Ul6usN1anR8N58rJ8HYaQiHr2tQNk7RvqZO1GLbfoRGHRyQlG2HQr6mnv24YcyxxtT8VZS5bICM47Oq2IprStD3ynwDyncfxnGWggnG1gDm2w7wQfe498v4DvB4B1PI8gTEbu8DPWF7K_0AVmB_1_1_1V11R1zVW_1yOrU1J_18Aavs
/* Additional includes go here */


#ifndef SPL_OPER_INSTANCE_STRATEGY_H_
#define SPL_OPER_INSTANCE_STRATEGY_H_

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

#include "../type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.h"

#include <bitset>

#define MY_OPERATOR Strategy$OP
#define MY_BASE_OPERATOR Strategy_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB IPort0Type;
    typedef SPL::BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB IPort1Type;
    typedef SPL::BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB OPort0Type;
    
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
    typedef std::bitset<3> OPortBitsetType;
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
#endif // SPL_OPER_INSTANCE_STRATEGY_H_


