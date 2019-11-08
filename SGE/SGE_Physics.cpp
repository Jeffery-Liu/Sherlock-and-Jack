//====================================================================================================
// Filename:	SGE_Physics.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "SGE_Physics.h"
#include "SGE_Graphics.h"

//====================================================================================================
// Namespace
//====================================================================================================

namespace SGE
{

//====================================================================================================
// Helper Functions
//====================================================================================================

bool Physics_BoundingBoxTest(const Rect& bb1, const Rect& bb2)
{
	bool intersect = true;
	if (bb1.max.y < bb2.min.y ||
		bb1.min.y > bb2.max.y ||
		bb1.min.x > bb2.max.x ||
		bb1.max.x < bb2.min.x)
	{
		intersect = false;
	}
	return intersect;
}

//----------------------------------------------------------------------------------------------------

bool Physics_BoundingCircleTest(const Circle& srcCircle, const Circle& intersectCircle)
{
	Vector2 vecToTarget = intersectCircle.center - srcCircle.center;
	float distanceSqr = vecToTarget.LengthSquared();
	float radii = intersectCircle.radius + srcCircle.radius;
	float radiiSqr = radii * radii;

	bool intersect = (distanceSqr < radiiSqr);
	return intersect;
}

//----------------------------------------------------------------------------------------------------

bool Physics_CircleRectangleTest(const Circle& srcCircle, const Rect& intersectRect)
{
	// Find the closest point to the circle within the rectangle
	const float closestX = SGE::Clamp(srcCircle.center.x, intersectRect.min.x, intersectRect.max.x);
	const float closestY = SGE::Clamp(srcCircle.center.y, intersectRect.min.y, intersectRect.max.y);

	// Calculate the distance between the circle's center and this closest point
	const float distanceX = srcCircle.center.x - closestX;
	const float distanceY = srcCircle.center.y - closestY;

	// If the distance is less than the circle's radius, an intersection occurs
	const float distanceSqr = (distanceX * distanceX) + (distanceY * distanceY);
	const float radiusSqr = srcCircle.radius * srcCircle.radius;
	const bool intersect = (distanceSqr < radiusSqr);
	return intersect;
}

//----------------------------------------------------------------------------------------------------

Vector2 Physics_Response(const float dt, const Vector2& src, const Vector2& contact, const Vector2& velocity, const float restitution/* = 2.0f*/)
{
	if (dt == 0.0f)
	{
		return Vector2(0.f, 0.f);
	}

	Vector2 normal = contact - src;
	normal.Normalize();

	Vector2 vel_dt = velocity * dt;
	SGE::Graphics_DebugLine(src, src + vel_dt, 0xAAAAFF);
	SGE::Graphics_DebugLine(contact, src, 0x00FF00);

	float dot = SGE::Math_Dot(vel_dt, normal);
	Vector2 A = (normal * restitution) * dot;

	SGE::Graphics_DebugLine(contact, contact + A, 0xFFFFFF);

	Vector2 X = vel_dt - A;
	SGE::Graphics_DebugLine(src, src + X, 0xFF0000);

	Vector2 response_vel = X * (1.f/dt);
	return response_vel;
}

} // namespace SGE