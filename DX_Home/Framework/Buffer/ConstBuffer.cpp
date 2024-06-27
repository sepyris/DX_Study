#include "framework.h"
#include "ConstBuffer.h"

ConstBuffer::ConstBuffer(void* data, UINT data_size)
	: data(data), data_size(data_size)
{
	// VertexBuffer의 생성자에 넣었던 내용을 복사해오기
	// 단, 고쳐야 할 부분이 다름

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = data_size;
	// 1) Bytewidth(대역폭)
	// 상수 버퍼는 데이터의 총 용량을 매개변수로서 받기 때문에
	// 아예 이를 그대로 이용
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	// 2) BindFlags
	// 이 버퍼의 사용처(=용도)를 명확히 설명
	// 기존의 정점을 저장하는 용도에서 상수를 저장하는 버퍼로 바꾸는 것
	
	// 바꾸지 않는다면 도형 자체가 정상적으로 출력되지 않음

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;

	DEVICE->CreateBuffer(&bd, &initData, &buffer);
}

ConstBuffer::~ConstBuffer()
{
	buffer->Release();
}


// 이제부터 사용할 셰이더 파일들에는
// 상수 버퍼를 사용하는 부분이 있음
// 그 부분에 셰이더에서 요구하는 규격으로서 데이터를 전달할 수 있도록
// 셰이더의 "어느 슬롯"에 이 버퍼의 데이터를 등록할 것인지를
// 함수로서 지정할 수 있도록 하는 역할
void ConstBuffer::SetVS(UINT slot) // 정점 셰이더에 등록할 때 쓰는 함수
{
	DVC->UpdateSubresource(buffer, 0, NULL, data, 0, 0);
	DVC->VSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetPS(UINT slot) // 픽셀 셰이더에 등록할 때 쓰는 함수
{
	DVC->UpdateSubresource(buffer, 0, NULL, data, 0, 0);
	DVC->PSSetConstantBuffers(slot, 1, &buffer);
}
