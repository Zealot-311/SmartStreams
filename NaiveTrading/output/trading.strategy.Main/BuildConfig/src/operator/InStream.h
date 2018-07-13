// eJydkslOwzAQhjXXPoWFOLQSytYKUBEHWjjQLAI5FZQLMo1JTRM7ciZtU8S74zTsnMA_0WPNr1m9cFplVocgE1sPhuCpR5eCCY64He5ZlY11we8Qnax3SpecfZ_0F2OUD_16W5C6WYSxLOinm_0i5CG6DMJB5YdFGKfTs83hRXh271qLvZ9JbmfbgD758cVRhOO08qeqpFNvlZyHKyrcYEsxGl2Pb9ZrPWqiHeiD6W3fAXoVDIdCYt_0DneK2ymOmGB4OWs1rterNDeyFynlpL2Tt2jMmrVgwaVPUnOXlOV_1xTBU5l2hHTKx4rFkiZGonDBlIJXkDoUEhCqU_1OvgvCshB77A_0d4g5iSLP5EvCP2AhyPOCnP4zuvs2jZVyvGflstBizru9A7Kj3D5u74SU1UMukHSbYq3qGfWFrBci412nd9J56QAMAMV8yTXoErWBBwYe_1zBQ5J_1Gey1431iDVv1G_04dZdkz78D2tA6ag6SKtof0GDmizall9cTGlXwEl5fAJ


#ifndef SPL_OPER_INSTANCE_INSTREAM_H_
#define SPL_OPER_INSTANCE_INSTREAM_H_

#include <SPL/Runtime/Serialization/NetworkByteBuffer.h>
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
#include "../type/BeJwrMXYzLSjKTE7NtCguKUosSU2vdDMvSi1LzStNBQCWwwrB.h"

#include <bitset>

#define MY_OPERATOR InStream$OP
#define MY_BASE_OPERATOR InStream_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1 IPort0Type;
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
    
    
    
    SPL::int32 lit$0;
    SPL::float64 lit$1;
    SPL::uint32 lit$2;
    
    
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
   
   
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_INSTREAM_H_

