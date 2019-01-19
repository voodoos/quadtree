#include "QuadValModel.h"




QuadValModel::QuadValModel(AABB b)
	: box{ b } {}


const AABB& QuadValModel::getBox() const {
	return box;
}
