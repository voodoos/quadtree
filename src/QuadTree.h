#pragma once
#include <forward_list>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <SDL.h>

#include "AABB.h"
#include "utils.h"



template <typename T>
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
	using val = QuadVal;
private:
	QuadNode root;
public:
	constexpr QuadTree(int, int, int = 3, int = 5);
	virtual ~QuadTree();

	//const int& get_me() const;
	//const int& get_md() const;
	const QuadNode& get_root() const;
	void insert(std::unique_ptr<T> elt);

	std::string toString() const;
};

//////
/// Nested class QuadNode
//////

template <typename T>
class QuadTree<T>::QuadNode
{
	using eptr = std::unique_ptr<T>;
private:
	int max_elements;
	int max_depth;
	int depth;

	/// The node's bounding box
	const AABB box;

	/// A node without children is a leaf
	std::forward_list <QuadNode> children{};
	std::forward_list <eptr> values{};
	short counter = 0;

public:
	constexpr QuadNode(int, int, int = 3, int = 4, int = 0);
	virtual ~QuadNode();

	int countChildren() const;
	bool isLeaf() const;
	const AABB& get_box() const;
	const std::forward_list <QuadNode>& get_children() const;
	const std::forward_list <eptr>& get_values() const;

	void insert(eptr elt);
	std::string toString(int indent = 0) const;

	QuadNode(const QuadNode&) = delete;
	QuadNode& operator=(const QuadNode&) = default;

private:
	void  force_insert(eptr elt);
	void  dispatch(eptr& elt);
	void  split_and_insert(eptr elt = nullptr);
};

using namespace std;
using namespace std::literals::string_literals;

template <typename T>
constexpr QuadTree<T>::QuadNode::QuadNode(int w, int h, int me, int md, int d)
	: box{ AABB{ 0,0,w,h } }, max_elements{ me }, max_depth{ md }, depth{ d }
{
}

template <typename T>
QuadTree<T>::QuadNode::~QuadNode()
{
}

template <typename T>
int QuadTree<T>::QuadNode::countChildren() const
{
	return distance(children.begin(), children.end());
}

template <typename T>
bool QuadTree<T>::QuadNode::isLeaf() const
{
	return children.begin() == children.end();
}

template <typename T>
const AABB & QuadTree<T>::QuadNode::get_box() const
{
	return box;
}

template <typename T>
const std::forward_list<typename QuadTree<T>::QuadNode>& QuadTree<T>::QuadNode::get_children() const
{
	return children;
}

template <typename T>
const std::forward_list<typename QuadTree<T>::QuadNode::eptr>& QuadTree<T>::QuadNode::get_values() const
{
	return values;
}


template <typename T>
void QuadTree<T>::QuadNode::insert(eptr elt)
{
	DEBUG("Inserting " + elt->toString() + "\n");
	if (isLeaf() && counter < max_elements) {
		force_insert(std::move(elt));
		DEBUG("Elt " + to_string(counter) + "/" + to_string(max_elements) + ".\n");
	}
	else {
		// Split if needed
		split_and_insert(std::move(elt));

	}
	DEBUG("End of insertion\n");
}

template <typename T>
string QuadTree<T>::QuadNode::toString(int indent) const {
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

template <typename T>
void QuadTree<T>::QuadNode::force_insert(eptr elt)
{
	values.emplace_front(std::move(elt));
	counter++;
}
template <typename T>
void QuadTree<T>::QuadNode::dispatch(eptr& elt)
{
	AABB box = elt->get_box();

	// Could be optimized
	for (auto& child : children)
		if (box.is_in(child.box)) {
			child.insert(std::move(elt));
			counter--;
			break;
		}

	if (elt) {
		DEBUG("Element not fitting, inserted in parent\n");
		//force_insert(std::move(elt));
	}
}

template <typename T>
void QuadTree<T>::QuadNode::split_and_insert(eptr elt)
{
	// Only split leafs
	if (isLeaf()) {
		DEBUG("Splitting");
		int x = box.get_x(), y = box.get_y();
		int w2 = box.get_w() / 2, h2 = box.get_h() / 2;
		int w2r = box.get_w() % 2, h2r = box.get_w() % 2;

		// The four quadrants
		children.emplace_front(
			AABB{ x + w2 + w2r, y + h2 + h2r, w2, h2 },
			depth + 1
		);
		children.emplace_front(
			AABB{ x, y + h2 + h2r, w2 + w2r, h2 },
			depth + 1
		);
		children.emplace_front(
			AABB{ x + w2 + w2r, y, w2, h2 + h2r },
			depth + 1
		);
		children.emplace_front(
			AABB{ x, y, w2 + w2r, h2 + h2r },
			depth + 1
		);

		// We try to dispatch elements from the list
		// todo : optimization : we should not move around things staying in the list afterall...
		for (auto& elt : values)
			dispatch(elt);

		// Elements succesfully dispatched will leave a nullptr
		values.remove(nullptr);
	}

	if (elt) {
		dispatch(elt);
	}
}


//////
/// QuadTree
//////

template<typename T>
inline constexpr QuadTree<T>::QuadTree(int w, int h, int me, int md)
	: root{ w, h, me, md } {
	static_assert(md == 5, "Literal failed");
}

template <typename T>
QuadTree<T>::~QuadTree()
{
}
/*
template<typename T>
inline const int & QuadTree<T>::get_me() const
{
	return max_elements;
}

template<typename T>
inline const int & QuadTree<T>::get_md() const
{
	return max_depth;
}*/

template<typename T>
const typename QuadTree<T>::QuadNode & QuadTree<T>::get_root() const
{
	return root;
}

template <typename T>
void QuadTree<T>::insert(std::unique_ptr<T> elt) {
	root.insert(std::move(elt));
}

template <typename T>
std::string QuadTree<T>::toString() const {
	ostringstream  ss;
	//ss << "Max elements per node: " << max_elements << endl;
	//ss << "Max depth: " << max_depth << endl;
	ss << root;
	return ss.str();
}
