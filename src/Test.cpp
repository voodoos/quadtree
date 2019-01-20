#include "pch.h"
#include <forward_list>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "QuadTree.h"

using namespace std;

int main(int argc, char *argv[]) {

	std::cout << "Hello World!\n";

	/*std::cout << "Size of QuadNode<int>: " << sizeof(QuadTree<int, 4, 5>::QuadNode > ) << endl;
	std::cout << "Size of QuadNode<short>: " << sizeof(QuadTree<int, 4, 5>::QuadNode) << endl;
	std::cout << "Size of forward_list<int>: " << sizeof(forward_list<int>) << endl;
	std::cout << "Size of short: " << sizeof(short) << endl;
	std::cout << "Size of AABB: " << sizeof(AABB) << endl;*/

	class TestItem : public QuadValModel {
	private:
		int i;

	public:
		TestItem(int i, AABB b)
			: QuadValModel{ b }, i{ i }{}
		TestItem(int i, int x, int y, int w, int h)
			: TestItem{ i, AABB {x,y,w,h} } {}

		std::string toString() const {
			return to_string(i) + getBox().toString();
		};
	};

	QuadTree<TestItem, 3> qt{ 500, 500 };
	cout << qt.toString() << endl;
	qt.insert(make_unique<TestItem>(0, AABB{ 50,50,500,500 }));
	qt.insert(make_unique<TestItem>(0, AABB{ 50,50,500,500 }));
	qt.insert(make_unique<TestItem>(0, AABB{ 50,50,500,500 }));
	qt.insert(make_unique<TestItem>(0, AABB{ 50,50,500,500 }));
	qt.insert(make_unique<TestItem>(0, AABB{ 50,50,500,500 }));
	qt.insert(make_unique<TestItem>(0, AABB{ 50,50,500,500 }));
	qt.insert(make_unique<TestItem>(1, AABB{ 10,10,10,10 }));
	qt.insert(make_unique<TestItem>(2, AABB{ 100,10,10,10 }));
	qt.insert(make_unique<TestItem>(3, AABB{ 10,100,10,10 }));
	qt.insert(make_unique<TestItem>(4, AABB{ 300,300,10,10 }));
	qt.insert(make_unique<TestItem>(5, AABB{ 300,10,10,10 }));
	cout << qt.toString() << endl;

	return 0;
}
