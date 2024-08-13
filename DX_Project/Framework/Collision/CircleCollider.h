#pragma once
class CircleCollider : public Collider {
public:
	
private:
	float radius;
	// 여기서는 타원을 다루지 않고 원만 다룸
	//이 경우 원의 반지름만 구하는것으로 쉽게 구성 가능

	

	// Collider을(를) 통해 상속됨
	virtual void CreateLine() override;

	bool isAABB(RectCollider* collider);
	bool isOBB(RectCollider* collider);
	//사각형 충돌 판정과의 충돌여부를 가릴때 사용하는 함수들
	//여기서 AABB라고 적혀있긴 한데 진짜 AABB충돌은 아니기는 함
	//그냥 회전하지 않은 사각형과 충돌할때는 이렇게도 할수 있다 라는걸 보여주기 위해만들어둔것

	//실제로는 OBB쪽을 주로 이용하게 될 것

	//또한 사각형의 충돌 판정은 회전을 고려해야 하지만
	//원형 충돌 판정은 애초에 원이라서 회전해도 다 똑같으므로 고려할 필요가 없음

	//그래서 AABB,OBB는 CircleCollider내부에선 사각형과 충돌할때만 따짐

public:
	CircleCollider(float rad);
	~CircleCollider();

	float GetRadius() {
		return radius * min(GlobalScale().x, GlobalScale().y);
		//이 충돌판정이 항상 1,1스케일을 가진다고 보장할수 없음
		//그래서 스케일값으로 인해 원이 찌그러진 경우,
		//적어도 비어있는 공간에 충돌할일은 없게
		//scale의 2개 값중에 더 작은 값으로 반지름을 맞춤
	}

	// Collider을(를) 통해 상속됨
	virtual bool isPointCollision(Vector2 point) override;
	virtual bool isCircleCollision(CircleCollider* collider) override;
	virtual bool isRectCollision(RectCollider* collider, Vector2* overwrap = NULL) override;
	
};