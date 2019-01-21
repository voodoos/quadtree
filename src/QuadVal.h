#pragma once

#include "AABB.h"
#include "QuadTree.h"

/// A "model" class to guide the creation of 
/// possible values for the QuadTree

template <typename T, int ME, int MD>
class QuadTree<T, ME, MD>::QuadVal
{
private:
	AABB box;
	QuadNode* host = nullptr;
public:
	QuadVal() = default;
	QuadVal(AABB);

	QuadVal(const QuadVal&) = delete;
	QuadVal& operator=(const QuadVal&) = delete;
	virtual ~QuadVal() = default;

	const AABB& get_box() const;
	virtual std::string toString() const = 0;
};

using namespace std;


template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::QuadVal::QuadVal(AABB b)
	: box{
	b
} {}


template <typename T, int ME, int MD>
const AABB& QuadTree<T, ME, MD>::QuadVal::get_box() const {
	return box;
}
