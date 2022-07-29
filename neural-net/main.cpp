#include "matmath/Matrix.hpp"
#include "Network.hpp"

#include <iostream>

int main(){
	Network net(1,3,1,1);
	Matrix input(1, 1);
	Matrix desOut(1, 1);
	int numTrains = 0;

	input.fill(1);
	input.print();

	desOut.fill(0);
	desOut.print();

	net.randomize();
	net.print();

	std::cout<<"Output:\n";
	net.feedFwd(input).print();

	for(int i = 0; i <= numTrains; i++){
		//std::cout<<"Train "<<i<<'\n';
		net.trainSGD(input, desOut);
	}

	std::cout<<"Output:\n";
	net.feedFwd(input).print();



	//std::cout<<net.costTotal(std::vector<Matrix>{input}, std::vector<Matrix>{desOut});
	




	return 0;
}