// eJydjz1vwkAMhuW_1gjrfXcKAlI20kVD5UKUkA6PVmOQq4jtdTFD66wkEFiaEvNjD_07yPJWBluVadBBSqhyTJ79sWLUMEZpwIZkppGTzplL7PYVu6_103_0ty6yxU4_069O6dF1exn26TFdZXXnVzG450I1rqdMND5HeI6vCIuuxgLDtvqino_1Mtsegd2p6KSUVXKAjsmKZqA9a7IB8G8p9NkrwkAC2EyQBi8MH_0EhyODmUew_0NRsHw9r3z3Hv_0ZbJ7ZZoRfAFdfG1p
/* Additional includes go here */


#include "./Hello.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>

#include <string>

#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR Hello_Base
#define MY_OPERATOR Hello$OP


// Constructor
MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
{
    // Initialization code goes here
}

// Destructor
MY_OPERATOR_SCOPE::MY_OPERATOR::~MY_OPERATOR() 
{
    // Finalization code goes here
}

// Notify port readiness
void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady() 
{
    // Notifies that all ports are ready. No tuples should be submitted before
    // this. Source operators can use this method to spawn threads.

    /*
      createThreads(1); // Create source thread
    */
}
 
// Notify pending shutdown
void MY_OPERATOR_SCOPE::MY_OPERATOR::prepareToShutdown() 
{
    // This is an asynchronous call
}

// Processing for source and threaded operators   
void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t idx)
{
    // A typical implementation will loop until shutdown
    /*
      while(!getPE().getShutdownRequested()) {
          // do work ...
      }
    */
}

// Tuple processing for mutating ports 
void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple & tuple, uint32_t port)
{
    // Sample submit code
    /* 
      submit(otuple, 0); // submit to output port 0
    */
	int batch_size = 40;
	
	float32 curr = tuple.getAttributeValue("price");
	
	ifstream ifs("history.txt");
	std::vector<float32> history;
	int now;
	
	ifs>>now;
	for(int i = 1; i < batch_size; i++) {
		ifs>>now;
		
		history.push_back(now);
	}
	
	history.push_back(curr);
	float32 diff = 0;
	
	for(int i = batich_size - 1; i > 1; i--){
		diff += i*(history[i] - history[i-1]);
	}
	
	ofstream ofs("history.txt");
	for(int i = 0; i < batch_size; i++) {
		ofs<<history[i];
	}
	
	int32 purchase = -1;
	if(diff > 0) {
		purchase = 1;
	}
	
	OPort0Type otuple;
	ValueHandle handle0 = otuple.getAttributeValue("strategy");
	
	int32 & strategy = handle0;
	strategy = purchase;
	submit(otuple, 0);
}

// Tuple processing for non-mutating ports
void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple const & tuple, uint32_t port)
{
    // Sample submit code
    /* 
      OPort0Type otuple;
      submit(otuple, 0); // submit to output port 0
    */
}

// Punctuation processing
void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Punctuation const & punct, uint32_t port)
{
    /*
      if(punct==Punctuation::WindowMarker) {
        // ...;
      } else if(punct==Punctuation::FinalMarker) {
        // ...;
      }
    */
}

static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("Hello",&initer));
    return true;
}

template<class T> static void initRTC (SPL::Operator& o, T& v, const char * n) {
    SPL::ValueHandle vh = v;
    o.getContext().getRuntimeConstantValue(vh, n);
}

MY_BASE_OPERATOR::MY_BASE_OPERATOR()
 : Operator() {
    uint32_t index = getIndex();
    (void) getParameters(); // ensure thread safety by initializing here
    $oportBitset = OPortBitsetType(std::string("01"));
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

void MY_BASE_OPERATOR::tupleLogic(Tuple & tuple, uint32_t port) {
}


void MY_BASE_OPERATOR::processRaw(Tuple & tuple, uint32_t port) {
    tupleLogic (tuple, port);
    static_cast<MY_OPERATOR_SCOPE::MY_OPERATOR*>(this)->MY_OPERATOR::process(tuple, port);
}


void MY_BASE_OPERATOR::punctLogic(Punctuation const & punct, uint32_t port) {
}

void MY_BASE_OPERATOR::punctPermitProcessRaw(Punctuation const & punct, uint32_t port) {
    {
        punctNoPermitProcessRaw(punct, port);
    }
}

void MY_BASE_OPERATOR::punctNoPermitProcessRaw(Punctuation const & punct, uint32_t port) {
    switch(punct) {
    case Punctuation::WindowMarker:
        punctLogic(punct, port);
        process(punct, port);
        break;
    case Punctuation::FinalMarker:
        punctLogic(punct, port);
        
        if (punct == Punctuation::FinalMarker) {
            process(punct, port);
            bool forward = false;
            {
                AutoPortMutex $apm($fpMutex, *this);
                $oportBitset.reset(port);
                if ($oportBitset.none()) {
                    $oportBitset.set(1);
                    forward=true;
                }
            }
            if(forward)
                submit(punct, 0);
            return;
        }
        process(punct, port);
        break;
    case Punctuation::DrainMarker:
    case Punctuation::ResetMarker:
    case Punctuation::ResumeMarker:
        break;
    case Punctuation::SwitchMarker:
        break;
    default:
        break;
    }
}

void MY_BASE_OPERATOR::processRaw(Punctuation const & punct, uint32_t port) {
    switch(port) {
    case 0:
        punctNoPermitProcessRaw(punct, port);
        break;
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



