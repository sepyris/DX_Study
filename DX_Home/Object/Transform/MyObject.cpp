#include "framework.h"
#include "MyObject.h"

MyObject::MyObject(Float2 p, Float2 s, float a, 
	Float2 size, D3D11_PRIMITIVE_TOPOLOGY t,
	Matrix* parent)
	: Transform(p,s,a,parent)
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
	if (parent == NULL) {
		if (this->parent != parent) {
			this->parent = parent;
		}
	}
	WorldUpdate();
	// ��� ó���� �������� ���̴� ������ ó���� ������ ���·�
	// �� ������Ʈ�� ��ġ ���� ������ ����, ���� ��Ŀ� ������Ʈ

}

void MyObject::Render(Matrix* parent)
{
	if (parent != NULL) {
		WB->Set(*parent);
	}
	else {
		WB->Set(world);
	}
	
	WB->SetVS(0);

	tri->Render();
}
