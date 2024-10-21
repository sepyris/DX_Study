#pragma once
class ConstBuffer // 상수 버퍼
{
private:
	ID3D11Buffer* buffer;

	void* data; // 이 버퍼 객체에 저장될 데이터를 멤버 변수로 미리 선언만 해둔 것
	// 어떤 데이터가 들어올지는 지금 시점에선 모름
	UINT data_size;// VertexBuffer의 stride와 거의 동일하나,
	// 말 그대로 어떤 데이터가 들어올지 모르므로 어떤 데이터를 이용해도 말이 되도록 이름지은 것

public:
	ConstBuffer(void* data, UINT data_size);
	virtual ~ConstBuffer();
	// 이 상수 버퍼는 다른 버퍼에 상속시켜서 사용할 내용이며,
	// 상수 버퍼 자체가 "상수 버퍼 클래스로서" 사용하는 경우가 매우 많기 때문에
	// 부모 클래스의 소멸자만 호출될 가능성이 매우 높음
	// 따라서 상속받은 버퍼 클래스의 소멸자가 확실히 호출되도록 가상함수로 만든 것

	void SetVS(UINT slot);
	void SetPS(UINT slot);
	// 각 셰이더의 지정된 슬롯에 넘길 데이터

};