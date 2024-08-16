#pragma once
// �� ����� ������ �ʿ��� ��� ���۰� ���� ������
// �� ���۵��� �����ϴ� ����

// ��� ���۶�� ���� ���ó�� ������ ���Ƽ�
// ������ DX ���α׷��� ������ ������ �߰��ϰ� �Ǵ� ���۰� �� �ִ� �����
// �ʿ��� ������ ���⿡ ����

class MatrixBuffer : public ConstBuffer
	// MatrixBuffer : 3���� ������ ���õ� ������ �ϴ� �� �ʿ���
	// ����� �����ϴ� �뵵�� ����
{
private:
	struct Data
	{
		Matrix matrix;
	} data;

public:
	MatrixBuffer() : ConstBuffer(&data, sizeof(data))
	{
		data.matrix = XMMatrixIdentity();
		// ��������� ����� �Լ��� ����
		// �ʱⰪ�� ������ķ� �ʱ�ȭ

		// ������ �츮�� ������ ������ �����ϱ� ���ؼ�
		// �ﰢ�Լ�, *����� ����, �������*,
		// ���п����� ����, ��Ȯ���� �� ������ ���� �� ����
		// ����� ������ �˾Ƶ־� ������ �� ����

		// ���ʹݿ��� �̸� ���� �����ϱ�� �ſ� ������,
		// �̸� �ش� ������� ������ ���� ����

		// ���� - 4X4 ũ���� ��������� ��� ����°�?
		/*
		1 0 0 0
		0 1 0 0
		0 0 1 0
		0 0 0 1
		*/
		// 2��° ���� - �� ��������� �̷��� ����°�?
		// -> �� ��İ� ������ ������ � ��Ŀ� ���ϴ���
		// ����� ������ ����Ǵ� ����� �������� ��
		// �׻� ���ϱ� ���� ����� �״�� �����Ǵ� ����̱� ����

		// ���п��� "�׵��"�� "����"�̶�� ������ ����
		// �Ȱ��� �� ������ ���꿡 ���ؼ�(����, ���� ��)
		// �׵�� : � ���� �� ���� �̿��� �������� ��� 
		// �׻� �� � ���� �״�� �����Ǵ� ��
		// ������ ��쿣 0,  ������ ��쿣 1
		// ���� : � ���� ���� ��,
		// �� ���� ������ ���� �� ������� �׵���� ������ ��
		// ������ ��쿣 1�� ������ -1
		// ������ ��쿣 12�� ������ 1/12

		// �̷� ������ "���� �� ������ ������ �����ϴ� �� ü�� �ȿ�����
		// �������ϸ� �׵���� ������ �����Ѵٰ� �� �� �ִ�"�� �� �� �ְ�
		// �װ� ��Ŀ��� ������ ���� ���� �������

		// XMMatrixIdentity : �׷� �������,
		// ��Ȯ���� �� ������� �� 3D �׷��Ƚ����� �ַ� ����ϴ� ��� ��������
		// 4X4 ����� ��������� ������ִ� �Լ�
		// ���� �� MatrixBuffer�� ���� �� 4X4 ũ���� ��������� ������ ��

	}
	~MatrixBuffer() {};

	void Set(Matrix value)
	{
		data.matrix = XMMatrixTranspose(value);
		// ����� �����͸� �ٸ� ��ķ� �����ϴ�
		// ��� ���� �����Լ�
	}
};

class ColourBuffer : public ConstBuffer
	// ColourBuffer : ������ �ȼ� ���̴��� ����� �� ����� ���۸� Ŭ����ȭ�� ��
	// �����δ� �������� ���� ���� �������� �ʰ�
	// ���� �� ��ü�� ������ �ִ� ���� ���۸� ���ؼ� 
	// ���� ��ü�� ������ �����ϵ��� ���� ����
{
public:
	struct Data
	{
		Float4 colour;
	} data;

	ColourBuffer() : ConstBuffer(&data, sizeof(data))
	{
		data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		// �ʱⰪ�� ����� �����ϴ� �Ǽ� 4���� ����
	}
};

