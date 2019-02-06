#pragma once
#include <forward_list>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>


#include "AABB.h"
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
	class QuadVal;
	using val = QuadVal;
private:
	QuadNode root;
public:
	QuadTree(int, int);
	virtual ~QuadTree();

	const QuadNode& get_root() const;
    
    void insert(const T& elt);   // Copy insert
	void insert(T&& elt);       // Move insert

	std::string toString() const;
};

/////////////////////////////
/// Nested class QuadNode ///
/////////////////////////////

template <typename T, int MaxElts, int MaxDepth>
class QuadTree<T, MaxElts, MaxDepth>::QuadNode
{
	using vals_t = QuadVal;
private:
	int depth;

	/// The node's bounding box
	AABB box;

	/// A node without children is a leaf
	std::forward_list <QuadNode> children{};
    std::forward_list <vals_t> values{};
	short counter = 0;

public:
	QuadNode(AABB, int = 0);
	virtual ~QuadNode();
    
    QuadNode(const QuadNode&) = delete;
    QuadNode& operator=(const QuadNode&) = delete;
    QuadNode(QuadNode&&) = delete;
    QuadNode& operator=(QuadNode&&) = delete;

	int countChildren() const;
	bool isLeaf() const;
	const AABB& get_box() const;
	const std::forward_list <QuadNode>& get_children() const;
	const std::forward_list <vals_t>& get_values() const;

	std::string toString(int indent = 0) const;

    void insert(vals_t&& elt);

private:
	void  force_insert(vals_t&& elt);
	bool  dispatch(vals_t&& elt);
	void  split_and_insert(vals_t&& elt);
};

////////////////////////////
/// QuadNode Definitions ///
////////////////////////////
using namespace std;
using namespace std::literals::string_literals;

template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::QuadNode::QuadNode(AABB b, int d) : depth{ d }, box{ b }
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
const AABB & QuadTree<T, ME, MD>::QuadNode::get_box() const
{
	return box;
}

template <typename T, int ME, int MD>
const std::forward_list<typename QuadTree<T, ME, MD>::QuadNode>& QuadTree<T, ME, MD>::QuadNode::get_children() const
{
	return children;
}

template <typename T, int ME, int MD>
const std::forward_list<typename QuadTree<T, ME, MD>::QuadNode::vals_t>& QuadTree<T, ME, MD>::QuadNode::get_values() const
{
	return values;
}

template <typename T, int ME, int MD>
string QuadTree<T, ME, MD>::QuadNode::toString(int indent) const
{
	string vals = ""s;
	for (auto& val : values) {
		if (vals != ""s) vals += ", "s;
		vals += val.toString();
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

template <typename T, int ME, int MD>
void QuadTree<T, ME, MD>::QuadNode::insert(vals_t&& elt)
{
    DEBUG("Insert " + elt.toString() + "\n");
    //todo: move or forward ?
    if (isLeaf() && counter < ME) {
        force_insert(std::forward<QuadVal>(elt));
    }
    else {
        // Split if needed
        split_and_insert(std::forward<QuadVal>(elt));
        
    }
    DEBUG("End insert " + elt.toString() + "\n");
}

template <typename T, int ME, int MD>
void QuadTree<T, ME, MD>::QuadNode::force_insert(vals_t&& elt)
{
    elt.set_host(*this);
    values.push_front(std::forward<vals_t>(elt));
    //values.push_front(QuadVal(std::forward<T>(elt)));
	counter++;
}

template <typename T, int ME, int MD>
bool QuadTree<T, ME, MD>::QuadNode::dispatch(vals_t&& elt)
{
    DEBUG("Dispatch " + elt.toString() + "\n");
	AABB box = elt.get_box();

	// Could be optimized
	for (auto& child : children)
		if (box.is_in(child.box)) {
			child.insert(std::forward<vals_t>(elt));
			counter--;
            DEBUG("Dispatched " + elt.toString() + "\n");
            return true;
		}
    DEBUG("No dispatch " + elt.toString() + "\n");
    return false;
}

template <typename T, int ME, int MD>
void QuadTree<T, ME, MD>::QuadNode::split_and_insert(vals_t&& elt)
{
	// Only split leafs
	if (isLeaf()) {
		DEBUG("Splitting.\n");
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
		for (auto& elt : values)
            dispatch(std::forward<vals_t>(elt));
        
        //TODO the whole QuadVal / TestVal move thing feels clunky

		// Elements succesfully dispatched will leave a moved QuadVal
		values.remove_if([](vals_t& qv){ return qv.moved(); });
	}
    
    // We try to insert the element in the children
    if(!dispatch(std::forward<vals_t>(elt)))
        // if it fails we insert it here
        force_insert(std::forward<vals_t>(elt));
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

template<typename T, int ME, int MD>
const typename QuadTree<T, ME, MD>::QuadNode & QuadTree<T, ME, MD>::get_root() const
{
	return root;
}

template <typename T, int ME, int MD>
void QuadTree<T, ME, MD>::insert(const T& elt) {
    static_assert(std::is_copy_constructible_v<T>,
                  "T should copy-constructible did you forgot to move ?");
    insert(T(elt));
}

template <typename T, int ME, int MD>
void QuadTree<T, ME, MD>::insert(T&& elt) {
    // Perfect forwarding
	root.insert(QuadVal(std::forward<T>(elt)));
}

template <typename T, int ME, int MD>
std::string QuadTree<T, ME, MD>::toString() const {
	ostringstream  ss;
	ss << "Max elements per node: " << ME << endl;
	ss << "Max depth: " << MD << endl;
	ss << root;
	return ss.str();
}
