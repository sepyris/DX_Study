#include "framework.h"

VertexBuffer::VertexBuffer(void* data, UINT s, UINT count)
	: stride(s), offset(0)
{
	// ������ �� �������� ���۸� ����� ����ߴ� �κ��� ����,
	// �� Ŭ������ �°� �� 2���� ���ļ� ���

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = stride * count;
	// 1) Bytewidth(�뿪��)
	// �������� �� ���� ���� �ϳ��� ũ�� * ������ ������ ���� üũ�߾��µ�
	// ���⼭�� �� ���� �ϳ��� �뷮�� ���� �����ص� stride�� �̿�
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;
	// 2) pSysMem
	// ���� �ʿ����� �����ڿ��� �������� ���Ϳ� �־�ΰ�
	// �̸� ����ϴ� ���̾��µ�
	// ���⼱ �������� �Ű������μ� �ƿ� �����Ͱ� ����ִ� �ּҸ� �޾�����
	// �̸� �״�� �̿��ϵ��� �ǳ���
	
	// void*�� ����ȯ�� �ؾ� ����� �� �ִٴ� ����
	// ���ʿ� � ���������� �м��� ����� ���� ���̴� ���� �ǳ״� �̻� ���ǹ�

	DEVICE->CreateBuffer(&bd, &initData, &buffer);
}

VertexBuffer::~VertexBuffer()
{
	buffer->Release();
}

void VertexBuffer::Set(D3D11_PRIMITIVE_TOPOLOGY type)
{
	DVC->IASetVertexBuffers
	(0, 1, &buffer, &stride, &offset);
	DVC->IASetPrimitiveTopology(type);
	// ������ Scene���� ������Ʈ�� ������ �ִ� ������ ������ ����ߴ� ��
	// �� Ŭ�������� �˾Ƽ� ���� ó���ϵ��� ������
}
