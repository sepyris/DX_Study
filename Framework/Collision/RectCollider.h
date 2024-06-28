#pragma once
class RectCollider : public Collider {

public:
	struct ObbDesc {//나중에 OBB충돌 알고리즘에서 사용하는 구조체
		Vector2 pos;
		Vector2 Axis[2];
		Vector2 half_size;
	};

private:
	Vector2 size;
	ObbDesc obb_desc;

	// Collider을(를) 통해 상속됨
	virtual void CreateLine() override;

	bool isAABB(RectCollider* rect, Vector2* overwrap = NULL);
	bool isOBB(RectCollider* rect);
	bool isAABB(CircleCollider* rect);
	bool isOBB(CircleCollider* rect);

	float separateAxis(Vector2 seperate, Vector2 e1, Vector2 e2);
	//OBB충돌 처리의 연산과정 도중 사용할 함수

public:
	RectCollider(Vector2 size);
	~RectCollider();

	ObbDesc GetObbDesc();

	// Collider을(를) 통해 상속됨
	virtual bool isPointCollision(Vector2 point) override;
	virtual bool isCircleCollision(CircleCollider* collider) override;
	virtual bool isRectCollision(RectCollider* collider, Vector2* overwrap = NULL) override;
	
	Vector2 Size() { return size * GlobalScale(); }
	//이 충돌 판정이 화면 기준으로 실제로 얼마만큼의 사이즈를 가지고 있는지
	// 전체 화면 기준의 길이로 환산해 반환

	float RightVX() { return GlobalPos().x + size.x * 0.5f;}
	float LeftVX() { return GlobalPos().x - size.x * 0.5f; }
	float TopVX() { return GlobalPos().y - size.y * 0.5f; }
	float BottomVX() { return GlobalPos().y + size.y * 0.5f; }
	//이상의 4개 함수들은 각 영역의 끝자락을 계산해 반환 하는 함수
	//주로 AABB알고리즘에서 사용될 예정



};