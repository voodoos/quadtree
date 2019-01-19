#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include "AABB.h"
#include "utils.h"

#include "QuadNode.h"


template <typename T, int MaxElts = 4, int MaxDepth = 10>
/// requires T to have a bounding box
class QuadTree
{
	///<summary>
	///<para>This implementation of quadtrees is fairly simple. It may differ from others
	///in the way it deals with overlapping elements wich are places on the deepest node
	///containing them entirely. Thus the elements limit might not always be respected.</para>
	///</summary>
public:
	class QuadNode;
	class QuadVal;

private:
	QuadNode* root;
public:
	QuadTree(int, int);
	virtual ~QuadTree();

	void insert(T* elt);

	std::string toString() const;
};

template<typename T, int MaxElts, int MaxDepth>
inline QuadTree<T, MaxElts, MaxDepth>::QuadTree(int w, int h)
	: root{ new QuadNode{ AABB{ 0,0,w,h } } }
{
}

template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::~QuadTree()
{
	delete root;
}

template <typename T, int ME, int MD>
void QuadTree<T, ME, MD>::insert(T* elt) {
	root.insert(std::move(elt));
}

template <typename T, int ME, int MD>
std::string QuadTree<T, ME, MD>::toString() const {
	ostringstream  ss;
	ss << "Max elements per node: " << ME << endl;
	ss << "Max depth: " << MD << endl;
	ss << root;
	return ss.str();
}
