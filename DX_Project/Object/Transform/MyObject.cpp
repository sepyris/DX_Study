#include "framework.h"
#include "MyObject.h"

MyObject::MyObject(Float2 p, Float2 s, float a, 
	Float2 size, D3D11_PRIMITIVE_TOPOLOGY t)
	: Transform(p,s,a)
{
	tri = new Triangle(size, t);
}

MyObject::~MyObject()
{
	delete tri;
}

void MyObject::Update(Matrix* parent)
{
	// TO-DO ) ������ ������Ʈ�� ���� ������ ���� �ִٸ�
	// �̰��� �� ���� �� �̵� ���� �ٷ�� �ڵ带 �ۼ���
	if (this->parent != parent)
		this->parent = parent;

	WorldUpdate();
	// ��� ó���� �������� ���̴� ������ ó���� ������ ���·�
	// �� ������Ʈ�� ��ġ ���� ������ ����, ���� ��Ŀ� ������Ʈ

}

void MyObject::Render()
{
	WB->Set(world);
	WB->SetVS(0);

	tri->Render();
}
