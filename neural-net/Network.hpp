#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "Layer.hpp"
#include "matmath/Matrix.hpp"

#include <vector>

class Network{
private:
	std::vector<Layer> layers;
	double learnRate = 1;

public:
	Network(int, int, int, int);
	Matrix feedFwd(Matrix);
	void randomize();
	void print();
	void save(char*);
	Network load(char*);
	double costTotal(std::vector<Matrix>, std::vector<Matrix>);
	void trainSGD(Matrix, Matrix);
};



#endif