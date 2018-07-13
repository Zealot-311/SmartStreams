// eJytUF1rwjAU5f4TkT0ojMYOkVHGwG0KUyuDdg_1uRWK92qxpUpLo6n790mgdZQNhjLzcezkn50MX3FPIqWFSUB4EY8YNKvChZ58Pbc8j5lAgecDJhwqj7GZ6y8PPrG_0m72_0TKCons3hRHJJyvl7Nn2dhfzcNizDevg7LwSgcLn0vbbuPODNXPYheZkHAmTZ3blLaKCa2rXsAIKnMUZNUHHyyoMKLGRUkMgpprp9wj1wWOQpD5pTtMVZ0bYlkTQ0FIQVWEpvauvt7JSVHKuwaBO4w3omkSqmD4FFyjvWSUt1x7q5brJDKDt4WzdKwJEPV6XZhVBYKtbZoV8sJdFT5ay3AQLmKAfpwlIJTG2BD4XkxLP9eqM4KxRKEDZfUDPrOj_1w3Pz_0c_0HWZ9eGcvlFR0_1EFUoW1lEauizp5Rfkl_1YlWH5q0Gt_1p2pq_0AHbLOxT




#ifndef SPL_OPER_INSTANCE_TRADEQUOTESFILTERED_H_
#define SPL_OPER_INSTANCE_TRADEQUOTESFILTERED_H_

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

#include "../type/BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1.h"

#include <bitset>

#define MY_OPERATOR TradeQuotesFiltered$OP
#define MY_BASE_OPERATOR TradeQuotesFiltered_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1 IPort0Type;
    typedef SPL::BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1 OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    inline void tupleLogic(Tuple const & tuple, uint32_t port);
    void processRaw(Tuple const & tuple, uint32_t port);
    
    inline void punctLogic(Punctuation const & punct, uint32_t port);
    void processRaw(Punctuation const & punct, uint32_t port);
    void punctPermitProcessRaw(Punctuation const & punct, uint32_t port);
    void punctNoPermitProcessRaw(Punctuation const & punct, uint32_t port);
    
    
    
    SPL::list<SPL::rstring > lit$0;
    
    
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
   MY_OPERATOR() {}
  
   void process(Tuple const & tuple, uint32_t port);
   void process(Punctuation const & punct, uint32_t port);
   
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_TRADEQUOTESFILTERED_H_

