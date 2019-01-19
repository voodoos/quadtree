#pragma once
#include <algorithm>
#include <forward_list>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include "utils.h"

template <typename T, int MaxElts, int MaxDepth>
class QuadTree;

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

	void insert(T* elt);
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
void QuadTree<T, ME, MD>::QuadNode::insert(T* elt)
{
	DEBUG("Inserting " + elt->toString() + "\n");
	if (counter < ME)
		values.emplace_front(elt);
	//AABB elt_box = elt.getBox();
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

