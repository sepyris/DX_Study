#pragma once
// Float2�� ���� �����ϰ� �� ���� �̿��ϱ� ���� ����� Ŭ������,
// �Ǽ� 2���� �̷��� (������ �ǹ���)���͸� �ٷ�� Ŭ����
class Vector2 : public Float2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(Float2 value);

	Vector2 operator+ (const Vector2& value) const;
	Vector2 operator- (const Vector2& value) const;
	Vector2 operator* (const Vector2& value) const;
	Vector2 operator/ (const Vector2& value) const;

	Vector2 operator* (const float& value) const;
	Vector2 operator/ (const float& value) const;

	void  operator+= (const Vector2& value);
	void  operator-= (const Vector2& value);
	void  operator*= (const float& value);
	void  operator/= (const float& value);

	// Float2�� �̷� �����ڵ鿡 ���� ������ �����ε��� �Ǿ����� ����
	// �̷� �͵��� �����ϵ��� ���� �� �� ���� ����Ϸ� ����� ����
	// �� Ŭ������ ���� ù��° ����

	// �ι�° ������
	// �츮�� ������ 2���� ���͸� �̿��� �� ���� �ϰ� �Ǵ� ������ ����
	// (�� ������ ���̰� ��� �Ǵ���,
	// Ȥ�� �� ���Ͱ� 2���� ������ �� ȭ�鿡�� ������ ��� �Ǵ���)
	// �̷� �͵��� �ʿ��� ������ �Ź� ����� �����ؼ� ������ �ʰ�
	// �ƿ� �Լ��μ� �ս��� ����� ���� �� �Լ����� �ۼ�

	// �� ������ ���̸� ����ϴ� �Լ�
	// ������ x,y��ǥ�� �̿��ؼ� ��Ÿ��� ��Ģ���� ������ ���̸� ���ϸ�
	// �װ� �� ������ ���� = ũ�Ⱑ ��
	float GetLength() const
	{
		return sqrt(x * x + y * y);
	}

	// �� �� �Լ��� �����Ϸ��� "���� ����"�� ���� �����ؾ� �ϴµ�,
	// �̿� ���ؼ��� ���� �� �� �Լ��� cpp���� ������ �� ������
	void Normalize();
	Vector2 Normalized() const;
	
	// �� ���Ͱ� 2���� �������� ����Ű�� ������ ��ȯ�ϴ� �Լ�
	float Angle() const;

	// �� ���͸� �����ϴ� �Լ�
	// ���� ��ü�� ���Ͷ�� ���� �� ��ü�� ������ �ִ� ���̴ٺ���,
	// static�� �̿��ؼ� �ƿ� �� Ŭ���� ��ü�� ���� ������ �����ϵ��� �ϴ� ��
	static float Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	// ���Ϳ� ����� ���ؾ� �� ��,
	// �� �Լ��� ���ؼ� �����ϵ��� �����ϴ� �Լ�
	static Vector2 TransformCoord(const Vector2& vec, const Matrix& mt);

};