//
// Created by Xiaomi on 09.11.2019.
//

#include <Algorithm.h>
#include <Cluster.h>
#include <Error.h>
#include <iostream>

int main() {
	Algorithm Algorithm;
	auto [Error, Clusters] = Algorithm.Clustering("../TestData/TestData.txt", 2, 100);
	if (Error) {
		std::cout << "Error: " << *Error << std::endl;
	} else {
		std::cout << Clusters;
	}
	return 0;
}