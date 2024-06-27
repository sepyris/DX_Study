#pragma once
// �⺻�����δ� ���� ������Ʈ���� ������� �Ͱ� ���
// ������ �̹��� ����Ǵ� �̷� ��ü�� �ִ� ��ŭ
// ���� Ŭ�����ʹ� ������ �޶��� ��

class Shape
{
protected:
	vector<Vertex> vertices = {};

	VertexShader* VS;
	PixelShader* PS;

	// pos_x, pos_y�� �� �̻� ������� ����
	// : transform�̶�� Ŭ�������� �ٷ� ����

	VertexBuffer* VB;
	ColourBuffer* CB;
	// ���� ����/������ �����ϴ� �� ����� ���۵�
	// ������ ID3D11Buffer ��� ������ �뵵�� Ưȭ�� ���� Ŭ������ �̿�
public:
	Shape();

	VertexBuffer** const GetBuffer() { return &VB; }
	int GetVertexSize() { return vertices.size(); }

	void SetColor(Float4 colour)
	// �� ������ ������ �� ���� �������ִ� ������
	// -> �� ���ۿ� ���ο� ���� �����ϴ� �Լ�
	{
		CB->data.colour = colour;
	}

	virtual void Render() = 0;
	// ������ Scene���� �׸��� ����ϴ� �ڵ带 ���� �����ߴ� ��
	// �����δ� �� ������Ʈ�� ������ �ִ� �׷����� ����ϴ� Ŭ��������
	// ���� ó���� ���� ���þ� �ϰ� �� ����

	// �̸� ����, �� ����� ����� �Լ���
	// �� Ŭ������ ��ӹ޴� ��� Ŭ������ �������� ����
};