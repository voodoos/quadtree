#pragma once
#include <string>

using namespace std::literals::string_literals;

struct AABB {
public:
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

	std::string toString() const;
};
