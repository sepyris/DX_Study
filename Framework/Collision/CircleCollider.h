#pragma once
class CircleCollider : public Collider {
public:
	
private:
	// Collider을(를) 통해 상속됨
	virtual void CreateLine() override;

public:
	CircleCollider();
	virtual ~CircleCollider();

	// Collider을(를) 통해 상속됨
	virtual bool isPointCollision(Vector2 point) override;
	virtual bool isCircleCollision(CircleCollider* collider) override;
	virtual bool isRectCollision(RectCollider* collider, Vector2* overwrap = NULL) override;
	
};