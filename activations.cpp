#include <stdexcept>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;
template <typename T>
class fc
{
public:
	fc();
	~fc();
	std::string name;
	std::string w_name;
	std::string b_name;
	int input_dim;
	int output_dim;
	std::map<T,T> params;
	std::map<T,T> grads;
	std::vector<T> meta;
	void init(std::string name = "FC", int input_dim = 0, int output_dim = 0, float init_scale = 0){
		name = name;
		w_name = name + "_w";
		b_name = name + "_b";
		input_dim = input_dim;
		output_dim = output_dim;
		params.insert(std::pair<std::string, std::vector<T> >(w_name, util_scalar_mult(init_scale, util_random_matrix(input_dim, output_dim))));
		params.insert(std::pair<std::string, std::vector<T> >(b_name, util_scalar_mult(init_scale, util_zero_matrix(output_dim))));
		grads.insert(std::pair<std::string, std::vector<T> >(w_name, NULL));
		grads.insert(std::pair<std::string, std::vector<T> >(b_name, NULL));
		meta = NULL;
	}

	std::vector<T> forward(std::vector<T> feat){
		std::vector<T> output = NULL;
		try{
			if(input_dim != feat[0].size()){
				throw(1);
			}
		} catch(int i){
			cout << "specified input dimension does not match actual input dimension";
		}
		output = util_add(util_mult(util_reshape(feat,1,input_dim), params[w_name]));
		meta = feat;
		return output;
	}

	std::vector<T> backward(std::vector<T> dprev){
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
		grads.insert(std::pair<std::string, std::vector<T> >(w_name, NULL));
		grads.insert(std::pair<std::string, std::vector<T> >(b_name, NULL));
		grads.insert(std::pair<std::string, std::vector<T> >(b_name, util_sum(dprev, 0)));
		dfeat = util_mult(dprev, util_reshape(util_transpose(params[w_name]), meta.size(), meta[0].size()));
		grads.insert(std::pair<std::string, std::vector<T> >(w_name, util_mult(util_transpose(util_reshape(feat, 1, input_dim)),dprev)));
		meta = NULL;
		return dfeat;
	};

};
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
	std::vector<T> forward(std::vector<T> feat){
		std::vector<T> output = NULL;
		output = util_max(feat, 0);
		meta = feat;
		return output;
	};

	std::vector<T> backward(std::vector<T> dprev){
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
		return dfeat.data;
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
	std::vector<T> forward(std::vector<T> feat){
		std::vector<T> output = NULL;
		output = util_sigmoid(feat);
		meta = feat;
		return output.data;
	};
	std::vector<T> backward(std::vector<T> dprev){
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
		return dfeat.data;
	};
};
