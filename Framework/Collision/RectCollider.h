#pragma once
class RectCollider : public Collider {

public:
	struct ObbDesc {//���߿� OBB�浹 �˰��򿡼� ����ϴ� ����ü
		Vector2 pos;
		Vector2 Axis[2];
		Vector2 half_size;
	};

private:
	Vector2 size;
	ObbDesc obb_desc;

	// Collider��(��) ���� ��ӵ�
	virtual void CreateLine() override;

	bool isAABB(RectCollider* rect, Vector2* overwrap = NULL);
	bool isOBB(RectCollider* rect);
	bool isAABB(CircleCollider* rect);
	bool isOBB(CircleCollider* rect);

	float separateAxis(Vector2 seperate, Vector2 e1, Vector2 e2);
	//OBB�浹 ó���� ������� ���� ����� �Լ�

public:
	RectCollider(Vector2 size);
	~RectCollider();

	ObbDesc GetObbDesc();

	// Collider��(��) ���� ��ӵ�
	virtual bool isPointCollision(Vector2 point) override;
	virtual bool isCircleCollision(CircleCollider* collider) override;
	virtual bool isRectCollision(RectCollider* collider, Vector2* overwrap = NULL) override;
	
	Vector2 Size() { return size * GlobalScale(); }
	//�� �浹 ������ ȭ�� �������� ������ �󸶸�ŭ�� ����� ������ �ִ���
	// ��ü ȭ�� ������ ���̷� ȯ���� ��ȯ

	float RightVX() { return GlobalPos().x + size.x * 0.5f;}
	float LeftVX() { return GlobalPos().x - size.x * 0.5f; }
	float TopVX() { return GlobalPos().y - size.y * 0.5f; }
	float BottomVX() { return GlobalPos().y + size.y * 0.5f; }
	//�̻��� 4�� �Լ����� �� ������ ���ڶ��� ����� ��ȯ �ϴ� �Լ�
	//�ַ� AABB�˰��򿡼� ���� ����



};