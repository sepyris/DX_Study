#include "framework.h"
#include "Collider.h"

Collider::Collider()
{
	VS = new VertexShader(L"Shader/VertexShader/VertexShaderPos.hlsl", +1, D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);
	PS = new PixelShader(L"Shader/PixelShader/PixelShaderPos.hlsl");

	CB = new ColourBuffer();
	CB->data.colour = { 0.7f,0.7f,0.99f,0 };

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
	if (!is_active) {//이 오브젝트가 활성화된 상황이 아니면 아예 출력 자체를 하지 않게 만든다.
		return;
	}
	WB->Set(world);
	WB->SetVS(0);
	CB->SetPS(0);

	//색입히기 위해 TRIANGLESTRIP로 변경
	VB->Set(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//VB->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	VS->Set();
	PS->Set();
	DVC->Draw(vertices.size(), 0);
}

bool Collider::isCollision(Collider* collider, Vector2* overwrap)
{
	
	switch (collider->GetType())
		//입력받은 충돌 판정의 종류에 따라서
		//사용하는 충돌 판정 방식이 서로 다르기 때문에
		//분기문으로 타입에 따라 다른 함수를 호출함
	{
	case TYPE::RECT: {
		return isRectCollision((RectCollider*)collider, overwrap);
	}
	case TYPE::CIRCLE: {
		return isCircleCollision((CircleCollider*)collider);
	}
	default:
		return false;
	}
}

