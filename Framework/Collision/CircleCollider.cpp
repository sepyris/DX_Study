#include "framework.h"

CircleCollider::CircleCollider()
{
}

CircleCollider::~CircleCollider()
{
}
bool CircleCollider::isPointCollision(Vector2 point)
{
	return false;
}
bool CircleCollider::isCircleCollision(CircleCollider* collider)
{
	return false;
}

bool CircleCollider::isRectCollision(RectCollider* collider, Vector2* overwrap)
{
	return false;
}



void CircleCollider::CreateLine()
{
}

