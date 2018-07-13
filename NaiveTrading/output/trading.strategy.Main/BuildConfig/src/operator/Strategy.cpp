// eJzFkN9Lw0AMgMm_1Mny_0H91Q6GM3X1xblOvQPQYb2xvrXblmLd1fb_0cmwnwSH0YIhATyfQkHLK2rRMcBmaoxjs2lytA60KCm0DATQvLYkkzoaQjZ2_1aYmt26eHzIeVkd1hvfmU3Ul6usN1anR8N58rJ8HYaQiHr2tQNk7RvqZO1GLbfoRGHRyQlG2HQr6mnv24YcyxxtT8VZS5bICM47Oq2IprStD3ynwDyncfxnGWggnG1gDm2w7wQfe498v4DvB4B1PI8gTEbu8DPWF7K_0AVmB_1_1_1V11R1zVW_1yOrU1J_18Aavs
/* Additional includes go here */


#include "./Strategy.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>

#include <string>

#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR Strategy_Base
#define MY_OPERATOR Strategy$OP


#include <fstream>

using namespace std;

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
	
	float64 curr = tuple.getAttributeValue("price");
	
	ifstream ifs("history.txt");
	std::vector<float64> history;
	int now;
	
	ifs>>now;
	for(int i = 1; i < batch_size; i++) {
		ifs>>now;
		history.push_back(now);
	}
	
	history.push_back(curr);
	float64 diff = 0;
	
	for(int i = batch_size - 1; i > 1; i--){
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
	otuple.assignFrom(tuple, false);
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
    instantiators_.insert(std::make_pair("Strategy",&initer));
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
    $oportBitset = OPortBitsetType(std::string("011"));
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
    switch(port) {
    }
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
                    $oportBitset.set(2);
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
    case 1:
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



