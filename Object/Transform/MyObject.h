#pragma once
// Transform�� ��ӹް�, ����μ� �ﰢ���� ����ϵ��� �ϴ�
// �������� ������Ʈ�� ����ϴ� Ŭ����
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