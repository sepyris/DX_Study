#include "framework.h"
#include "Triangle.h"

Triangle::Triangle(Float2 size, D3D11_PRIMITIVE_TOPOLOGY type)
	: size(size), type(type)
{
	// ����� �ﰢ���� ������ ���Ϳ� �߰�
	vertices.emplace_back(0, size.y * (-2.0 / 3.0), 1.0f, 1.0f, 1.0f);
	vertices.emplace_back(size.x * (0.5f), size.y * (1.0 / 3.0), 1.0f, 1.0f, 1.0f);
	vertices.emplace_back(size.x * (-0.5f), size.y * (1.0 / 3.0), 1.0f, 1.0f, 1.0f);

	// ���� �Ͱ� �ٸ� �� ���������,
	// �������� ���������� ���⼭�� size�� �⺻���� 100, 100�̶�� ���� ����
	// -> ���� �� ���������� �����ǥ�� �ƴ϶� ������ǥ�踦 ��������,
	// Ư�� API ��ó�� ȭ���� ���� �� ���� (0,0)���� ��� �ִٴ� �����μ�
	// ������ ��ǥ�� �����ϰ� �ִٴ� �ǹ�

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	VS = new VertexShader(L"Shader/VertexShader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShader.hlsl", flags);

	VB = new VertexBuffer(vertices.data(), sizeof(Vertex),
							vertices.size());
	CB = new ColourBuffer();
	
}

Triangle::~Triangle()
{
	delete VS;
	delete PS;
	delete VB;
	delete CB;
}

void Triangle::Render()
{
	if (CB->data.colour.x != 1.0f
		|| CB->data.colour.y != 1.0f
		|| CB->data.colour.z != 1.0f)
		// �� �ﰢ���� �����ϰ� �ִ� ��������� RGB�� �� �ϳ��� 1.0�� �ƴ϶��
		// ��, �Ϻ��� ����� �ƴ϶��
		CB->SetPS(0); // �� ������ ������ �ִ� ����� �ƴ� ��������� ����
		// �ȼ� ���̴��� �ѱ��
		
	// VS, PS�� �ý��ۿ� ����ϴ� �κ�
	VS->Set();
	PS->Set();

	// ���̴��� ���ۿ� ����ִ� �����͸� �ѱ��
	// � ������ �׸� ������ ��ġ�� �˸��� �κ�
	VB->Set(type);

	// �״�� ���� �� ���� ������ŭ �׷��޶� ��û�ϴ� �� �ڵ� �ϳ�
	DVC->Draw(vertices.size(), 0);
}
