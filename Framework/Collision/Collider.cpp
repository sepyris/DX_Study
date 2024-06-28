#include "framework.h"
#include "Collider.h"

Collider::Collider()
{
	VS = new VertexShader(L"Shader/VertexShader/VertexShaderPos.hlsl", +1, D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);
	PS = new PixelShader(L"Shader/PixelShader/PixelShaderPos.hlsl");

	CB = new ColourBuffer();
	CB->data.colour = { 0,1,0,1 };

	WB = new MatrixBuffer();
}

Collider::~Collider()
{
	delete VS;
	delete PS;
	delete CB;
	delete WB;
}

void Collider::Render()
//이 클래스는 순수 가상함수가 있는 추상 클래스이므로
//이 클래스 자체의 인스턴스가 존재할수 없음
//정점이 정의되어 있는 정상적으로 등록된 자식 클래스에서만 이 함수가 호출 된다는 의미
//따라이 이 클래스 내부에서 아직 동적할당이 되지 않은 멤버를 이용해도
//아무런 문제가 없을것이라 확신 가능
{
	WB->Set(world);
	WB->SetVS(0);
	CB->SetPS(0);

	VB->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	//정점들을 선만 그려서 출력하도록 함

	VS->Set();
	PS->Set();
	DVC->Draw(vertices.size(), 0);
}

bool Collider::isCollision(Collider* collider, Vector2* overwrap)
{
	return false;
}

