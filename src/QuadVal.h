#pragma once

#include "AABB.h"
#include "QuadTree.h"
#include "utils.h"

/// A "model" class to guide the creation of 
/// possible values for the QuadTree

template <typename T, int ME, int MD>
class QuadTree<T, ME, MD>::QuadVal
{
private:
    T val;
	QuadNode* host = nullptr;
    
public:
	explicit QuadVal(T&&);
    QuadVal(QuadVal&&);

    QuadVal() = default;
	QuadVal(const QuadVal&) = delete;
	QuadVal& operator=(const QuadVal&) = delete;
	virtual ~QuadVal() = default;

    
    T&& get_val();
	const AABB& get_box() const;
	std::string toString() const;
    
};

using namespace std;


template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::QuadVal::QuadVal(T&& v)
: val{ std::move(v) } {}

template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::QuadVal::QuadVal(QuadVal&& v)
: val{ std::move(v.val) }, host {v.host} {
    v.host = nullptr;
    DEBUG("Moving QuadVal.\n");
}


template <typename T, int ME, int MD>
T&& QuadTree<T, ME, MD>::QuadVal::get_val() {
    return std::move(val);
}

template <typename T, int ME, int MD>
const AABB& QuadTree<T, ME, MD>::QuadVal::get_box() const {
	return val.get_box();
}

template <typename T, int ME, int MD>
string QuadTree<T, ME, MD>::QuadVal::toString() const {
    return val.toString();
}
