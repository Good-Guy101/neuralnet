#include "Layer.hpp"
#include "matmath/Matrix.hpp"

#include <iostream>
#include <vector>

Layer::Layer(int _numInputs, int _height, int _type){
	this->numInputs = _numInputs;
	this->height = _height;
	this->type = _type;
	this->weights = Matrix(_height, numInputs);
	this->bias = Matrix(_height, 1);
	this->activation_func = &matSig;
}

void Layer::randomize(){
	weights.randomize();
	bias.randomize();
}

Matrix Layer::activate(Matrix inputs){
	if(inputs.rows > numInputs || inputs.col > 1){
		std::cout<<"\033[31m"<<"[Error] Input not compatable with current Layer\033[0m\n";
		exit(EXIT_FAILURE);
	}
	Matrix output = this->activation_func(matAdd(matDot(weights, inputs), bias));
	this->activation = output;
	return output;
}

void Layer::print(){
	std::cout<<"Layer type: ";
	if(!type)
		std::cout<<"Hidden\n";
	else
		std::cout<<"Output\n";
	std::cout<<"Weights: \n";
	weights.print();
	std::cout<<"Bias: \n";
	bias.print();
}

int Layer::getInputSize(){
	return numInputs;
}

int Layer::getOutputSize(){
	return height;
}

void Layer::update(Matrix deltaW){
	this->weights = matSub(weights, deltaW);
}

Matrix Layer::getLastOut(){
	return activation;
}

Matrix Layer::getWeights(){
	return this->weights;
}