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
	// TO-DO ) 앞으로 오브젝트를 직접 관리할 일이 있다면
	// 이곳에 그 관리 및 이동 등을 다루는 코드를 작성함
	if (this->parent != parent)
		this->parent = parent;

	WorldUpdate();
	// 모든 처리가 끝났으면 셰이더 측에서 처리가 가능한 형태로
	// 이 오브젝트의 위치 등의 정보를 갱신, 월드 행렬에 업데이트

}

void MyObject::Render()
{
	WB->Set(world);
	WB->SetVS(0);

	tri->Render();
}
