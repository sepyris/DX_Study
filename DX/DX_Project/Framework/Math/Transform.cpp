#include "framework.h"

Transform::Transform(Vector2 p, Vector2 s, float a, Matrix* parent)
	: pos(p), scale(s), rot(Float3(0.0f, 0.0f, a)), parent(parent), is_active(true)
{
	/*
	// �� �����ڿ�����
	// SRT ��ȯ ����� ����� �̸� �����ص�

	S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	R = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	T = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	
	world = S * R * T;

	�� ������� ���� WorldUpdate�� ȣ���ؼ� �� �����̹Ƿ� ���⼱ ���� ����
	*/

	world = XMMatrixIdentity();
	// ������ķ� world ��� �ʱ�ȭ

	right = Vector2(1, 0);
	up = Vector2(0, -1);
	// �����ʰ� ���� ����Ű�� ���� ���� �ϴ��� �ʱ�ȭ

	WB = new MatrixBuffer();
	
	WorldUpdate();
	// ���� ������� ������� �̿��Ͽ� �ʱ�ȭ
}

Transform::~Transform()
{
}

void Transform::WorldTransform(Matrix* parent)
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	Matrix R = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	Matrix T = XMMatrixTranslation(pos.x, pos.y, 0.0f);

	world = S * R * T;

	if (parent != NULL)
		world *= *parent;
}

void Transform::WorldUpdate()
{

	S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	/*
	������Ʈ�� Scale(=ũ��)�� ��ķ� ����� ����
	�� �Լ��� Transform�� ��ϵ� scale�� 4X4 ����� ���·� ��ȯ�����ִ� �Լ�
	
	�����δ� ������ ���� ����� ����
	scale.x = a, scale.y = b, scale.z = c�� �ϸ�
	( a 0 0 0 )
	( 0 b 0 0 )
	( 0 0 c 0 )
	( 0 0 0 1 )
	���� ���� ����� �����ؼ� ��ȯ
	*/

	R = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	//R = XMMatrixRotationZ(rot.z);
	/*
	Ʈ�������� 3�� �� ������ ȸ������ ��Ŀ� ����
	...�ؾ� �ϳ�, �츮�� 3�� �� ���θ� ���� �ʰ�
	z�� �ϳ��� �� ���̱� ������ ���� �Լ� ��� �Ʒ��� �Լ��� �����
	(3D�� �Ѿ�� �ȴٸ� �Ʒ��� �ƴ϶� ������ ��� ��)

	�Ʒ��� �Լ��� ������ � ���� ��ȯ�ϴ��������� ����
	���� �Լ��� �����δ� 3���� ����� ����� �̸� ���� ���� ����� ��ȯ�Ѵٸ�
	�Ʒ��� �Լ��� �� ��������� 3�� ��� �� z�࿡ �����ϴ� ������ �ϳ�����
	���� ��ȯ�ϴ� �Լ�

	�Ʒ��� �Լ��� rot.z = a��� ������ ������ ���� ����� �������
	( cos(a) -sin(a) 0 0 )
	( sin(a) cos(a)  0 0 )
	(   0       0    1 0 )
	(   0       0    0 1 )
	�̷� ������ Z�� �� ��ü�� �ö�Ÿ�� �ʴ� �κ���
	11, 12, 21, 22�� ���� �ﰢ�Լ��� ����Ǵ� ������ �۵���
	�ٸ� �Լ���(X,Y) ���� ���������� ��ġ�� �ٸ���
	*/
	T = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	/*
	������Ʈ�� "����", �� "�̵�"�� ��Ŀ� ����
	�׳� ������ ���� ��ǥ�� ���� �̵��� �� ����� ���� �����Ѵٰ� ���� OK

	( 1 0 0 0 )
	( 0 1 0 0 )
	( 0 0 1 0 )
	( x y z 1 )
	��ǥ�� ���� ���� ���� ����� ��������� ��
	*/

	P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
	IP = XMMatrixInverse(NULL, P);
	// �ǹ��� ����ϴٰ� �������� �� SRT ��ȯ ��Ŀ� �߰��ؾ� �� 2�� ���
	// P : T�� ���� ������ ������ �ϳ�,
	// �� Ʈ�������� �߽����� �ƴ� �ٸ� �������� ȸ���� �ϰڴٴ� �̾߱�
	// IP : P�� �����
	// ���������� P�� ������� �̸� ���ص׾� ������ ������ �ʱ� ����

	// Ư���� �ǹ��� ���� �������� ������ ���� ����� ���������
	// ������ �Ű澲�� �ʾƵ� OK

	world = IP * S * R * T * P;
	// �ǹ����� �����ϸ� ���� ���� �������

	// ���� �θ� �����ϴ� Ʈ�������̸�
	if (parent != NULL)
		world *= *parent;

	// ������� World ����� ���ϴ� �����̾���
	// �� �ں��ʹ� �� �ڿ� �� Ʈ�������� ������ �ڷ����
	// �� ��Ŀ��� �����ϴ� ����

	WB->Set(world);

	XMStoreFloat4x4(&mat_world, world);
	// 4x4 ��ķ� �̷��� �����Ϳ��� �����͵��� ����,
	// XMFloat4x4 �ڷ������� �̷��� ��Ŀ� �� ������ �����ϴ� �Լ�

	right = Vector2(mat_world._11, mat_world._12);
	up = Vector2(mat_world._21, mat_world._22);
	// �� Ʈ�������� ���� �ִ� ������ �������� ���� �������� ������
	// (= �� ������ �� ������Ʈ�� ȸ���� ���� 
	// ���� �������� ������ �޶��� �� �ֱ� ������ �������ϴ� ��)

	XMVECTOR outS, outR, outT;
	// ��ȯ �Ϸ�� ���� ��Ŀ��� ������ Scale, Rotation, Translocation �����͸�
	// ������ ����

	XMMatrixDecompose(&outS, &outR, &outT, world);
	// ���� ��Ŀ��� �����и� ����, ������ ������ �ش� �����͵��� ����
	XMStoreFloat2(&global_scale, outS);
	// ���� �̸��� 4x4 ������ ����������, �Ǽ� 2���� �̷��� �����͸� ����
}
