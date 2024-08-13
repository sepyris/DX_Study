#pragma once
// 새로 만든 Shape를 상속받아 이용하는 새로운 방식의 삼각형 클래스
// 정확히는 SRT 변환을 적용시킬 예정인 클래스


class RectUV : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;

public:
	RectUV(Vector2 size = Float2(100.0f, 100.0f),
		Vector2 start_uv = Vector2(0,0),
		Vector2 end_uv = Vector2(1, 1),
		D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~RectUV();


	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }

	// Shape을(를) 통해 상속됨
	virtual void Render() override;

};