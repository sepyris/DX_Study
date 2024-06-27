#pragma once
// ���� ���� Shape�� ��ӹ޾� �̿��ϴ� ���ο� ����� �ﰢ�� Ŭ����
// ��Ȯ���� SRT ��ȯ�� �����ų ������ Ŭ����


class Triangle : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	Float2 size; // �� ������ ũ�⸦ ������ ���

public:
	Triangle(Float2 size = Float2(100.0f, 100.0f),
		D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~Triangle();


	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }

	// Shape��(��) ���� ��ӵ�
	virtual void Render() override;

};