#include "framework.h"
#include "ConstBuffer.h"

ConstBuffer::ConstBuffer(void* data, UINT data_size)
	: data(data), data_size(data_size)
{
	// VertexBuffer�� �����ڿ� �־��� ������ �����ؿ���
	// ��, ���ľ� �� �κ��� �ٸ�

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = data_size;
	// 1) Bytewidth(�뿪��)
	// ��� ���۴� �������� �� �뷮�� �Ű������μ� �ޱ� ������
	// �ƿ� �̸� �״�� �̿�
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	// 2) BindFlags
	// �� ������ ���ó(=�뵵)�� ��Ȯ�� ����
	// ������ ������ �����ϴ� �뵵���� ����� �����ϴ� ���۷� �ٲٴ� ��
	
	// �ٲ��� �ʴ´ٸ� ���� ��ü�� ���������� ��µ��� ����

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;

	DEVICE->CreateBuffer(&bd, &initData, &buffer);
}

ConstBuffer::~ConstBuffer()
{
	buffer->Release();
}


// �������� ����� ���̴� ���ϵ鿡��
// ��� ���۸� ����ϴ� �κ��� ����
// �� �κп� ���̴����� �䱸�ϴ� �԰����μ� �����͸� ������ �� �ֵ���
// ���̴��� "��� ����"�� �� ������ �����͸� ����� ��������
// �Լ��μ� ������ �� �ֵ��� �ϴ� ����
void ConstBuffer::SetVS(UINT slot) // ���� ���̴��� ����� �� ���� �Լ�
{
	DVC->UpdateSubresource(buffer, 0, NULL, data, 0, 0);
	DVC->VSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetPS(UINT slot) // �ȼ� ���̴��� ����� �� ���� �Լ�
{
	DVC->UpdateSubresource(buffer, 0, NULL, data, 0, 0);
	DVC->PSSetConstantBuffers(slot, 1, &buffer);
}
