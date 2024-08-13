#pragma once
class CircleCollider : public Collider {
public:
	
private:
	float radius;
	// ���⼭�� Ÿ���� �ٷ��� �ʰ� ���� �ٷ�
	//�� ��� ���� �������� ���ϴ°����� ���� ���� ����

	

	// Collider��(��) ���� ��ӵ�
	virtual void CreateLine() override;

	bool isAABB(RectCollider* collider);
	bool isOBB(RectCollider* collider);
	//�簢�� �浹 �������� �浹���θ� ������ ����ϴ� �Լ���
	//���⼭ AABB��� �����ֱ� �ѵ� ��¥ AABB�浹�� �ƴϱ�� ��
	//�׳� ȸ������ ���� �簢���� �浹�Ҷ��� �̷��Ե� �Ҽ� �ִ� ��°� �����ֱ� ���ظ����а�

	//�����δ� OBB���� �ַ� �̿��ϰ� �� ��

	//���� �簢���� �浹 ������ ȸ���� ����ؾ� ������
	//���� �浹 ������ ���ʿ� ���̶� ȸ���ص� �� �Ȱ����Ƿ� ����� �ʿ䰡 ����

	//�׷��� AABB,OBB�� CircleCollider���ο��� �簢���� �浹�Ҷ��� ����

public:
	CircleCollider(float rad);
	~CircleCollider();

	float GetRadius() {
		return radius * min(GlobalScale().x, GlobalScale().y);
		//�� �浹������ �׻� 1,1�������� �����ٰ� �����Ҽ� ����
		//�׷��� �����ϰ����� ���� ���� ��׷��� ���,
		//��� ����ִ� ������ �浹������ ����
		//scale�� 2�� ���߿� �� ���� ������ �������� ����
	}

	// Collider��(��) ���� ��ӵ�
	virtual bool isPointCollision(Vector2 point) override;
	virtual bool isCircleCollision(CircleCollider* collider) override;
	virtual bool isRectCollision(RectCollider* collider, Vector2* overwrap = NULL) override;
	
};