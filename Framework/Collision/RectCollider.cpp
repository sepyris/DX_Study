#include "framework.h"


RectCollider::RectCollider(Vector2 size)
	: size(size)
{
	type = TYPE::RECT;

	CreateLine();
}

RectCollider::~RectCollider()
{
}

void RectCollider::CreateLine()
//�� �浹 ������ ������ ȭ�鿡 ǥ���ϱ� ����
//� ������ ����ϴ��� ���� �ϴ� �κ�
{
	Vector2 half = Size() * 0.5f;

	vertices.emplace_back(-half.x, +half.y);
	vertices.emplace_back(+half.x, +half.y);
	vertices.emplace_back(+half.x, -half.y);
	vertices.emplace_back(-half.x, -half.y);
	vertices.emplace_back(-half.x, +half.y);
	//�ð� �ݴ�������� ������ �������������
	//�ﰢ���� �ƴ϶� ���� �ߴ°��̶� �ð������ ��ų�ʿ䰡 ����

	VB = new VertexBuffer(vertices.data(), sizeof(VertexPos), vertices.size());
}

RectCollider::ObbDesc RectCollider::GetObbDesc()
{
	return ObbDesc();
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
	return false;
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

	//if(overwrap != NULL)
	return isAABB(collider, overwrap);
	//else
	//isOBB(collider);
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
/*O Bounding Box�� ���Ӹ�

*/
{

	return false;
}

bool RectCollider::isAABB(CircleCollider* rect)
{
	return false;
}

bool RectCollider::isOBB(CircleCollider* rect)
{
	return false;
}

float RectCollider::separateAxis(Vector2 seperate, Vector2 e1, Vector2 e2)
{
	return 0.0f;
}
