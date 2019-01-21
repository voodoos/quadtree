#pragma once
#include <string>

using namespace std::literals::string_literals;

class AABB {
	///<summary>
	/// <code>
	///   O(x,y) ---w-----o
	///      |            |
	///      |            |
	///      h            h
	///      |            |
	///      |            |
	///      o -----w-----o
	/// </code>
	///</summary>
	int x, y, w, h;

public:
	AABB();
	constexpr AABB(int, int, int, int);
	int get_x() const;
	int get_y() const;
	int get_w() const;
	int get_h() const;
	std::string toString() const;

	bool is_in(const AABB&) const;
};
