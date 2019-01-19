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

	class TestItem : public QuadValModel {
	private:
		int i;
		AABB box;

	public:
		TestItem(int i, AABB b)
			: i{ i }, box{ b } {}
		TestItem(int i, int x, int y, int w, int h)
			: i{ i }, box{ AABB {x,y,w,h} } {}
		const AABB& getBox() const {
			return box;
		}

		std::string toString() const {
			return to_string(i) + box.toString();
		};

		TestItem(const TestItem& t) {
			cout << "/!\ OUPS, copy of " + t.toString();
		}

		TestItem& operator=(const TestItem& t) {
			cout << "/!\ OUPS, copy of " + t.toString();
			return TestItem(t);
		}
	};

	QuadTree<TestItem> qt{ 500, 500 };
	cout << qt.toString() << endl;
	qt.insert(new TestItem{ 4, AABB{10,10,10,10} });
	cout << qt.toString() << endl;
}
