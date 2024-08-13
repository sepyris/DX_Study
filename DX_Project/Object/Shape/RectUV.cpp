#include "framework.h"

RectUV::RectUV(Vector2 size, Vector2 start_uv, Vector2 end_uv, D3D11_PRIMITIVE_TOPOLOGY type)
	:Shape(),type(type)
{
	Float2 half_size = Float2(size.x / 2.0f, size.y / 2.0f);
	//�� ������ �Է¹��� ũ�⸦ �������� �ɰ���
	//�̸� �������� ��ġ�� �����ϱ� ���� ������ ���

	Float2& hf = half_size;
	//���۷��� ����� �̿��ؼ� �� half_size��� ������ hf��� ������ ����
	
	vertices_uv.emplace_back(-hf.x, -hf.y, start_uv.x, start_uv.y);
	vertices_uv.emplace_back(+hf.x, -hf.y, end_uv.x, start_uv.y);
	vertices_uv.emplace_back(-hf.x, +hf.y, start_uv.x, end_uv.y);
	vertices_uv.emplace_back(-hf.x, +hf.y, start_uv.x, end_uv.y);
	vertices_uv.emplace_back(+hf.x, -hf.y, end_uv.x, start_uv.y);
	vertices_uv.emplace_back(+hf.x, +hf.y, end_uv.x, end_uv.y);
	//���� ���� �������� �Է���
	//start_uv,end_uv :���� ���õ� �ؽ��� �����Ϳ��� ����κк��� ����κб����� ����ϰڴٴ¶�
	//�� ������ 0~1����
	//2D���� 0,0�� �ؽ�ó�� ������ ��
	//1,1�� �����ʾƷ���
	//�� ����Ʈ���� �ؽ���(�̹���)��ü�� �̿��ϰڴٴ� ���� ��
	// 
	//�ٸ� 0�� 1�� ���� ����ٰ� �ؼ� ������ �߻������� �ʴ´�
	//�� �׷��� �Ǵ����� CreateSamplerState�Լ����� ����

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	VS = new VertexShader(L"Shader/VertexShader/VertexShaderUV.hlsl",2,flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShaderUv.hlsl");

	VB = new VertexBuffer(vertices_uv.data(), sizeof(VertexUV),
		vertices_uv.size());
	CB = new ColourBuffer();

}

RectUV::~RectUV()
{
	delete VS;
	delete PS;
	delete VB;
	delete CB;
}

void RectUV::Render()
{
	CB->SetPS(0);
	VB->Set(type);
	VS->Set();
	PS->Set();
	DVC->Draw(vertices_uv.size(), 0);

	//�������� �̷�� �� ��ü�� �̹����� ��� ����϶�°������� �����Ǿ� ������
	//�װ� �׳� �̿��ϸ� ok

}
