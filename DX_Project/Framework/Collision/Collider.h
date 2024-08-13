#pragma once
/*
3D�������� � ������Ʈ�� �ٸ� ������Ʈ�� �浹 �ϴ°���
�⺻�����δ� �� ���� ���� ������ �ִ� �浹 ���� ���� �浹 �����̶� �Ҹ��°���
���� ��,�浹�ϴ� ������ �ִ��� ������ �˻��ϴ� ������ ����

������ �浹 �ߴ����� ���θ� �Ǵ��ϴ� �˰����̶�°���
������ ���� ����� �����Ѱ͵��� ����
�׷��� ���⼭�� �� �� �ַ� ���̴� 2���� �˰����� ����� ����
(��� �˰��� �������� ���� ����,AABB�˰���,OBB�˰���)


*/


class Collider:public Transform
{
public:
	enum class TYPE {
		RECT,
		CIRCLE
	};
	//�� Ŭ������ �� �ڽ� Ŭ�������� ����Ұ��� ������ ���� Ŭ����
	//���� �������� ġȯ ��Ģ�� ���� �ڽ� Ŭ�������� �� Ŭ������ �����
	//����� ��Ȳ�� �ſ� ����
	//����, �θ�Ŭ���������� � �ڽ� Ŭ������ ���°����� �Ǵ��ϱ� ����
	//����μ� � Ŭ���������� ����ϴ� ������ Ŭ���� ����� ������̰�
	//�ű⿡ ����� ������ Ŭ������ public���� ��ǥ �Ѱ�

protected:
	TYPE type;//�׷��� ����� ������ Ŭ������ protected����� �ϳ� ����

	VertexShader* VS;
	PixelShader* PS;

	VertexBuffer* VB;

	ColourBuffer* CB;
	//��������� ������ ����ѰͰ� ����
	MatrixBuffer* WB;
	//�� �浹 ���� Ŭ������ �ڱ��ڽ��� ��ü������ ����ϰ� ������̹Ƿ�
	//�� �������� ����� ���� ���۸� ���� ������ذ�

	vector<VertexPos> vertices;//�ű⿡ ����� ����
	//�ٸ� �� Ŭ������ ������ ������ �ƴ϶�
	//������ �ƿ� ������� �ʰ� ��ġ�� ����ϴ� ������ �����
	// ������ۿ� �ִ� �������� �׵θ����� �׸� �����̱� ����
	//


public:
	Collider();
	virtual ~Collider();
	void Render();

	TYPE GetType() { return type; }

	virtual bool isCollision(Collider* collider,Vector2* overwrap = NULL);
	//�Է¹��� �浹������ � Ÿ���̳Ŀ� ���� �Ʒ��� �ִ� �ٸ� �Լ��� ȣ���ϴ� �߰��Լ�

	//�Ʒ��� �� �Լ�(+�� �浹 ����)�� ����
	//Ư���� ���� �浹 �ߴ����� �˻��ϴ� �Լ�
	virtual bool isPointCollision(Vector2 point) = 0;
	virtual bool isCircleCollision(class CircleCollider* collider) = 0;
	virtual bool isRectCollision(class RectCollider* collider, Vector2* overwrap = NULL) = 0;

	void SetColor(float r, float g, float b) {
		CB->data.colour = Float4(r, g, b, 1);
	}
protected:
	virtual void CreateLine() = 0;

	//�� �浹 ������ �׵θ����� ���� �ϴ� �Լ�
	//���� �׸��� �簢���� �׸��� �θ�Ŭ���� �ܰ迡�� �˼� �����Ƿ�
	//�̸� �ڽ� Ŭ�������� �׸����� ����
};