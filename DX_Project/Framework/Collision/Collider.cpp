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
//�� Ŭ������ ���� �����Լ��� �ִ� �߻� Ŭ�����̹Ƿ�
//�� Ŭ���� ��ü�� �ν��Ͻ��� �����Ҽ� ����
//������ ���ǵǾ� �ִ� ���������� ��ϵ� �ڽ� Ŭ���������� �� �Լ��� ȣ�� �ȴٴ� �ǹ�
//������ �� Ŭ���� ���ο��� ���� �����Ҵ��� ���� ���� ����� �̿��ص�
//�ƹ��� ������ �������̶� Ȯ�� ����
{
	if (!is_active) {//�� ������Ʈ�� Ȱ��ȭ�� ��Ȳ�� �ƴϸ� �ƿ� ��� ��ü�� ���� �ʰ� �����.
		return;
	}
	WB->Set(world);
	WB->SetVS(0);
	CB->SetPS(0);

	//�������� ���� TRIANGLESTRIP�� ����
	VB->Set(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//VB->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	VS->Set();
	PS->Set();
	DVC->Draw(vertices.size(), 0);
}

bool Collider::isCollision(Collider* collider, Vector2* overwrap)
{
	
	switch (collider->GetType())
		//�Է¹��� �浹 ������ ������ ����
		//����ϴ� �浹 ���� ����� ���� �ٸ��� ������
		//�б⹮���� Ÿ�Կ� ���� �ٸ� �Լ��� ȣ����
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

