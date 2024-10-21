#include "framework.h"
#include "IndexBuffer.h"



IndexBuffer::IndexBuffer(void* data, UINT count)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(UINT) * count;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//VertexBuffer�� ũ�� �ٸ��� ������
	//� �������� ����ϴ� �κ��� �ٲ������

	//�߰��� ���̴����� �ٷ�� �������� �ε����� �翬�� UINT�ϼ��ۿ� ������
	//�� ������ ũ��� �Է¹��� �����Ϳ� ����ִ� �ڷ�� * sizeof(UINT)�� ��

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;

	DEVICE->CreateBuffer(&bd, &initData, &buffer);
}

IndexBuffer::~IndexBuffer()
{
	buffer->Release();
}

void IndexBuffer::Set()
{
	DVC->IASetIndexBuffer(buffer,DXGI_FORMAT_R32_UINT,0);
}
