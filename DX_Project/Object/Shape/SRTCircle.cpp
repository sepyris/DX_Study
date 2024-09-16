#include "framework.h"

SRTCircle::SRTCircle(Float2 size, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type)
	: Shape(), type(type), size(size)
{
	float angle = 2 * (float)M_PI;
	// ������ ���� ���� ���� �� ���� ��ġ�� �ﰢ�Լ��� ���� ���ϱ� ����,
	// �� �ﰢ�Լ��� ���� ��ǥ���� ����� �����ϱ� ���� ������ ���� ��
	// �ʱⰪ�� �� �� ������ �ǹ��ϴ� 360����
	// �������� ��ȯ�� ���� 2 * pi ��

	// M_PI��� ������ ����� �̿��ϹǷ�
	// framework.h���� _USE_MATH_DEFINES�� ������ <math.h>�� ������ �ʿ�
	// �츮�� �̹� �̰� ����?

	switch (type)
	// ������ ���� ���빰�� �� ä���� ���������
	// ��Ȳ�� ���� ���� ������ ���� �׸� �ʿ� ����
	// �� �׵θ����� �׸� �ʿ䰡 ����
	// �׷��� �Է¹��� D3D11_PRIMITIVE_TOPOLOGY(=type)�� � ���̳Ŀ� ����
	// �׸��� �׸��� �� ����� ������ �����͸� �ٸ��� ���鵵�� �� ��
	{
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		for (int i = 0; i < vertex_count; i++)
		{
			vertices.emplace_back(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
			// �ﰢ���� ù��° ������ �����, ���� ������ �Է�
			vertices.emplace_back(
				-cos(angle) * this->size.x,
				sin(angle) * this->size.y,
				(float)(angle / (2 * M_PI)), float((2 * M_PI - angle) / (2 * M_PI)), 1.0f
			);
			// �ﰢ�Լ��� ���� Ȯ���� �������� �� �� �ϳ��� �߰�

			angle -= 2 * (float)M_PI / (float)vertex_count;
			// ���� ����

			vertices.emplace_back(
				-cos(angle) * this->size.x,
				sin(angle) * this->size.y,
				(float)(angle / (2 * M_PI)), (float)((2 * M_PI - angle) / (2 * M_PI)), 1.0f
			);
			// �ﰢ�Լ��� ���� Ȯ���� �������� ���� ���� �߰�
		}
		break;
		// �̸� �� 6���� �ﰢ���� �������� �׸��� �ϵ��� �ϰ� ����

	case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
		for (int i = 0; i <= vertex_count; i++)
		{
			vertices.emplace_back(
				-cos(angle) * this->size.x,
				sin(angle) * this->size.y,
				(float)(angle / (2 * M_PI)), (float)((2 * M_PI - angle) / (2 * M_PI)), 1.0f
			);
			angle -= 2 * (float)M_PI / (float)vertex_count;
		}
		// �� ���� �������� �߰��� ������� �Ѵٴ� �� ���� �������鸸 ���������� �߰��ϸ� ��
		break;
	}

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	VS = new VertexShader(L"Shader/VertexShader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShader.hlsl", flags);

	VB = new VertexBuffer(vertices.data(), (UINT)sizeof(Vertex), (UINT)vertices.size());
	CB = new ColourBuffer();
}

SRTCircle::SRTCircle(float radius, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type)
	: SRTCircle(Float2(radius, radius), vertex_count, type)
	// ���� �����ڴ� �ڱ� �ڽ��� �ٸ� �����ڷε� �̿��� �� �ִ�
{
}

SRTCircle::~SRTCircle()
{
	delete VS;
	delete PS;
	delete VB;
	delete CB;
}

void SRTCircle::Render()
{
	if (CB->data.colour.x != 1.0f || CB->data.colour.y != 1.0f || CB->data.colour.z != 1.0f)
		CB->SetPS(0);
	// �÷����ۿ� ����� ������ ����� �ƴ϶��
	// �� �÷����۸� ���̴��� �Է��� ��

	VB->Set(type);
	VS->Set();
	PS->Set();
	DVC->Draw((UINT)vertices.size(), 0);
}