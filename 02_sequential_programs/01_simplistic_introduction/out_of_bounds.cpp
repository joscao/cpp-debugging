#include <vector>
#include <iostream>


/*
 * WARNING: THIS IS AN INTENTIALLY FAULTY PROGRAM TO DEMONSTRATE DEBUGGING TECHNIQUES
 */

int main(){
	std::vector<double> data{1.,2.,3.,4.};

	std::cout << data[4] << "\n";

	std::cout << data.at(4) << "\n";
}
