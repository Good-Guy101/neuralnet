#ifndef LAYER_HPP
#define LAYER_HPP

#include "matmath/Matrix.hpp"

#include <vector>

class Layer{
private:
	int type; // 0 = hidden. 1 = output
	int numInputs;
	int height;
	Matrix weights;
	Matrix bias;
	Matrix activation;

	Matrix (*activation_func)(Matrix);

public:
	Layer(int, int, int);
	void randomize();
	Matrix activate(Matrix);
	void print();

	int getInputSize();
	int getOutputSize();
	void update(Matrix);
	Matrix getLastOut();
	Matrix getWeights();
};



#endif