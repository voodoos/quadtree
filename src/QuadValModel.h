#pragma once

#include "AABB.h"

/// A "model" class to guide the creation of 
/// possible values for the QuadTree
class QuadValModel
{
private:
	AABB box;
public:
	QuadValModel() = default;
	QuadValModel(AABB);
	QuadValModel(const QuadValModel&) = delete;
	QuadValModel& operator=(const QuadValModel&) = delete;
	virtual ~QuadValModel() = default;

	const AABB& getBox() const;
	virtual std::string toString() const = 0;
};