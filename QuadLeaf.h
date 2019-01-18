#pragma once
#include "QuadNode.h"

template <typename T>
class QuadLeaf :
	public QuadNode<T>
{
public:
	QuadLeaf();
	~QuadLeaf();
};

