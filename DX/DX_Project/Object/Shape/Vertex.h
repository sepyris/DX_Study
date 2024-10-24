#pragma once
// �� ������Ʈ���� ����� �������� ���� �ϴ� ���
//������ Ư���� ������ �ʿ�� �Ҷ� ����
struct Vertex
// ������ �츮�� ������ ���� �� �� ������ ������ �� ����ü�� ���� ������
{
	Float3 position; // ������ ��ġ
	// �츮�� ������ �ٷ�� �� 2D����
	// �⺻�����δ� 3D ���� ����� �̿��ؼ� 2D�� �ٷ�� ���̱� ������
	// ����ϴ� �Լ� ���� �԰ݿ� �°� x,y,z 3�� ������ �����͸� 
	// ���� ������ �ص־� �� -> ����� �� �ϴ��� z���� �ϴ� ������ ����

	Float4 colour; // ������ ������ �ִ� ��
	// RGB���� �̿��ؼ� ���� �����ϳ�,
	// ���⿡ �߰��� Alpha���̶�� �����͸� ���� ������

	Vertex()
		// C++���� ����ü�� ��ǻ� public�� �����ϴ� Ŭ������ ���� ����
		// �̷��� �����ڸ� ����� �͵� ���� X
		// �ƹ� �Է� ���� ����Ʈ �����ߟ� ���� �ʱ�ȭ��
	{
		position = Float3(0, 0, 0);
		colour = Float4(0, 0, 0, 1);
		// RGB�� �ܿ� 4��° ���� ���İ��� ����� ��ȸ�� ���� �� ����
	}
	Vertex(float x, float y, float r, float g, float b)
	{
		position = Float3(x, y, 0);
		// 2D���� z���� ��ġ�� ������� ����
		colour = Float4(r, g, b, 1);
		// DX������ RGB���� �̿��� ��
		// 0.0f ~ 1.0f������ ���� ���� ������μ� ������ ǥ����
	}
};


struct VertexPos {// ��ǥ�� ������ � �����͵� ���� ������
	Float3 position;

	VertexPos(float x = 0, float y = 0)
	{
		position = Float3(x, y, 0);
	}
};

struct VertexUV
{
	Float3 position;
	Float2 UV;


	VertexUV(float x = 0, float y = 0, float u = 0, float v = 0)
	{
		position = Float3(x, y, 0);
		UV = Float2(u, v);
	}
};