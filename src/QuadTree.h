#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include "QuadValModel.h"
#include "utils.h"



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
private:
	QuadNode root;
public:
	QuadTree(int, int);
	virtual ~QuadTree();

	void insert(std::unique_ptr<T> elt);

	std::string toString() const;
};

//////
/// Nested class QuadNode
//////

template <typename T, int MaxElts, int MaxDepth>
class QuadTree<T, MaxElts, MaxDepth>::QuadNode
{
private:
	int max_elements;
	int max_depth;
	int depth;

	/// The node's bounding box
	AABB box;

	/// A node without children is a leaf
	std::forward_list <QuadNode> children{};
	std::forward_list <std::unique_ptr<T>> values{};
	short counter = 0;

public:
	QuadNode(AABB);
	virtual ~QuadNode();

	int countChildren() const;
	bool isLeaf() const;

	void insert(std::unique_ptr<T> elt);
	std::string toString(int indent = 0) const;

	QuadNode(const QuadNode&) = delete;
	QuadNode& operator=(const QuadNode&) = default;
};
using namespace std;
using namespace std::literals::string_literals;

template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::QuadNode::QuadNode(AABB b) : box{ b }
{
}

template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::QuadNode::~QuadNode()
{
}

template <typename T, int ME, int MD>
int QuadTree<T, ME, MD>::QuadNode::countChildren() const
{
	return distance(children.begin(), children.end());
}

template <typename T, int ME, int MD>
bool QuadTree<T, ME, MD>::QuadNode::isLeaf() const
{
	return children.begin() == children.end();
}


template <typename T, int ME, int MD>
void QuadTree<T, ME, MD>::QuadNode::insert(std::unique_ptr<T> elt)
{
	DEBUG("Inserting " + elt->toString() + "\n");
	if (counter < ME)
		values.emplace_front(std::move(elt));
	else {
		AABB elt_box = elt->getBox();
	}
	DEBUG("End of insertion\n");
}

template <typename T, int ME, int MD>
string QuadTree<T, ME, MD>::QuadNode::toString(int indent) const {
	string vals = ""s;
	for (auto& val : values) {
		if (vals != ""s) vals += ", "s;
		vals += val->toString();
	}

	// Showing child nodes with indent
	auto in = [&indent]() {
		string in = ""s;
		for (int i = 0; i <= indent; i++) in += "\t";
		return in;
	};
	string schild = ""s;
	for (auto& child : children)
		schild += in() + child.toString(indent + 1) + "\n"s;
	return "Node"s + (isLeaf() ? "(leaf)"s : ""s) + ", box"s + box.toString() + ", vals{"s + vals + "}"s + "\n"s + schild;
}


//////
/// QuadTree
//////

template<typename T, int MaxElts, int MaxDepth>
inline QuadTree<T, MaxElts, MaxDepth>::QuadTree(int w, int h)
	: root{ AABB{ 0,0,w,h } }
{
}

template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::~QuadTree()
{
}

template <typename T, int ME, int MD>
void QuadTree<T, ME, MD>::insert(std::unique_ptr<T> elt) {
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
