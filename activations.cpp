#include <stdexcept>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

template <typename T>
class relu
{
public:
	relu();
	~relu();
	std::string name;
	std::map<T,T> params;
	std::map<T,T> grads;
	std::vector<T> meta;

	void init(std::string name = "relu"){
		name = name;
		params = NULL;
		grads = NULL;
		meta = NULL;
		grads[name] = NULL;
	};
	std::vector<T> forward(T feat){
		T output = NULL;
		output = util_max(feat, 0);
		meta = feat;
		return output;
	};

	std::vector<T> backward(T dprev){
		std::vector<T> feat = meta;
		try {
			if (feat == NULL){
				throw 1;
			};
		}
		catch(int i){
			cout << "No forward function called before for this module!";
		};
		std::vector<T> dfeat = NULL;
		feat = meta;
		//TODO: maybe take this
		feat = util_div(util_max(feat,0), feat);
		dfeat = util_mult(dprev, feat);
		meta = NULL;
		return dfeat;
	};
};
template <typename T>
class sigmoid
{
public:
	sigmoid();
	~sigmoid();

	std::string name;
	std::map<T,T> params;
	std::map<T,T> grads;
	std::vector<T> meta;
	
	void init(string name = "sigmoid"){
		name = name;
		params = NULL;
		grads = NULL;
		meta = NULL;
		grads[name] = NULL;
	};
	std::vector<T> forward(T feat){
		T output = NULL;
		output = util_sigmoid(feat);
		meta = feat;
		return output;
	};
	std::vector<T> backward(T dprev){
		std::vector<T> feat = meta;
		try {
			if (feat == NULL){
				throw 1;
			};
		}
		catch(int i){
			cout << "No forward function called before for this module!";
		};
		std::vector<T> dfeat = NULL;
		feat = meta;
		feat = util_div(util_sigmoid(feat), feat);
		dfeat = util_mult(dprev, feat);
		meta = NULL;
		return dfeat;
	};
};
