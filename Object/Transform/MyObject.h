#pragma once
// Transform을 상속받고, 멤버로서 삼각형을 출력하도록 하는
// 실질적인 오브젝트를 담당하는 클래스
class MyObject : public Transform
{
private:
	Triangle* tri;

public:
	MyObject(Float2 p = Float2(0, 0), 
		Float2 s = Float2(1, 1),
		float a = 0.0f, 
		Float2 size = Float2(100, 100),
		D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~MyObject();

	void Update(Matrix* parent = NULL);
	void Render();

	void SetColor(Float4 colour)
	{
		tri->SetColor(colour);
	}

};