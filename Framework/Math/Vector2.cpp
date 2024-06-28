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
// 이 위의 코드들은 평범한 생성자, 연산자 오버로딩에 들어갈 법한 내용이라
// 설명할 거리가 없음

void Vector2::Normalize() // 벡터 "표준화" 함수
/*
이 함수를 이해하려면 "단위 벡터"라는 개념을 먼저 알아둬야 함

단위 벡터 : 길이가 1인 벡터를 말함
기본적으로 벡터는 어느 지점에서 어느 방향으로 향하는지를 크기와 함꼐 기록하는 개념
그런데, 크기는 필요하지 않고 방향만 필요할 경우,
크기가 존재하는 벡터는 그 크기가 연산결과에 영향을 끼칠 수 있음
따라서 그 영향을 제거하기 위해 유의미한 크기를 가지지 않고
방향만을 표시하도록 하는 벡터를 만든 것이 단위 벡터가 됨
(벡터와 벡터끼리 곱할 경우, 
어느 한 쪽의 크기가 1이면 계산이 완료된 벡터의 x,y값이 어떻게 바뀌었든
바뀐 벡터의 크기는 기존 벡터와 동일함)

우리가 앞으로 쓰게 되는 벡터는 단위 벡터가 아닌 것이 훨씬 많으니,
이를 필요에 따라서 단위 벡터로 "표준화"를 하는 과정이 간혹 필요해지는데
그 때 그 단위 벡터가 아닌 벡터를 단위 벡터로 만드는 것이 본 함수
*/
{
    float length = GetLength();
    x /= length;
    y /= length;

    // 결국 현재 벡터를 크기 1에 맞추는 식이므로
    // 다르게 말하면 이 벡터의 크기를 1로 줄이거나 늘리는 식이므로
    // 자기 자신이 가지고 있던 멤버를 자기 자신의 길이로 나눠주면 손쉽게 구함
}

// 벡터를 표준화"했을 경우 만들어지는 벡터"를 반환하는 함수
// 기존 벡터를 표준화하면 안 되는데, 이 벡터의 단위 벡터는 필요한 경우 사용함
Vector2 Vector2::Normalized() const
{
    float length = GetLength();
    return Vector2(x / length, y / length);
    
    // 계산식 자체는 위와 똑같지만, 대입을 하지 않고
    // (그 이전에 const 선언을 통해 이 함수를 통해서
    // 이 벡터의 데이터를 바꾸지 못하도록 강제해둠)
    // 아예 그렇게 계산한 결과로 새 벡터를 만들어서 반환
}

float Vector2::Angle() const // 각도를 계산하는 함수
// 정확히는, x축 기준으로 각도가 얼만큼인지 계산
{
	return atan2(y, x);
    // 왜 이 식이 나오는지는 삼각함수를 찾아 배울 것
}

Vector2 Vector2::TransformCoord(const Vector2& vec, const Matrix& mt)
// 벡터와 행렬을 곱셈시키는 함수
// 어떤 식으로 시행되는지 자체는 중요치 않을 것으로 보이니,
// 여기선 그냥 구축만 하고 어떤 내용인지까지는 적지 않음
{
    XMVECTOR temp = XMLoadFloat2(&vec);
    temp = XMVector2TransformCoord(temp, mt);

    Vector2 temp_pos;
    XMStoreFloat2(&temp_pos, temp);

    return temp_pos;
}
