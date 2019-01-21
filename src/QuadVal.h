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
	//typename QuadNode& host;
public:
	QuadVal() = default;
	QuadVal(/*T&,*/ AABB);

	QuadVal(const QuadVal&) = delete;
	QuadVal& operator=(const QuadVal&) = delete;
	virtual ~QuadVal() = default;

	const AABB& get_box() const;
	virtual std::string toString() const = 0;
};

using namespace std;


template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::QuadVal::QuadVal(/*T& v,*/ AABB b)
	: /*val{ v }, */box{
	b
} {}


template <typename T, int ME, int MD>
const AABB& QuadTree<T, ME, MD>::QuadVal::get_box() const {
	return box;
}
