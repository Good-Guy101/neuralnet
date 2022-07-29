#include "Network.hpp"
#include "Layer.hpp"
#include "matmath/Matrix.hpp"

#include <vector>
#include <iostream>
#include <math.h>

Network::Network(int inHeight,int hiddenHeight, int outHeight, int numHidden){
	layers.push_back(Layer(inHeight, hiddenHeight, 0));
	for(int i = 1; i < numHidden; i++)
		layers.push_back(Layer(hiddenHeight, hiddenHeight, 0));
	layers.push_back(Layer(hiddenHeight, outHeight, 1));
}

Matrix Network::feedFwd(Matrix input){
	Matrix curInput = input.copy();
	for(int i = 0; i < layers.size(); i++){
		curInput = layers[i].activate(curInput);
	}

	return curInput;
}

void Network::randomize(){
	for(int i = 0; i < layers.size(); i++){
		layers[i].randomize();
	}

}

void Network::print(){
	std::cout<<"numLayers = "<<layers.size()<<'\n';
	for(int i = 0; i < layers.size(); i++)
		layers[i].print();
}

void Network::save(char* fileName){

}

Network Network::load(char* fileName){

}

double Network::costTotal(std::vector<Matrix> inputs, std::vector<Matrix> desired){
	if(inputs[0].col != this->layers[0].getInputSize() || desired[0].col != this->layers[layers.size()-1].getOutputSize()){
		std::cout<<"\033[31m"<<"[Error] Input or desired output not compatable with current network: input size = "<<this->layers[0].getInputSize()<<" output size = "<<this->layers[layers.size()-1].getOutputSize()<<"\033[0m\n";
		exit(EXIT_FAILURE);
	}
	double output = 0;//fix

	for(int i = 0; i < inputs.size(); i++){
		//output += matPow(matSub(feedFwd(inputs[i]),desired[i]), 2);
	}
	//return output.length() * double(1.0 / (2.0 * inputs.size()));
}

void Network::trainSGD(Matrix input, Matrix target){
	std::vector<Matrix> gradientW;
	std::vector<Matrix> gradientB;
	std::vector<Matrix> outputs;
	Matrix outError;
	Matrix curInput = input;
	Matrix curGrad;
	Matrix deltaW;

	for(int i = 0; i < layers.size(); i++){
		curInput = layers[i].activate(curInput);
		outputs.push_back(curInput);
	}
	outError = matSub(target, outputs.back());
	//outError.print();
	for(int i = layers.size()-1; i >= 0; i--){
		curGrad = matdSig(outputs[i]);
		curGrad = matMult(curGrad, outError);
		curGrad = matScale(curGrad, learnRate);
		gradientW.push_back(curGrad);
		std::cout<<"First";
		if(i > 0)
			outError = matDot(layers[i-1].getWeights(), outError);
	}

	for(int i = 0; i < gradientW.size(); i--){
		std::cout<<"Second";
		deltaW = matDot(gradientW[i], matTrans(outputs[outputs.size()-(1+i)]));
		layers[layers.size()-(1+i)].update(deltaW);//the layers are wrong check term
	}
	
}
