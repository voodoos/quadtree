#pragma once

#include <optional>

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
	QuadNode* host;
    
public:
    explicit QuadVal(T&&);
	explicit QuadVal(T&&,  QuadNode&);
    QuadVal(QuadVal&&);

    QuadVal() = default;
	QuadVal(const QuadVal&) = delete;
	QuadVal& operator=(const QuadVal&) = delete;
	virtual ~QuadVal() = default;

    
    //T&& move_val();
	const AABB& get_box() const;
	std::string toString() const;
    bool moved() const;
    
};

using namespace std;

template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::QuadVal::QuadVal(T&& v)
: val{ std::move(v) }, host { nullptr } {
}


template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::QuadVal::QuadVal(
    T&& v,
    QuadNode& qn)
: val{ std::move(v) }, host { &qn } {
}

template <typename T, int ME, int MD>
QuadTree<T, ME, MD>::QuadVal::QuadVal(QuadVal&& v)
: val{ std::move(v.val) }, host {v.host} {
    v.host = nullptr;
    DEBUG("Moving QuadVal.\n");
}

/*
template <typename T, int ME, int MD>
T&& QuadTree<T, ME, MD>::QuadVal::move_val() {
    this->host = nullptr;
    return std::move(val);
}
 */

template <typename T, int ME, int MD>
const AABB& QuadTree<T, ME, MD>::QuadVal::get_box() const {
	return val.get_box();
}

template <typename T, int ME, int MD>
string QuadTree<T, ME, MD>::QuadVal::toString() const {
    return val.toString();
}

template <typename T, int ME, int MD>
bool QuadTree<T, ME, MD>::QuadVal::moved() const {
    return host == nullptr;
}
