#pragma once
class ConstBuffer // ��� ����
{
private:
	ID3D11Buffer* buffer;

	void* data; // �� ���� ��ü�� ����� �����͸� ��� ������ �̸� ���� �ص� ��
	// � �����Ͱ� �������� ���� �������� ��
	UINT data_size;// VertexBuffer�� stride�� ���� �����ϳ�,
	// �� �״�� � �����Ͱ� ������ �𸣹Ƿ� � �����͸� �̿��ص� ���� �ǵ��� �̸����� ��

public:
	ConstBuffer(void* data, UINT data_size);
	virtual ~ConstBuffer();
	// �� ��� ���۴� �ٸ� ���ۿ� ��ӽ��Ѽ� ����� �����̸�,
	// ��� ���� ��ü�� "��� ���� Ŭ�����μ�" ����ϴ� ��찡 �ſ� ���� ������
	// �θ� Ŭ������ �Ҹ��ڸ� ȣ��� ���ɼ��� �ſ� ����
	// ���� ��ӹ��� ���� Ŭ������ �Ҹ��ڰ� Ȯ���� ȣ��ǵ��� �����Լ��� ���� ��

	void SetVS(UINT slot);
	void SetPS(UINT slot);
	// �� ���̴��� ������ ���Կ� �ѱ� ������

};