#include "framework.h"
#include "IndexBuffer.h"



IndexBuffer::IndexBuffer(void* data, UINT count)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(UINT) * count;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//VertexBuffer와 크게 다를건 없으나
	//어떤 버퍼인지 명시하는 부분은 바꿔줘야함

	//추가로 셰이더에서 다루는 꼭지점의 인덱스는 당연히 UINT일수밖에 없으니
	//이 버퍼의 크기는 입력받은 데이터에 들어있는 자료수 * sizeof(UINT)가 됨

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
