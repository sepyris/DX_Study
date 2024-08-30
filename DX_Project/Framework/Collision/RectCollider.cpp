#include "framework.h"


RectCollider::RectCollider(Vector2 size)
	: size(size)
{
	type = TYPE::RECT;

	CreateLine();
}

RectCollider::~RectCollider()
{
	delete VB;
}

void RectCollider::CreateLine()
//�� �浹 ������ ������ ȭ�鿡 ǥ���ϱ� ����
//� ������ ����ϴ��� ���� �ϴ� �κ�
{
	Vector2 half = Size() * 0.5f;

	vertices.emplace_back(-half.x, +half.y);
	vertices.emplace_back(-half.x, -half.y);
	vertices.emplace_back(+half.x, -half.y);
	vertices.emplace_back(+half.x, +half.y);
	vertices.emplace_back(-half.x, +half.y);
	//�ð� �ݴ�������� ������ �������������
	//�ﰢ���� �ƴ϶� ���� �ߴ°��̶� �ð������ ��ų�ʿ䰡 ����

	VB = new VertexBuffer(vertices.data(), sizeof(VertexPos), vertices.size());
}

RectCollider::ObbDesc RectCollider::GetObbDesc()
//ȸ���� ���¿����� �浹������ ������ �����ϱ� ���� �ʿ��� �����͸� ��Ƶ� ����ü
{
	obb_desc.pos = GlobalPos();//�浹 ������ ��ü �����󿡼��� ��ǥ
	obb_desc.half_size = Size() * 0.5f;//�浹������ ũ�� �¿� �� ������ ����
	obb_desc.Axis[0] = Right();
	obb_desc.Axis[1] = Up();
	//�� �浹 ������ ���� �ٶ󺸴� ������ �������� ���� ������ ���� ����Ű�� ���� ����

	return obb_desc;
}

bool RectCollider::isPointCollision(Vector2 point)
//�Է¹��� ���� �簢�� ���ο� �ִ��� = �浹�ϴ��� �˻��ϴ� �Լ�
{
	Vector2 half = Size() * 0.5f;
	float left = GlobalPos().x - half.x;
	float right = GlobalPos().x + half.x;
	float top = GlobalPos().y - half.y;
	float bottom = GlobalPos().y + half.y;
	//�� �簢���� ũ�⸦ Ȯ���ѵ�
	//�����¿� ������ ��ǥ�� ���� �����󿡼��� ��ǥ�μ� Ȯ������
	//�ű⿡ ������ ���� ũ�⸦ �̿��� �� �������� ��ǥ,
	//�� �� �簢���� ������ ���

	//�׷��� ���� �����ȿ� �Էµ� ��ǥ�� ����ִ��� �˻�

	if (point.x > left && point.x < right) {
		if (point.y > top && point.y < bottom) {
			return true;//���� �ִٸ� �浹�Ѱ�
		}
	}

	return false;//�׷��� ������ �浹���� ������
}

bool RectCollider::isCircleCollision(CircleCollider* collider)
{
	return isOBB(collider);
}

bool RectCollider::isRectCollision(RectCollider* collider, Vector2* overwrap)
{
	//�簢�� ������ �簢�� ������ �浹�ߴٰ� �Ѵٸ�
	//�̴� ��Ȯ�� � ���°� �Ǵ°�?
	//->�� ��Ȯ�� � ���°� �Ǵ°������� �ٷ�°� �浹 �̷�
	//�� � ������� �浹�� ó���Ұ��̳Ŀ� ����
	//�� �浹 �ߴ� �� ���� �ϴ¹���� ���� ���� �޶����� ��

	//������� �簢���� ���� �浹 �ߴ�,�� ��ġ�� �κ��� �ִٴ� �̾߱��
	//������ �簢���� ������ �Ϻΰ� ������ ������ ħ���ϰ� �ִٴ� �̾߱��
	//�׷��ٸ� ������ �簢���� �����ϴ� �������� ��� �ϳ��� ������ ������ ���ִ� ��Ȳ�̶�� ���� �ϴ°��� ������

	//�׷��Ƿ� �ϴ� ������ �������� Ȯ��,�� �������� �� �ȿ� ���� �ִ����� �˻��ϴ� �˰����� �����ξ�
	//�̸� �̿��� �˻��ϴ� ����� ����

	//�ٸ� �̹���� ���� ���ؼ� ���� ������ �浹�� �ٷ� �ʿ䰡 ����
	
	//�� ����� �ٽ� ���̵��� �̰�:
	//�������ϸ� ���� �浹 ���� ��쿡 �� �簢���� ��� �ϳ��� �������� ������ ���ο� �� �������̴�
	//���� ������4���� �ϳ��� ���濡�� �� �ְų�
	//������ ������4���� �ϳ��� ���� ���� �ְų�
	//�� ���� �ϳ��� �ش� �ȴٸ� �浹�Ѱ��̴�.


	/*
	�̶�� �˰����� ������ ���� ����������,
	�����δ� �������� �׻� ���濡�� ��ġ���� �ʾҴ��� �浹�ϴ� ��Ȳ�� �߻���
	
	->���� �� �˰����� �浹������ ����� ���� ����
	�׷��ٸ� ��� �ؾ� �ϴ°�?
	
	->��밡���ϴٰ� ������ �˰����� �����
	�װ��� AABB�˰���� OBB�˰���

	���� ��� �˰����� ���������� ��Ȳ�� ���� �ٸ���
	�� �ٸ� ��Ȳ�� �Ű������� �Է� �ϳ� ���ĸ� ���� ��� �����ϴ�
	���⼭�� ���ǹ����� ��� �˰����� ����Ұ����� ����

	//�ϴ� �� �ڽ��� ���� �������� ���ѵ�
	Vector2 half = Size() * 0.5f;
	float left = GlobalPos().x - half.x;
	float right = GlobalPos().x + half.x;
	float top = GlobalPos().y - half.y;
	float bottom = GlobalPos().y + half.y;

	Vector2 opp_half = collider->Size() * 0.5f;
	float opp_left = collider->GlobalPos().x - opp_half.x;
	float opp_right = collider->GlobalPos().x + opp_half.x;
	float opp_top = collider->GlobalPos().y - opp_half.y;
	float opp_bottom = collider->GlobalPos().y + opp_half.y;
	//������ ������ ���� ������� ����

	if (collider->isPointCollision(Vector2(left,top))||
		collider->isPointCollision(Vector2(left, bottom)) ||
		collider->isPointCollision(Vector2(right, top)) ||
		collider->isPointCollision(Vector2(right, bottom)) ||

		isPointCollision(Vector2(opp_left, opp_top)) ||
		isPointCollision(Vector2(opp_left, opp_bottom)) ||
		isPointCollision(Vector2(opp_right, opp_top)) ||
		isPointCollision(Vector2(opp_right, opp_bottom))
		) 
	{
		//�׷��� ���� ���� ������ ������ �������� �ϳ��� ������ ������ ħ���ϰ� �ִٸ� 
		return true;//�浹�Ѱ����� ���
	}


	return false;//�ƹ��������� ħ������ �ʰ� �ִٸ� �浹���� �ʾ���
	*/

	if(overwrap != NULL)
		return isAABB(collider, overwrap);
	else
		return isOBB(collider);
}

bool RectCollider::isAABB(RectCollider* rect, Vector2* overwrap)
/*Axis - Aligned Bounding Box�� ���Ӹ�
���� ������ ������-> �浹������ �̷�� ��� ������ ������
�⺻��� �����ϵ��� ������������ ����ϴ� �˰���

�⺻�����δ� �ſ� �����ٴ� ���� ���� ū �����̳�
ȸ������ �ʴ� ��쿡�� ���������� �����Ѵٴ°��� ���� ū ����

*/
{
	float max_left = max(LeftVX(), rect->LeftVX());
	float min_right = min(RightVX(), rect->RightVX());
	float max_top = max(TopVX(), rect->TopVX());
	float min_bottom = min(BottomVX(), rect->BottomVX());
	//2���� �簢���� �浹������ �̿���,
	//���� �� ū ����/�� ��ǥ��
	//���� �� ���� ������/�Ʒ� ��ǥ�� ���

	//�̷��� �Ͽ� �� �簢���� �����ִ� ������ �����Ҽ� �ְ� ��
	//�ٸ� ���� ������ �� ���� ��ü�� ���� �ʿ�� ������
	//�ش� ������ ���μ��� ������ ũ�⸸ ���ϸ� ��
	Vector2 obstackle = Vector2(min_right - max_left, min_bottom - max_top);
	//�̷��� ������� �簢���� ���� ���̸� �˻��Ͽ�
	//���� �ϳ��� 0 ���϶�� �� �簢���� �������� �ʴ´ٰ� �Ǵ��Ҽ� ����
	//�ݴ�� �Ѵ� ������ �׸�ŭ ������ �浹�ϴ� ������ �ִٴ� ��

	if (obstackle.x>0.f&& obstackle.y > 0.f) {
		//�� ������ �������ٸ� = �浹 �ߴٸ�
		if (overwrap != NULL) {
			*overwrap = obstackle;
		}
		// overwrap �� �Լ� �� �� ���Լ��� ȣ���Ѱ�����
		//�浹 ������ ��Ȯ�� ��� �ǳ� �� �����͸� �޾ư��� ����������
		// ���� �̰� �Է� �Ǿ� �ִٸ� ������ ���� �浹 ������ ����� �Է��ϴ½����� ȣ���� ��ġ�� ��ȯ
		return true;
		
	}
	return false;

	/*
	�� ����� �浹���θ� �˻��ϴ� ����� ������ ȸ������ �ʰ�
	������ ���� x��,y��� �����ϴٴ� �� ������ ������� �˻� ���

	�̶�����
	1.���� ���� �ϳ��� ȸ���� �̷����ٸ�
	�װ� ������� ���� ������ �ڵ�δ�
	�׷��Ȱ� ���� �浹������ ��ġ���� �ʰ� �Ǵ°�

	2.��ġ�ϰ� �Ϸ��� �ص�, �� �˰��� ��ü��
	���� ������ ���� �̿��ؼ� �˻��ϴ°��� �⺻ ������ ���� �˰����̶�
	���� ȸ���� ������ �ٸ��� �� �˰����� �״�� ���� ����

	->���� ������ AABB�δ� 2D������ ȸ������ ���� �簢�������� �˻縸 ����
	


	*/
}

bool RectCollider::isOBB(RectCollider* rect)
/*Oriented Bounding Box�� ���Ӹ�
���⼺ ��� ���� - ȸ�� ������ ���󰡴� �浹 ���� ó����

�� ��ü�� � �࿡ "����(�翵)"��������
������ �� ��ü�� ���� ��ġ�� �ʴ� �ٸ�
�� ��ü ���̸� �������� �Ϻ��� �и� ��Ű�� ������ �и����� �ϳ��� �ִ°��̴�
��� ���� �׷� �и����� �����ϴ����� �������� ���� �˻��ؼ�
�ϳ��� �����Ѵٸ� ���� �浹���� �ʰ� �и��Ȱ�
�������� �ʴ´ٸ� �浹�� ���̶�� �Ǵ��ϴ� �浹 �˻� �˰���
*/
{
	
	ObbDesc this_obb = GetObbDesc();
	ObbDesc rect_obb = rect->GetObbDesc();

	Vector2 nea1 = this_obb.Axis[0];
	Vector2 nea2 = this_obb.Axis[1];
	Vector2 ea1 = nea1 * this_obb.half_size.x;
	Vector2 ea2 = nea2 * this_obb.half_size.y;

	Vector2 neb1 = rect_obb.Axis[0];
	Vector2 neb2 = rect_obb.Axis[1];
	Vector2 eb1 = neb1 * rect_obb.half_size.x;
	Vector2 eb2 = neb2 * rect_obb.half_size.y;
	Vector2 distance = this_obb.pos - rect_obb.pos;

	//�׽�Ʈ��:nea1(A.RIGHT())
	float lengthA = ea1.GetLength();
	float lengthB = separateAxis(nea1, eb1, eb2);
	float length = abs(Vector2::Dot(distance, nea1));
	if (length > lengthA + lengthB) {
		return false;
	}

	//�׽�Ʈ��:nea2(A.UP())
	lengthA = ea2.GetLength();
	lengthB = separateAxis(nea2, eb1, eb2);
	length = abs(Vector2::Dot(distance, nea2));
	if (length > lengthA + lengthB) {
		return false;
	}
	//�׽�Ʈ��:neb1(B.Right())
	lengthA = eb1.GetLength();
	lengthB = separateAxis(neb1, ea1, ea2);
	length = abs(Vector2::Dot(distance, neb1));
	if (length > lengthA + lengthB) {
		return false;
	}
	//�׽�Ʈ��:neb2(B.Up())
	lengthA = eb2.GetLength();
	lengthB = separateAxis(neb2, ea1, ea2);
	length = abs(Vector2::Dot(distance, neb2));
	if (length > lengthA + lengthB) {
		return false;
	}
	return true;
}

bool RectCollider::isAABB(CircleCollider* circle)
{
	//�̹� ���� �ڵ尡 ������ �״�� �̿��ϴ� ���
	return circle->isRectCollision(this);
	//�ٸ� �� Ŭ�������� ����ؾ� �ϴ� ����� �ٸ� Ŭ�������ٰ� �ðܹ����� ���� �Ǳ⿡
	//S.O.L.I.D��Ģ�� ����å�ӿ�Ģ�� �����ϰ� ��
	//�̶����� CircleCollider�� ������ ����� �� ��ɵ� ������ ����� ������ ���� ����
	//
	// ���� �ڵ带 ������ ���ʿ� �°� ��ġ�°� ����
	//

} 

bool RectCollider::isOBB(CircleCollider* circle)
{
	//CircleCollider���� ���� �ڵ带 �״�� ���� �ؿ�����
	//���� ��ζ�� �� �簢���� ���� �°� ���ľ� �� �ʿ䰡 ����
	//�׷��� ���ʿ� �� �ڵ� ��ü�� ���� �� �Լ��� ȣ���ϴ� Transform�� ������ �̿��ϹǷ�
	//���� ��ĥ ����������



	Matrix S = XMMatrixScaling(circle->scale.x, circle->scale.y, 1.0f);
	Matrix R = XMMatrixRotationZ(circle->rot.z);
	Matrix T = XMMatrixTranslation(circle->pos.x - pos.x, circle->pos.y - pos.y, 0.0f);

	Matrix circle_world = S * R * T;

	circle_world *= XMMatrixRotationZ(-circle->rot.z);

	XMFLOAT4X4 temp_matrix;
	XMStoreFloat4x4(&temp_matrix, circle_world);
	//������� ���忡�� �����͸� �����ϱ� ���� FLOAT4x4��Ŀ� ����

	Vector2 circle_obb_center = Vector2(temp_matrix._41, temp_matrix._42);

	//������ ������ �׷��� ��ġ�� ����� ���� ��ǥ�� �̿��ؼ�
	//������ ȸ������ �ʰ� �ִ� �簢���� �浹�ϴ��� �ƴ����� �˻�

	//����ϴ� �ڵ�� AABB������ ���� ����
	//�ٸ� �ٲ��� �ϴ� �κ��� 2����
	Vector2 half = Size() * 0.5f;
	Vector2 closest;

	//1.���� ��ġ�� �簢���� ���带 �������� �ٲ�� ��������
	//�� �ٲ� ��ġ�� �̿��ϵ��� �����ؾ���

	//���� ó���ϴ� ������ �簢���� �߽��� ���������� ��� ��Ȳ
	// ���� �簢���� pos���̶������ �̿����� �ʰ�
	//�׳� ������ �������� ����ϱ⸸ �ϸ� ��
	if (circle_obb_center.x < -half.x) {
		closest.x = -half.x;
	}
	else if (circle_obb_center.x > half.x) {
		closest.x = half.x;
	}
	else {
		closest.x = circle_obb_center.x;
	}

	if (circle_obb_center.y < -half.y) {
		closest.y = -half.y;
	}
	else if (circle_obb_center.y > half.y) {
		closest.y = half.y;
	}
	else {
		closest.y = circle_obb_center.y;
	}


	//2.���ʿ��� ���� ���� ��ġ�� �̿��ϴ� �˰����� isPointCollision��
	//����Ҽ� ����
	//���� �簢���� ȸ���� �°� ��ġ�� �̵������Ƿ�
	//���� ��ġ�� �������� ����ϴ� �� �Լ��� �״�� ���� ���� ����
	//����,���⼱ ���� ����� ����� �Ѵ�
	if ((circle_obb_center - closest).GetLength() < circle->GetRadius()) {
		return true;
	}
	return false;
}

float RectCollider::separateAxis(Vector2 seperate, Vector2 e1, Vector2 e2)
//���� �׽�Ʈ�ϰ� �ִ� ���� ������ �̿�,
//�ش� ���� ������� �ʴ� ����� ������������
// ���������� �翵 ������ ��������� ���̸� �����ϴ� �Լ�
//
{
	float r1 = abs(Vector2::Dot(seperate, e1));
	float r2 = abs(Vector2::Dot(seperate, e2));
	//seperate��� �������� ����� ������ ����Ű�� ���� ���͸� �������� �Ͽ�
	//e1��e2�� ���� �ش� ���� �������� �󸶸�ŭ�� ��ǥ�� ������ �ִ���
	//������ ���� ����ϴ� ����

	return r1 + r2;
	//e1,e2�� ���� ������� 2�� ���͸� �̿��ؼ� ���� ���̴�
	//���������� �翵�� �� ���̰� �� ���� �Ǵ°�
}
/*
����:

1)��->�簢�� �浹 ���� ������ ��������
������ �簢��->������ �浹���� �Լ��� ��������� ���� ��Ȳ
�̰� ������

��Ʈ:�� �״�� �����ϴ� ����� ���� ����� ������ ���α׷��� �������� ��¦ �� ���� ��� 2���� ����� ����
��� ����� ���� �ϴ� �������� ����


2)���󿡼� ���� ����� ����
���� ���� �����?

����:������ ���� ȯ������ �����
1.��ֹ��� �ε��� ��� 1�ʵ��� �÷��̾��� ���� ���ߴٰ� ������������ ���ƿð� + b���� ������ �������� ���� ���� �ڸ��� ���ư���
2.�������� ȭ��(=����) ��ü�� ��� 3���� �־ �� 3���� ��� �Ծ���߸� Ŭ���� �Ҽ� �ֵ��� �Ұ�
(3���� �� �Ծ�� ������� ���������� ������ ���� �ǵ��� �ص� �ǰ�
3���� �� ���� ������ ������ ���� �ǵ��� �ص� �ǰ�
3���� �� �Դ°����� ����� ������ ���� ��ֹ��� ��������� �ص� �ǰ� ����� ����)

��Ʈ - �������� �Ծ����� �ƴ����� ���θ� �Ǵ��� ����� �������̳�
���� �������� �׳� ȭ�� ������ ġ���δ½��� �̿��ϸ� ū ������ ������
�ٸ� ����� �ᵵ �ǳ� �׷��� ���̵��� �������� ����

�÷��̾�� �ݵ�� Ű����θ� �����ϼ��ְ� �Ұ�

*/