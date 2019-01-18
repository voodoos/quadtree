#pragma once

struct AABB {
	int x, y, w, h;
};

template <typename T>
class QuadVal
{
private:
	T value;

public:
	QuadVal();
	~QuadVal();
};

