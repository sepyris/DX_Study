#include "framework.h"

CircleCollider::CircleCollider(float rad)
	:radius(rad)
{
	type = TYPE::CIRCLE;
	CreateLine();
}

CircleCollider::~CircleCollider()
{
	delete VB;
}
bool CircleCollider::isPointCollision(Vector2 point)
{
	//���̶�°��� ���� ��ü��
	//�߽ɿ��� ������ ��ŭ ������ �ִ� ���� ����
	//�׷��ٸ� �� �����ݺ��� ���� �� ������ �ִٸ�
	//�� �ȿ� �ִٴ� �̾߱Ⱑ ��
	return (GlobalPos()-point).GetLength() < radius;
	//�� �߽ɰ� �Է¹��� ������ �Ÿ��� ���ؼ�
	//�� �Ÿ��� ���������� ū�� ������ ���θ� bool�� ��ȯ
	//���������� �۴ٸ� ���ȿ� ���°�
	//ũ�Ⱑ ���ų� ũ�ٸ� �浹���� ������
}
bool CircleCollider::isCircleCollision(CircleCollider* collider)
{
	//�� ���� ���� ������ �Ÿ��� 
	//�� ���� �������� ���Ѱͺ��� �۴ٸ�
	//= �� ������ �������� ���θ� ���� �������� ��ġ�� �κ��� �ִٸ� �浹�Ѱ�
	Vector2 dir = GlobalPos() - collider->GlobalPos();

	return dir.GetLength() < radius + collider->GetRadius();
}

bool CircleCollider::isRectCollision(RectCollider* collider, Vector2* overwrap)
{
	if (overwrap != NULL)
		return isAABB(collider);
	else
		return isOBB(collider);

	return false;
}

void CircleCollider::CreateLine()
{
	float angle = (float)(2 * M_PI);	
	for (int i = 0; i <= 50; i++)
	{
		vertices.emplace_back(-cos(angle) * radius, sin(angle) * radius);
		vertices.emplace_back(cos(angle) * radius, -sin(angle) * radius);
		angle -= (float)(2 * M_PI) / 50.0f;
	}
	VB = new VertexBuffer(vertices.data(), (UINT)sizeof(VertexPos), (UINT)(vertices.size()));
}

bool CircleCollider::isAABB(RectCollider* collider)
//�簢�������� AABB�ʹ� ������ ���� ������ �ƴϳ�
//�簢���� ������� �������� �̿��ϴ°� ��ü�� ����̴�
//AABB��� ���θ��� ���� ��
{


	Vector2 half = collider->Size() * 0.5f;
	/*
	Vector2 closest; // ���� �簢�� ���̿� ���� ����� �Ÿ�
	
	if (pos.x < collider->pos.x - half.x) {
		//���� �߽����� ������ ���ʳ����� �� ���ʿ� �ִٸ�
		closest.x = collider->pos.x - half.x;
		//������ �簢���� ���� ����� ������ x��ǥ�� �簢���� ���ʳ�(�̶� ����)
		//���� �̰ͺ��� �� �ִٸ� ���ʿ� �浹�� ���� ����
	}
	else if (pos.x > collider->pos.x + half.x) {
		//�� �ݴ�� ������ ������ �� ������ �̶��
		closest.x = collider->pos.x + half.x;
		//���� ������ �¿� ����
	}
	else {
		//�Ѵ� �ƴ�, �� ���� �߽����� �簢������ x��ǥ ���� ���� �ִ� ���
		closest.x = pos.x;
	}

	//���� ������ y��ǥ�� ���ؼ��� �ݺ�
	if (pos.y < collider->pos.y - half.y) {
		closest.y = collider->pos.y - half.y;
	}
	else if (pos.y > collider->pos.y + half.y) {
		closest.y = collider->pos.y + half.y;
	}
	else {
		closest.y = pos.y;
	}

	//�׷��� ���� �簢���� ���ο��� ���� ���� ����� ���� �� ���ο� �����ϴ�����
	//�˻��ϴ� ������� �簢���� ���� �浹�ϴ��� üũ�ϸ� ��


	if (isPointCollision(closest)) {
		return true;
	}

	return false;

	*/

	// ������Ͱ� AABB
	//���ʿ����� �ڵ尡 ��
	//
	if (pos.x > collider->pos.x - half.x &&
		pos.x < collider->pos.x + half.x &&
		pos.y > collider->pos.y - half.y - GetRadius() &&
		pos.y < collider->pos.y + half.y + GetRadius()) {
		return true;
	}
	if (pos.x > collider->pos.x - half.x - GetRadius() &&
		pos.x < collider->pos.x + half.x + GetRadius() &&
		pos.y > collider->pos.y - half.y &&
		pos.y < collider->pos.y + half.y) {
		return true;
	}
	float left = collider->GlobalPos().x - half.x;
	float right = collider->GlobalPos().x + half.x;
	float top = collider->GlobalPos().y - half.y;
	float bottom = collider->GlobalPos().y + half.y;

	if (isPointCollision(Vector2(left,top)) ||
		isPointCollision(Vector2(left, bottom)) || 
		isPointCollision(Vector2(right, top)) || 
		isPointCollision(Vector2(right, bottom))) {
		return true;
	}

	return false;
}

bool CircleCollider::isOBB(RectCollider* collider)
//���� �簢�������� OBB�ʹ� �ٸ���,
//�׷��� �⺻������ ū���� ��Ѥ��ش� AABB�ʹ� �ٸ���
//������ �̷� ��ü�� ������ �ٸ�
//���⼭ OBB��� ���°� �׳� �ܼ��ϰ� �簢���࿡�� ó��
//ȭ���� �����ϴ� �˰����̶�� ���� �� �ϳ���

//������ ���̵��� �簢�� �浹�� OBB�̷п� ���� �ξ� ������
//�簢���� ȸ���� ������ �࿡ �������� �������� �ʾƼ� ����� �����Ѱ��̴�
//�ƿ� �� �밢������ ����� ���� ������ ��ü������ �ƴ�
//�簢���� ���� ��Ȯ�� �簢���� ���� ����� �������� 
//��� ���� ��ȯ ���Ѽ� ����ϸ� �Ǵ°;ƴѰ� ��� �߻�
{
	//�ϴ��� ���ο� ���带 ����� ���� �ʿ��� �۾��� ����
	Matrix T = XMMatrixTranslation(pos.x - collider->pos.x,
		pos.y - collider->pos.y,0);
	//�ٸ� ��ĵ��� Circle�� Transform�� ������ �ִ� ����� �̿��ص� �ǳ�
	//T��ĸ�ŭ�� ��ġ�� ������ ����� �̿��ؾ� ��

	Matrix circle_world = S * R * T;
	circle_world *= XMMatrixRotationZ(-collider->rot.z);
	//�׷��� ���� ����� ����,
	//�� �������� �簢���� �������ִ�������ŭ�� �߰��� ȸ�� ���Ѽ�
	//�簢���� ����� ������ x,y�࿡ �����ϵ��� �����

	XMFLOAT4X4 temp_matrix;
	XMStoreFloat4x4(&temp_matrix, circle_world);
	//������� ���忡�� �����͸� �����ϱ� ���� FLOAT4x4��Ŀ� ����

	Vector2 circle_obb_center = Vector2(temp_matrix._41, temp_matrix._42);

	//������ ������ �׷��� ��ġ�� ����� ���� ��ǥ�� �̿��ؼ�
	//������ ȸ������ �ʰ� �ִ� �簢���� �浹�ϴ��� �ƴ����� �˻�

	//����ϴ� �ڵ�� AABB������ ���� ����
	//�ٸ� �ٲ��� �ϴ� �κ��� 2����
	Vector2 half = collider->Size() * 0.5f;
	Vector2 closest;

	//1.���� ��ġ�� �簢���� ���带 �������� �ٲ�� ��������
	//�� �ٲ� ��ġ�� �̿��ϵ��� �����ؾ���

	//���� ó���ϴ� ������ �簢���� �߽��� ���������� ��� ��Ȳ
	// ���� �簢���� pos���̶������ �̿����� �ʰ�
	//�׳� ������ �������� ����ϱ⸸ �ϸ� ��
	if (circle_obb_center.x <  - half.x) {
		closest.x =  - half.x;
	}
	else if (circle_obb_center.x >  + half.x) {
		closest.x =  + half.x;
	}
	else {
		closest.x = circle_obb_center.x;
	}

	if (circle_obb_center.y <  - half.y) {
		closest.y =  - half.y;
	}
	else if (circle_obb_center.y >  + half.y) {
		closest.y =  + half.y;
	}
	else {
		closest.y = circle_obb_center.y;
	}


	//2.���ʿ��� ���� ���� ��ġ�� �̿��ϴ� �˰����� isPointCollision��
	//����Ҽ� ����
	//���� �簢���� ȸ���� �°� ��ġ�� �̵������Ƿ�
	//���� ��ġ�� �������� ����ϴ� �� �Լ��� �״�� ���� ���� ����
	//����,���⼱ ���� ����� ����� �Ѵ�
	if ((circle_obb_center - closest).GetLength() < GetRadius()) {
		return true;
	}
	return false;

	/*
	if (isPointCollision(closest)) {
		return true;
	}

	return false;
	*/
}

