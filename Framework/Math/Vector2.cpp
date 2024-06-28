#include "framework.h"
#include "Vector2.h"

Vector2::Vector2() : Float2(0, 0)
{
}

Vector2::Vector2(float x, float y) : Float2(x, y)
{
}

Vector2::Vector2(Float2 value) : Float2(value)
{
}

Vector2 Vector2::operator+(const Vector2& value) const
{
    return Vector2(x + value.x, y + value.y);
}

Vector2 Vector2::operator-(const Vector2& value) const
{
    return Vector2(x - value.x, y - value.y);
}

Vector2 Vector2::operator*(const Vector2& value) const
{
    return Vector2(x * value.x, y * value.y);
}

Vector2 Vector2::operator/(const Vector2& value) const
{
    return Vector2(x / value.x, y / value.y);
}

Vector2 Vector2::operator*(const float& value) const
{
    return Vector2(x * value, y * value);
}

Vector2 Vector2::operator/(const float& value) const
{
    return Vector2(x / value, y / value);
}

void Vector2::operator+=(const Vector2& value)
{
    x += value.x;
    y += value.y;
}

void Vector2::operator-=(const Vector2& value)
{
    x -= value.x;
    y -= value.y;
}

void Vector2::operator*=(const float& value)
{
    x *= value;
    y *= value;
}

void Vector2::operator/=(const float& value)
{
    x /= value;
    y /= value;
}
// �� ���� �ڵ���� ����� ������, ������ �����ε��� �� ���� �����̶�
// ������ �Ÿ��� ����

void Vector2::Normalize() // ���� "ǥ��ȭ" �Լ�
/*
�� �Լ��� �����Ϸ��� "���� ����"��� ������ ���� �˾Ƶ־� ��

���� ���� : ���̰� 1�� ���͸� ����
�⺻������ ���ʹ� ��� �������� ��� �������� ���ϴ����� ũ��� �Բ� ����ϴ� ����
�׷���, ũ��� �ʿ����� �ʰ� ���⸸ �ʿ��� ���,
ũ�Ⱑ �����ϴ� ���ʹ� �� ũ�Ⱑ �������� ������ ��ĥ �� ����
���� �� ������ �����ϱ� ���� ���ǹ��� ũ�⸦ ������ �ʰ�
���⸸�� ǥ���ϵ��� �ϴ� ���͸� ���� ���� ���� ���Ͱ� ��
(���Ϳ� ���ͳ��� ���� ���, 
��� �� ���� ũ�Ⱑ 1�̸� ����� �Ϸ�� ������ x,y���� ��� �ٲ����
�ٲ� ������ ũ��� ���� ���Ϳ� ������)

�츮�� ������ ���� �Ǵ� ���ʹ� ���� ���Ͱ� �ƴ� ���� �ξ� ������,
�̸� �ʿ信 ���� ���� ���ͷ� "ǥ��ȭ"�� �ϴ� ������ ��Ȥ �ʿ������µ�
�� �� �� ���� ���Ͱ� �ƴ� ���͸� ���� ���ͷ� ����� ���� �� �Լ�
*/
{
    float length = GetLength();
    x /= length;
    y /= length;

    // �ᱹ ���� ���͸� ũ�� 1�� ���ߴ� ���̹Ƿ�
    // �ٸ��� ���ϸ� �� ������ ũ�⸦ 1�� ���̰ų� �ø��� ���̹Ƿ�
    // �ڱ� �ڽ��� ������ �ִ� ����� �ڱ� �ڽ��� ���̷� �����ָ� �ս��� ����
}

// ���͸� ǥ��ȭ"���� ��� ��������� ����"�� ��ȯ�ϴ� �Լ�
// ���� ���͸� ǥ��ȭ�ϸ� �� �Ǵµ�, �� ������ ���� ���ʹ� �ʿ��� ��� �����
Vector2 Vector2::Normalized() const
{
    float length = GetLength();
    return Vector2(x / length, y / length);
    
    // ���� ��ü�� ���� �Ȱ�����, ������ ���� �ʰ�
    // (�� ������ const ������ ���� �� �Լ��� ���ؼ�
    // �� ������ �����͸� �ٲ��� ���ϵ��� �����ص�)
    // �ƿ� �׷��� ����� ����� �� ���͸� ���� ��ȯ
}

float Vector2::Angle() const // ������ ����ϴ� �Լ�
// ��Ȯ����, x�� �������� ������ ��ŭ���� ���
{
	return atan2(y, x);
    // �� �� ���� ���������� �ﰢ�Լ��� ã�� ��� ��
}

Vector2 Vector2::TransformCoord(const Vector2& vec, const Matrix& mt)
// ���Ϳ� ����� ������Ű�� �Լ�
// � ������ ����Ǵ��� ��ü�� �߿�ġ ���� ������ ���̴�,
// ���⼱ �׳� ���ุ �ϰ� � �������������� ���� ����
{
    XMVECTOR temp = XMLoadFloat2(&vec);
    temp = XMVector2TransformCoord(temp, mt);

    Vector2 temp_pos;
    XMStoreFloat2(&temp_pos, temp);

    return temp_pos;
}
