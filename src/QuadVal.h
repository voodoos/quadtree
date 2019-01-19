#pragma once

#include "QuadTree.h"

template <typename T, int MaxElts, int MaxDepth>
class QuadTree<T, MaxElts, MaxDepth>::QuadVal
{
private:
	T value;
	AABB box;
	QuadTree<T, MaxElts, MaxDepth>::QuadNode& parent;

public:
	QuadVal(T);
	~QuadVal();

	const AABB& getBox() const;
};

template <typename T, int MaxElts, int MaxDepth>
QuadTree<T, MaxElts, MaxDepth>::QuadVal::QuadVal(T v)
	: value{ v }
{
}

template <typename T, int MaxElts, int MaxDepth>
QuadTree<T, MaxElts, MaxDepth>::QuadVal::~QuadVal()
{
}

template <typename T, int MaxElts, int MaxDepth>
const AABB& QuadTree<T, MaxElts, MaxDepth>::QuadVal::getBox() const
{
	return box;
}
