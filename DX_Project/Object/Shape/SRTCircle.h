#pragma once
class SRTCircle : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	Float2 size;
	// ���� Ÿ������ ����� �ʹٸ� API���� �ٷ�� ��ó�� �¿�/���ϸ� ���ÿ� �̿��ؾ� ����
	// ���⼭�� �������� �̿��ϴ� ��Ÿ�Ϸ� ���� ����

public:
	SRTCircle(Float2 size, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type);
	SRTCircle(float radius, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type);

	~SRTCircle();


	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
	void Render();

};