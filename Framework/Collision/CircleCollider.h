#pragma once
class CircleCollider : public Collider {
public:
	
private:
	// Collider��(��) ���� ��ӵ�
	virtual void CreateLine() override;

public:
	CircleCollider();
	virtual ~CircleCollider();

	// Collider��(��) ���� ��ӵ�
	virtual bool isPointCollision(Vector2 point) override;
	virtual bool isCircleCollision(CircleCollider* collider) override;
	virtual bool isRectCollision(RectCollider* collider, Vector2* overwrap = NULL) override;
	
};