#pragma once
#include <forward_list>
#include <iostream>
#include <memory>

struct AABB;
template <typename T>
class QuadNode
{
private:
	/// A node without children is a leaf
	std::forward_list <QuadNode<T>> children{};
	std::forward_list <T> values{};

	AABB box;
public:
	QuadNode(AABB);
	~QuadNode();

	void insert(T elt);
};

using namespace std;

template <typename T>
QuadNode<T>::QuadNode(AABB b) : box{ b }
{
}

template <typename T>
QuadNode<T>::~QuadNode()
{
}

template<typename T>
void QuadNode<T>::insert(T elt)
{
	cout << "pouet" << "w" << box.w << " h" << box.h;
}