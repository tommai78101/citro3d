#pragma once
#include "types.h"
#include "maths.h"
#include <stdbool.h>

typedef struct C3D_AABB {
	C3D_FVec min;
	C3D_FVec max;
} C3D_AABB;

static inline bool AABB_ContainsAABB(const C3D_AABB* myself, const C3D_AABB* other) {
	return myself->min.x <= other->min.x &&
	       myself->min.y <= other->min.y &&
		   myself->min.z <= other->min.z &&
		   myself->max.x >= other->max.x &&
		   myself->max.y >= other->max.y &&
		   myself->max.z >= other->max.z;
}

static inline bool AABB_ContainsFVec3(const C3D_AABB* myself, const C3D_FVec* point) {
	return myself->min.x <= point->x &&
	       myself->min.y <= point->y &&
		   myself->min.z <= point->z &&
		   myself->max.x >= point->x &&
		   myself->max.y >= point->y &&
		   myself->max.z >= point->z;
}

static inline float AABB_GetSurfaceArea(const C3D_AABB* myself) {
	float x = myself->max.x - myself->min.x;
	float y = myself->max.y - myself->min.y;
	float z = myself->max.z - myself->min.z;
	return (float) (2.0f) * (x * x + x * z + y * z);
}

static inline void AABB_Combine(C3D_AABB* out, const C3D_AABB* a, const C3D_AABB* b){
	out->min = FVec3_New((a->min.x < b->min.x ? a->min.x : b->min.x), (a->min.y < b->min.y ? a->min.y : b->min.y), (a->min.z < b->min.z ? a->min.z : b->min.z));
	out->max = FVec3_New((a->max.x > b->max.x ? a->max.x : b->max.x), (a->max.y > b->max.y ? a->max.y : b->max.y), (a->max.z > b->max.z ? a->max.z : b->max.z));
}

static inline bool AABB_CollidesAABB(const C3D_AABB* a, const C3D_AABB* b){
	if (a->max.x < b->min.x || a->min.x > b->max.x)
		return false;
	if (a->max.y < b->min.y || a->min.y > b->max.y)
		return false;
	if (a->max.z < b->min.z || a->min.z > b->max.z)
		return false;
	return true;
}
