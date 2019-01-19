#pragma once
#include <forward_list>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>

#include "AABB.h"

template <typename T>
class QuadNode
{
private:
	/// A node without children is a leaf
	std::forward_list <QuadNode<T>> children{};
	std::forward_list <T> values{};
    short counter = 0;

    /// The node's bounding box
	AABB box;
public:
	QuadNode(AABB);
	~QuadNode();

    bool isLeaf() const;
    
	void insert(T elt);
    std::string toString() const;
    
    friend std::ostream & operator << (std::ostream &, const QuadNode<T> &);
};

using namespace std;
using namespace std::literals::string_literals;

template <typename T>
QuadNode<T>::QuadNode(AABB b) : box{ b }
{
}

template <typename T>
QuadNode<T>::~QuadNode()
{
}

template <typename T>
bool QuadNode<T>::isLeaf() const
{
    return children.begin() == children.end();
}


template<typename T>
void QuadNode<T>::insert(T elt)
{
	cout << "pouet" << "w" << box.w << " h" << box.h;
}

template<typename T>
std::ostream& operator << ( std::ostream& os, const QuadNode<T>& rhs ) {
    auto fold = [](string acc, T elt) { return acc + ", "s + to_string(elt); };
    string vals = (rhs.counter > 0)? accumulate(next(rhs.values.begin()), rhs.values.end(), to_string(rhs.values.front()), fold) : ""s;
    //string vals = fold("toto", "tata");
    return os << "Node"s + (rhs.isLeaf()?"(leaf)"s:""s) + ", box"s + rhs.box.toString() + ", vals{"s + vals + "}"s;
}
