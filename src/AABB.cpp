#include "AABB.h"

AABB::AABB() : AABB(0, 0, 0, 0)
{
}

AABB::AABB(int x, int y, int w, int h)
	: x{ x }, y{ y }, w{ w }, h{ h }
{
}

int AABB::get_x() const { return this->x; }
int AABB::get_y() const { return this->y; }
int AABB::get_w() const { return this->w; }
int AABB::get_h() const { return this->h; }

std::string AABB::toString() const {
	return "{x: "s + std::to_string(this->x)
		+ ", y: "s + std::to_string(this->y)
		+ ", w: "s + std::to_string(this->w)
		+ ", h: "s + std::to_string(this->h) + "}"s;
}

bool AABB::is_in(const AABB &b) const
{
	return (b.x <= x) && (b.y <= y) &&
		(b.x + b.w >= x + w) && (b.y + b.h >= y + h);
}
