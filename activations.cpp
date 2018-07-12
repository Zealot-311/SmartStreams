#include <stdexcept>
#include <math.h>
using namespace SPL;

const float 
template <typename T>
class relu
{
public:
	relu();
	~relu();
	void init(string name = "relu"){
		this.name = name;
		this.params = SPL::map<T,T>();
		this.grads = SPL::map<T,T>();
		this.meta = NULL;
		this.grads[this.name] = NULL;
	};
	SPL::list<T> forward(T feat){
		T output = NULL;
		output = util_max(feat, 0);
		this.meta = feat;
		return output;
	};

	SPL::list<T> backward(T dprev){
		feat = this.meta;
		try {
			if (feat == NULL){
				throw 1;
			};
		};
		catch(1){
			cout << "No forward function called before for this module!";
		};
		dfeat = NULL;
		feat = this.meta;
		//TODO: maybe take this out??
		feat = util_div(util_max(feat,0), feat);
		dfeat = util_mult(dprev, feat);
		this.meta = NULL;
		return dfeat;
	};
};

class sigmoid
{
public:
	sigmoid();
	~sigmoid();
	void init(string name = "sigmoid"){
		this.name = name;
		this.params = SPL::map<T,T>();
		this.grads = SPL::map<T,T>();
		this.meta = NULL;
		this.grads[this.name] = NULL;
	};
	SPL::list<T> forward(T feat){
		T output = NULL;
		output = util_sigmoid(feat);
		this.meta = feat;
		return output;
	};
	SPL::list<T> forward(T dprev){
		feat = this.meta;
		try {
			if (feat == NULL){
				throw 1;
			};
		};
		catch(1){
			cout << "No forward function called before for this module!";
		};
		dfeat = NULL;
		feat = this.meta;
		feat = util_div(util_sigmoid(feat), feat);
		dfeat = util_mult(dprev, feat);
		this.meta = NULL;
		return dfeat;
	};
};