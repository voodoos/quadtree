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

std::string AABB::toString() const {
    return "{ x: "s + std::to_string(x)
    + ", y: "s + std::to_string(y)
    + ", w: "s + std::to_string(w)
    + ", h: "s + std::to_string(h) + "}"s;
}
