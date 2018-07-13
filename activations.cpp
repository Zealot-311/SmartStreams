#include <stdexcept>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "matrix.h"

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
	std::unordered_map<T,T> params;
	std::unordered_map<T,T> grads;
	std::vector<std::vector<T> > meta;
	void init(std::string name = "FC", int input_dim = 0, int output_dim = 0, float init_scale = 0){
		name = name;
		w_name = name + "_w";
		b_name = name + "_b";
		input_dim = input_dim;
		output_dim = output_dim;
        
        //create 0 vector
        std::vector<std::vector<T> > zeroVector(1, std::vector<T> (input_dim,0));
        
		params.insert(std::pair<std::string, std::vector<std::vector<T> > >(w_name, scalarMultiplication(init_scale, randomMatrix<T>(input_dim, output_dim))));
        params.insert(std::pair<std::string, std::vector<std::vector<T> >>(b_name,  zeroVector));
		//grads.insert(std::pair<std::string, std::vector<std::vector<T> > >(w_name, NULL));
		//grads.insert(std::pair<std::string, std::vector<std::vector<T> > >(b_name, NULL));
		meta.clear();
	}

	std::vector<std::vector<T> > forward(std::vector<std::vector<T> > feat){
		std::vector<std::vector<T> > output;
		try{
			if(input_dim != feat[0].size()){
				throw(1);
			}
		} catch(int i){
            std::cout << "specified input dimension does not match actual input dimension";
		}
		output = pairwiseAddition(matrixMultiplication(reshapeVector(feat,1,input_dim), params[w_name]));
		meta = feat;
		return output;
	}

	std::vector<std::vector<T> > backward(std::vector<std::vector<T> > dprev){
		std::vector<std::vector<T> > feat = meta;
		try {
			if (feat.size() == 0){
				throw 1;
			};
		}
		catch(int i){
            std::cout << "No forward function called before for this module!";
		};
		std::vector<std::vector<T> > dfeat;
		//grads.insert(std::pair<std::string, std::vector<std::vector<T> > >(w_name, NULL));
		//grads.insert(std::pair<std::string, std::vector<std::vector<T> > >(b_name, NULL));
		grads.insert(std::pair<std::string, std::vector<std::vector<T> > >(b_name, sumAcrossAxis(dprev, 0)));
		dfeat = matrixMultiplication(dprev, reshapeVector(matrixTranspose(params[w_name]), meta.size(), meta[0].size()));
		grads.insert(std::pair<std::string, std::vector<std::vector<T> > >(w_name, matrixMultiplication(matrixTranspose(reshapeVector(feat, 1, input_dim)),dprev)));
		meta.clear();
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
	std::unordered_map<T,T> params;
	std::unordered_map<T,T> grads;
	std::vector<std::vector<T> > meta;

	void init(std::string name = "relu"){
		name = name;
	};
	std::vector<std::vector<T> > forward(std::vector<std::vector<T> > feat){
		std::vector<std::vector<T> > output;
		output = matrixMax(feat, 0);
		meta = feat;
		return output;
	};

	std::vector<std::vector<T> > backward(std::vector<std::vector<T> > dprev){
		std::vector<std::vector<T> > feat = meta;
		try {
			if (feat.size() == 0){
				throw 1;
			};
		}
		catch(int i){
            std::cout << "No forward function called before for this module!";
		};
		std::vector<std::vector<T> > dfeat;
		feat = meta;
		//TODO: maybe take this
		feat = pairwiseDivision(util_max(feat,0), feat);
		dfeat = matrixMultiplication(dprev, feat);
		meta.clear();
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
	std::unordered_map<T,T> params;
	std::unordered_map<T,T> grads;
    std::vector<std::vector<T> > meta;
	
    void init(std::string name = "sigmoid"){
		name = name;
		
	};
	std::vector<std::vector<T> > forward(std::vector<std::vector<T> > feat){
		std::vector<std::vector<T> > output;
		output = matrixSigmoid(feat);
		meta = feat;
		return output.data;
	};
	std::vector<std::vector<T> > backward(std::vector<std::vector<T> > dprev){
		std::vector<std::vector<T> > feat = meta;
		try {
			if (feat.size() == 0){
				throw 1;
			};
		}
		catch(int i){
            std::cout << "No forward function called before for this module!";
		};
        std::vector<std::vector<T> > dfeat;
		feat = meta;
		feat = pairwiseDivision(matrixSigmoid(feat), feat);
		dfeat = matrixMultiplication(dprev, feat);
        meta.clear();
		return dfeat.data;
	};
};

template <typename T>
class cross_entropy
{
public:
	cross_entropy();
	~cross_entropy();
	bool dim_average;
	std::vector<std::vector<T> > dloss;
	std::vector<std::vector<T> > label;

	void init(bool dim_average = true){
		dim_average = dim_average;
	};
	std::vector<std::vector<T> > forward(std::vector<std::vector<T> > feat, std::vector<std::vector<T> > label){
		std::vector<std::vector<T> > scores = softmax(feat);
		float loss;
		float sum = 0;
		int i = 0;
		while(i>=(label.size()*label[0].size())){
			sum += util_log(scores)[i][label[i]];
			i++;
		}
		loss = -sum/(label.size()*label[0].size());
		dloss = scores;
		label = label;
		return loss;
	};

	std::vector<std::vector<T> > backward(){
		try {
			if (dloss.size() == 0){
				throw 1;
			};
		}
		catch(int i){
            std::cout << "No forward function called before for this module!";
		};
		int i = 0;
		while(i>=(label.size()*label[0].size())){
			dloss[i][label[i]] = dloss[i][label[i]]-1
			i++;
		}
		dloss = scalarMultiplication(1/(label.size()*label[0].size()), dloss);
		return dloss
	}
};

std::vector<std::vector<T> > softmax(std::vector<std::vector<T> > feat){
	std::vector<std::vector<T> > scores;
	float maxfeat = util_amax(feat, 1);
	feat = matrixSubtraction()
}
