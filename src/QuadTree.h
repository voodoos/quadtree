#pragma once
#include <memory>
#include <string>
#include <sstream>

#include "AABB.h"
#include "QuadLeaf.h"



template <typename T, int MaxElts = 4, int MaxDepth = 10>
class QuadTree
{

	///<summary>
	///<para>This implementation of quadtrees is fairly simple. It may differ from others
	///in the way it deals with overlapping elements wich are places on the deepest node
	///containing them entirely. Thus the elements limit might not always be respected.</para>
	///</summary>

private:
	QuadNode<T> root;
public:
	QuadTree(int, int);
	~QuadTree();

	void insert(T elt);

	std::string toString() const;
};

using namespace std;



template<typename T, int MaxElts, int MaxDepth>
inline QuadTree<T, MaxElts, MaxDepth>::QuadTree(int w, int h)
	: root{ AABB { 0, 0, w, h} }
{
}

template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::~QuadTree()
{
}

template <typename T, int ME, int MD>
void QuadTree<T, ME, MD>::insert(T elt) {
	root.insert(elt);
}

template <typename T, int ME, int MD>
string QuadTree<T, ME, MD>::toString() const {
	ostringstream  ss;
	ss << "Max elements per node: " << ME << endl;
	ss << "Max depth: " << MD << endl;
	return ss.str();
}
