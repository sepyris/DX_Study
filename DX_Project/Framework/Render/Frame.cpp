#include "framework.h"
#include "Frame.h"

Frame::Frame(wstring file, Vector2 startUV, Vector2 endUV)
// ���� �ּҿ� �Բ� �ش� ���� �� ����� ������ "�̹��� ��ü������ �����ǥ�μ� �Է¹޾��� ��"�� ������
// �� �̹��� ��ü������ �����ǥ�� Ȯ���� ���� �������ϸ� ���� ������,
// ������ �⺻���� 0,0�� 1,1�� �̿��ϱ� ���� ���� ���̶� ���� OK
{
	texture = Texture::Add(file); // ���� �ҷ�����

	Vector2 size = texture->GetSize(); // �ҷ��� ������ ũ�⸦ �޾Ƽ� size�� �Է�

	Vector2 half_size = size * 0.5f; // ������ ��ġ�� �����ϴ� �� �� ����

	float left = -half_size.x;
	float right = half_size.x;
	float top = -half_size.y;
	float bottom = half_size.y;
	// �̸� ���� �� �̹����� ǥ�õ� ��,��,��,�� ������ ������ ��ǥ���� ����

	vertices.emplace_back(left, top, startUV.x, startUV.y);
	vertices.emplace_back(right, top, endUV.x, startUV.y);
	vertices.emplace_back(left, bottom, startUV.x, endUV.y);
	vertices.emplace_back(right, bottom, endUV.x, endUV.y);

	indices = { 0, 1, 2, 2, 1, 3 };
	// ������ �ε����� ���

	VB = new VertexBuffer(vertices.data(), (UINT)sizeof(VertexUV), (UINT)vertices.size());
	IB = new IndexBuffer(indices.data(), (UINT)indices.size());

	frame_size = endUV - startUV;
	// ��ü �������� ũ�� �� �� �������� �����ϴ� ������ �󸶳� �Ǵ����� frame_size�� ���
	// �� ���� ���߿� �� �������� �����ϰ� �ִ� �̹��� ���Ͽ� ���� ���� ũ�⸦ Ȯ���ϴ� �� ���
}

Frame::Frame(wstring file, float x, float y, float w, float h)
// ���� �ּҿ� �Բ� �ش� ���� �� 
// "�̹��� ���ο��� ����ϰ��� �ϴ� ������ ������ǥ�� �޾��� ��"�� ������
// 
// x, y : �̹��� ���� ������ ����ϰ��� �ϴ� ��������Ʈ�� �ִ�
//        �簢�� ������ ���۵Ǵ� ���� �� ���� ��ǥ
// 
// w, h : width, height�μ� ����ϰ��� �ϴ� ��������Ʈ�� �ִ�
//        �簢�� ������ ����/���� ������ �����ϴ� �Ű� ����
{
	texture = Texture::Add(file); // ���� �ҷ�����

	Vector2 size = texture->GetSize(); // �ҷ��� ������ ũ�⸦ �޾Ƽ� size�� �Է�

	Vector2 half_size = size * 0.5f; // ������ ��ġ�� �����ϴ� �� �� ����

	float left = -half_size.x;
	float right = half_size.x;
	float top = -half_size.y;
	float bottom = half_size.y;
	// �̸� ���� �� �̹����� ǥ�õ� ��,��,��,�� ������ ������ ��ǥ���� ����


	Vector2 cut_start = Vector2(x, y) / size;
	// ����ϰ��� �ϴ� ��ġ�� �̹������� �����ǥ(uv��)

	Vector2 cut_size = Vector2(w, h) / size;
	// ����ϰ��� �ϴ� �׸� �������� �����ǥ�μ��� ����

	Vector2 cut_end = cut_start + cut_size;
	// ����ϰ��� �ϴ� �̹����� ������,
	//�̹����� ������ ����Ű�� �簢���� ������ �Ʒ� ��

	vertices.emplace_back(left, top, cut_start.x, cut_start.y );
	vertices.emplace_back(right, top, cut_end.x, cut_start.y );
	vertices.emplace_back(left, bottom, cut_start.x, cut_end.y );
	vertices.emplace_back(right, bottom, cut_end.x, cut_end.y);

	indices = { 0, 1, 2, 2, 1, 3 };
	// ������ �ε����� ���

	VB = new VertexBuffer(vertices.data(), (UINT)sizeof(VertexUV), (UINT)vertices.size());
	IB = new IndexBuffer(indices.data(), (UINT)indices.size());

	frame_size = Vector2(w / texture->GetSize().x,
		                 h / texture->GetSize().y);
	//�ؽ��� ��ü�� ũ�⸦ ���� ���ѵ�
	//�װ͵��� ���� �Է¹��� ��������Ʈ ������ ũ��� ������
	//��ü �����󿡼��� ������ �Է��ϴ°�
	 
	 
	//���� frame_size�� ����Ǵ� ���� ��������Ʈ�� ũ�� �� ��ü�� �ƴ϶�
	//��������Ʈ�� ��ü ũ�⸦ �������� �󸶳� �������� üũ�ϴ� ��
}

Frame::~Frame()
{
	if (VB != NULL) {
		delete VB;
	}
	if (IB != NULL) {
		delete IB;
	}
	
}

void Frame::Render()
{
	VB->Set();
	IB->Set();
	texture->Set();

	DVC->DrawIndexed((UINT)indices.size(), 0, 0);
	//�� Ŭ������ �ε��� ���۸� �̿��ϹǷ�
	// = �������� ������ �ѹ��� ���ٴ� ������ �����Ƿ�
	// �������� ���� ���
	//��� �������� �̿��Ұ������� ����Ǿ��ִ� indices�� size�� �̿��ؼ�
	//�� ����� ���������� ������ �Է�
}
