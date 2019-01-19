#include "pch.h"
#include <forward_list>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "QuadTree.h"

using namespace std;

int main() {

	std::cout << "Hello World!\n";

	/*std::cout << "Size of QuadNode<int>: " << sizeof(QuadTree<int, 4, 5>::QuadNode > ) << endl;
	std::cout << "Size of QuadNode<short>: " << sizeof(QuadTree<int, 4, 5>::QuadNode) << endl;
	std::cout << "Size of forward_list<int>: " << sizeof(forward_list<int>) << endl;
	std::cout << "Size of short: " << sizeof(short) << endl;
	std::cout << "Size of AABB: " << sizeof(AABB) << endl;*/

	//class Item : public QuadTree<int>::QuadVal {};

	QuadTree<int> qt{ 500, 500 };
	//cout << qt.toString() << endl;
	//qt.insert(new Item{ 4, AABB{10,10,10,10} });
	//cout << qt.toString() << endl;
}
