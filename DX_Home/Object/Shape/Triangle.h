#pragma once
// 새로 만든 Shape를 상속받아 이용하는 새로운 방식의 삼각형 클래스
// 정확히는 SRT 변환을 적용시킬 예정인 클래스


class Triangle : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	Float2 size; // 이 도형의 크기를 저장할 멤버

public:
	Triangle(Float2 size = Float2(100.0f, 100.0f),
		D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~Triangle();


	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }

	// Shape을(를) 통해 상속됨
	virtual void Render() override;

};