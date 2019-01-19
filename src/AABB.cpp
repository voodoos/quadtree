#include "AABB.h"

std::string AABB::toString() const {
	return "{ x: "s + std::to_string(x)
		+ ", y: "s + std::to_string(y)
		+ ", w: "s + std::to_string(w)
		+ ", h: "s + std::to_string(h) + "}"s;
}
