#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {

	std::cout << "Hello World!\n";

	QuadTree<int> qt{ 500, 500 };
	cout << qt.toString() << endl;
	qt.insert(4);
}
