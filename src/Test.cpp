#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "QuadTree.h"

using namespace std;

int main() {

	std::cout << "Hello World!\n";

    std::cout << "Size of QuadNode<int>: " << sizeof(QuadNode<int>) << endl;
    std::cout << "Size of QuadNode<short>: " << sizeof(QuadNode<int>) << endl;
    std::cout << "Size of forward_list<int>: " << sizeof(forward_list<int>) << endl;
    std::cout << "Size of short: " << sizeof(short) << endl;
    std::cout << "Size of AABB: " << sizeof(AABB) << endl;
    
	QuadTree<int> qt{ 500, 500 };
	cout << qt.toString() << endl;
	qt.insert(4);
}
