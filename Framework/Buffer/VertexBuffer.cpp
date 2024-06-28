#include "framework.h"

VertexBuffer::VertexBuffer(void* data, UINT s, UINT count)
	: stride(s), offset(0)
{
	// 기존에 각 도형에서 버퍼를 만들어 등록했던 부분을 복사,
	// 본 클래스에 맞게 총 2개를 고쳐서 사용

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = stride * count;
	// 1) Bytewidth(대역폭)
	// 도형에서 쓸 때는 정점 하나의 크기 * 정점의 개수를 통해 체크했었는데
	// 여기서는 그 정점 하나의 용량을 직접 지정해둔 stride를 이용
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;
	// 2) pSysMem
	// 도형 쪽에서는 생성자에서 정점들을 벡터에 넣어두고
	// 이를 등록하는 식이었는데
	// 여기선 생성자의 매개변수로서 아예 데이터가 들어있는 주소를 받았으니
	// 이를 그대로 이용하도록 건네줌
	
	// void*라서 형변환을 해야 사용할 수 있다는 점은
	// 애초에 어떤 데이터인지 분석할 방법도 없는 셰이더 측에 건네는 이상 무의미

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
	// 기존의 Scene에서 오브젝트가 가지고 있던 내용을 일일이 등록했던 걸
	// 이 클래스에서 알아서 전부 처리하도록 가져옴
}
