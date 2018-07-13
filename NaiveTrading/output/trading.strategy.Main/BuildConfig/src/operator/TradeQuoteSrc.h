// eJydUctugzAQ1P5K1DM2KYoibjQpUgDTSpBDeokcWBKXhy1jQsjX12mVKr1WexqtZnZmtleNw0uuDGrfD0WDmRx0geACtTOHmeMQMykkLxiNmmX1PF427Fp7Jv78iLLsEiX5Tk3FJS0P6SZh3hAzxfLjNrgsXlmwd53T7I_1IpNMNfc6FN7BpoeJ1_0Db14zUvdJQvvflUdCwbt0G1d8doJW9kar00wjxRyN4T39e90aI7AgA5yRZ7cuoml_0x45_0SCdyQzGnnbr_1GMjVQtdoakXJwx17y0NFJyw6GTHd7CVTavVf_0jez8WGIsPg8FQI0IldcuNXa4tP_1wBFIr_0DKuhN7JNhC2QN99mKUgl9a_1h_1xYHLWjwwIiiRg13exRsAnyARrSPkPe10sI_0sGokNwsPKP0CFwyaB9



#ifndef SPL_OPER_INSTANCE_TRADEQUOTESRC_H_
#define SPL_OPER_INSTANCE_TRADEQUOTESRC_H_

#include <streams_boost/iostreams/stream.hpp>
#include <streams_boost/iostreams/filtering_streambuf.hpp>
#include <streams_boost/iostreams/device/file_descriptor.hpp>
#include <SPL/Runtime/Common/Metric.h>
#include <streams_boost/filesystem/path.hpp>
#include <SPL/Runtime/Operator/State/StateHandler.h>
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
#include "../type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h"


#define MY_OPERATOR TradeQuoteSrc$OP
#define MY_BASE_OPERATOR TradeQuoteSrc_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMSk2K8lMzk4tKjZJSSxJLTYpycxNdbNILM4uKMpMTgUAx6EMA_1 OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    
    inline void submit(Tuple & tuple, uint32_t port)
    {
        Operator::submit(tuple, port);
    }
    inline void submit(Punctuation const & punct, uint32_t port)
    {
        Operator::submit(punct, port);
    }
    
    
    
    SPL::rstring lit$0;
    
    
protected:
    Mutex $svMutex;
    SPL::rstring param$format$0;
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
    MY_OPERATOR();
    
    
        virtual void process(uint32_t index);
        virtual void allPortsReady();
    

    virtual void prepareToShutdown();

    

private:
    void initialize();
    std::string makeAbsolute(const std::string & path);
    inline void punctAndStatus(const std::string& pathName);
    void processOneFile (const std::string& pathName);
    
    

    int32_t _fd;
    uint64_t _tupleNumber;
    
    
    
    
    
    
        std::auto_ptr<streams_boost::iostreams::file_descriptor_source> _fd_src;
    
    std::auto_ptr<streams_boost::iostreams::filtering_streambuf<streams_boost::iostreams::input> > _filt_str;
    
        std::auto_ptr<std::istream> _fs;
    
    
    Metric& _numFilesOpenedMetric;
    Metric& _numInvalidTuples;

    
    std::streamoff _position;
    
    bool _reset; 
    // When FileSource is a start operator, this indicates
    // whether the file has been opened yet.
    bool _initialized;

    
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_TRADEQUOTESRC_H_


