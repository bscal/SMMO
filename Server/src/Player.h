#pragma once

#include "Core.h"

struct ColliderCapsule
{
	zpl_vec3 Center;
	zpl_vec3 Scale;
};

struct Player
{
	u32 UId;

	ColliderCapsule Collider;
	zpl_vec3 Position;
	zpl_vec3 Velocity;
};
