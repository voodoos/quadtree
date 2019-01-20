#include "QuadValModel.h"




QuadValModel::QuadValModel(AABB b)
	: box{ b } {}


const AABB& QuadValModel::get_box() const {
	return box;
}
