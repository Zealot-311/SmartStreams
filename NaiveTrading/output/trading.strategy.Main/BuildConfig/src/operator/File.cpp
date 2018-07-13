// eJx1UEFugzAQ1H4l6hk7JKoqbiQUqQlJKwGHnioXluLK2NbagMjr67RqpRyqPY12ZnZ2nFWRaIX1SEmSS4WlGalBWAMPE8MqiphfLLIdHmY61fOlKD_0P1eM2T3dpkZ7rqF_1dkBY6P_1FNJbfjabm3xyx_1Xtx8qRo6VA_1beGn0qZzrtHtbz4e9uYp5uKWkv_0NQvhRJQs6T1B8AwHozoGO9XtbsVeiokkKz0hOKwWU4oTJ2QO3ZWcgJKxJtkLFWeAHaaLyG78I_1wf3G9_1dY6gN_0Hz3mhAidoUH4sMyCPv8BHBo3wX503gyFDAUJ9R2Wg7GG_1gL_1VwwMQIFtSYY6O2WE38TA_0Rfp5HM_1




#include "./File.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>


#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR File_Base
#define MY_OPERATOR File$OP


#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <signal.h>


#include <streams_boost/iostreams/stream.hpp>
#include <streams_boost/iostreams/filtering_streambuf.hpp>
#include <streams_boost/iostreams/device/file_descriptor.hpp>


#include <SPL/Runtime/Common/ApplicationRuntimeMessage.h>
#include <SPL/Toolkit/IOHelper.h>
#include <SPL/Toolkit/RuntimeException.h>

#include <SPL/Runtime/Operator/OperatorMetrics.h>
#include <SPL/Runtime/Utility/LogTraceMessage.h>

using namespace std;
using namespace streams_boost::iostreams;

#define DEV_NULL "/dev/null"


// defines for error checking conditions
#define CHECK_FAIL      \
    if (failedRead)                                   \
        _numInvalidTuples.incrementValueNoLock()

    #define DO_ERROR(msg)                             \
        do { \
         \
          _numInvalidTuples.incrementValueNoLock();   \
          SPLTRACEMSGANDTHROW(SPLRuntimeFileSourceOperator, L_ERROR, msg, SPL_OPER_DBG);  \
         \
        } while (0)
    #define DO_ERROR_FILESOURCE(msg) DO_ERROR(msg)
    #define CHECK_ERROR(msg)                          \
        if (fs.fail() && !getPE().getShutdownRequested()) \
            DO_ERROR(msg)


string MY_OPERATOR_SCOPE::MY_OPERATOR::makeAbsolute(const string & fileName)
{
    namespace bf = streams_boost::filesystem;
    bf::path file(fileName);
    if (!file.is_absolute()) {
        // getDataDirectory will throw an exception if there is no data directory
        file = getPE().getDataDirectory();
        file /= fileName;
    }
    return file.string();
}


MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
    : MY_BASE_OPERATOR(), _fd(-1),
         
         
        
        
        
	
	  _fd_src(),
	
	_filt_str(),
	_fs(),
        
        _numFilesOpenedMetric(getContext().getMetrics().getCustomMetricByName("nFilesOpened")),
        _numInvalidTuples(getContext().getMetrics().getCustomMetricByName("nInvalidTuples"))
        
        ,_position(0)
        
	,_reset(false)
	,_initialized(false)
        
{
    _numFilesOpenedMetric.setValueNoLock(0);
    _numInvalidTuples.setValueNoLock(0);
    

       try {
           SPLAPPTRC(L_DEBUG, "Register tag data for governance", SPL_OPER_DBG);
           std::map<string,string> props;
           props["inputOperatorType"]="FileSource";
           namespace bf = streams_boost::filesystem;
           bf::path absPath(makeAbsolute(lit$0));
           props["srcName"]=absPath.filename().string();
           props["srcType"]="data_file";
           props["p1srcName"]=absPath.parent_path().string();
           props["srcParent"]="p1";
           props["p1parentType"]="parent_folder_or_host";
           props["p1srcType"]="data_file_folder";
           props["registerType"] = "input";
          setTagData("OperatorIGC", props);
     } catch (std::exception const & e) {
         SPLAPPTRC(L_DEBUG, "Exception received when registering tag data: " << e.what(), SPL_OPER_DBG);
     }
    
}



void MY_OPERATOR_SCOPE::MY_OPERATOR::prepareToShutdown()
{
    if (_fd >= 0) {
        ::close(_fd);
        _fd = -1;
    }
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::initialize()
{
    
     
}



void MY_OPERATOR_SCOPE::MY_OPERATOR::punctAndStatus(const string& pathName)
{
  SPLAPPTRC(L_DEBUG, "punctAndStatus", SPL_OPER_DBG);
  

  
      submit (Punctuation::WindowMarker, 0);
  
  
  
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::processOneFile (const string& path)
{
    SPL::BeJwrMUwzLSjKTE4FABALANU tuple$;
    
         
    namespace bf = streams_boost::filesystem;
    bf::path absPath(path);
    if (!absPath.is_absolute()) {
        absPath = getPE().getDataDirectory();
        absPath /= path;
    }
    string pathName = absPath.string();
    SPLAPPTRC(L_DEBUG, "Using '" << pathName << "' as the workload file...", SPL_OPER_DBG);

    int fd = ::open (pathName.c_str(), O_RDONLY | O_LARGEFILE);
    if (fd < 0) {
        
        
        SPLLOGMSG(L_ERROR, SPL_APPLICATION_RUNTIME_FAILED_OPEN_INPUT_FILE(pathName, RuntimeUtility::getErrorNoStr()), SPL_OPER_DBG);
        SPLTRACEMSGANDTHROW(SPLRuntimeFileSourceOperator, L_ERROR, SPL_APPLICATION_RUNTIME_FAILED_OPEN_INPUT_FILE(pathName, RuntimeUtility::getErrorNoStr()), SPL_OPER_DBG);
    }
    SPLAPPTRC(L_DEBUG, "File opened.", SPL_OPER_DBG);
    
    
 	_fd_src.reset(new file_descriptor_source(fd, close_handle));
	file_descriptor_source& fd_src = *_fd_src;
    
    _numFilesOpenedMetric.incrementValueNoLock();
    _filt_str.reset(new filtering_streambuf<input>);
    filtering_streambuf<input>& filt_str = *_filt_str;
    
    
    filt_str.push (fd_src);
    
	_fs.reset (new istream(&filt_str));
	istream& fs = *_fs;
    
    fs.imbue(locale::classic());

    _fd = fd;
    _tupleNumber = 0; 






bool failedRead = false;
if (getPE().getShutdownRequested()) SPLAPPTRC(L_DEBUG, "shutdown requested", SPL_OPER_DBG);
while(!getPE().getShutdownRequested()) {
   

  


    _tupleNumber++;
  
    if (SPL::safePeek(fs) == EOF) {
      SPLAPPTRC(L_DEBUG, "Break at safePeek(fs) == EOF", SPL_OPER_DBG);
      break;
    }
  

    bool doSubmit = true;
    try {
        
            // ignore comments and empty lines
            fs >> SPL::skipSpaceTabReturnNewLines;
            while (fs.peek() == '#') {
                std::string dummy;
                std::getline (fs, dummy);
                fs >> SPL::skipSpaceTabReturnNewLines;
            }
            
              if (SPL::safePeek(fs)==EOF) break;
            
            failedRead = false;
            



                
                    SPL::readCSV<SPL::float32,','>(fs, tuple$.get_price());
                    
                CHECK_ERROR (SPL_APPLICATION_RUNTIME_FAILED_READ_TUPLE("tuple<float32 price>", _tupleNumber));
                CHECK_FAIL;
                
                 
                    // Check that we read a complete line

                    int eolSep = fs.get();
		    if (eolSep == EOF) {
		      
                    }
                    else if (eolSep != '\n' && eolSep != '\r') {
                        
                        DO_ERROR (SPL_APPLICATION_RUNTIME_FAILED_READ_CHAR ("\\n", SPL::printableCharacter(eolSep), _tupleNumber, "after reading the attribute price"));
		    } 
                
            
        



    } catch (const SPLRuntimeException& e) {
        // Add the filename & tuple number
        DO_ERROR_FILESOURCE(
            SPL_APPLICATION_RUNTIME_FILE_SOURCE_SINK_FILENAME_TUPLE(_tupleNumber, pathName, e.getExplanation()));

    } catch (const std::exception& e) {
        DO_ERROR(SPL_APPLICATION_RUNTIME_EXCEPTION(e.what()));
        _numInvalidTuples.incrementValueNoLock();
        doSubmit = false;
    } catch (...) {
        DO_ERROR(SPL_APPLICATION_RUNTIME_UNKNOWN_EXCEPTION);
        _numInvalidTuples.incrementValueNoLock();
        doSubmit = false;
    }
    if (doSubmit) {
      
        submit (tuple$, 0);
        SPLAPPTRC(L_DEBUG, "Submitted tuple " << _tupleNumber, SPL_OPER_DBG);
      
    }
  

}



    punctAndStatus(pathName);


    if (_fd < 0) {
        // We closed it already.  Prevent an error message
        int newFd = ::open (DEV_NULL, O_RDONLY);
        ::dup2 (newFd, _fd);
        ::close(newFd);
    }
    _fd = -1; // no longer using this

    _fs.reset();
    
    _fd_src.reset();
    
    _filt_str.reset();


}


void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t) 
{
    SPLAPPTRC(L_DEBUG, "FileSource startup...", SPL_OPER_DBG);
    initialize();


        processOneFile (lit$0);




    SPLAPPTRC(L_DEBUG, "FileSource exiting...", SPL_OPER_DBG);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady()
{
    createThreads (1);
}








static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("File",&initer));
    return true;
}

template<class T> static void initRTC (SPL::Operator& o, T& v, const char * n) {
    SPL::ValueHandle vh = v;
    o.getContext().getRuntimeConstantValue(vh, n);
}

MY_BASE_OPERATOR::MY_BASE_OPERATOR()
 : Operator() {
    uint32_t index = getIndex();
    initRTC(*this, lit$0, "lit$0");
    addParameterValue ("file", SPL::ConstValueHandle(lit$0));
    param$format$0 = "csv";
    addParameterValue ("format", SPL::ConstValueHandle(param$format$0));
    (void) getParameters(); // ensure thread safety by initializing here
}
MY_BASE_OPERATOR::~MY_BASE_OPERATOR()
{
    for (ParameterMapType::const_iterator it = paramValues_.begin(); it != paramValues_.end(); it++) {
        const ParameterValueListType& pvl = it->second;
        for (ParameterValueListType::const_iterator it2 = pvl.begin(); it2 != pvl.end(); it2++) {
            delete *it2;
        }
    }
}



void MY_BASE_OPERATOR::checkpointStateVariables(NetworkByteBuffer & opstate) const {
}

void MY_BASE_OPERATOR::restoreStateVariables(NetworkByteBuffer & opstate) {
}

void MY_BASE_OPERATOR::checkpointStateVariables(Checkpoint & ckpt) {
}

void MY_BASE_OPERATOR::resetStateVariables(Checkpoint & ckpt) {
}

void MY_BASE_OPERATOR::resetStateVariablesToInitialState() {
}

bool MY_BASE_OPERATOR::hasStateVariables() const {
    return false;
}

void MY_BASE_OPERATOR::resetToInitialStateRaw() {
    AutoMutex $apm($svMutex);
    StateHandler *sh = getContext().getStateHandler();
    if (sh != NULL) {
        sh->resetToInitialState();
    }
    resetStateVariablesToInitialState();
}

void MY_BASE_OPERATOR::checkpointRaw(Checkpoint & ckpt) {
    AutoMutex $apm($svMutex);
    StateHandler *sh = getContext().getStateHandler();
    if (sh != NULL) {
        sh->checkpoint(ckpt);
    }
    checkpointStateVariables(ckpt);
}

void MY_BASE_OPERATOR::resetRaw(Checkpoint & ckpt) {
    AutoMutex $apm($svMutex);
    StateHandler *sh = getContext().getStateHandler();
    if (sh != NULL) {
        sh->reset(ckpt);
    }
    resetStateVariables(ckpt);
}


