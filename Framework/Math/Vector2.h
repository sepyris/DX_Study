#pragma once
// Float2를 쉽게 생성하고 더 쉽게 이용하기 위해 만드는 클래스로,
// 실수 2개로 이뤄진 (수학적 의미의)벡터를 다루는 클래스
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

	// Float2는 이런 연산자들에 대한 연산자 오버로딩이 되어있지 않음
	// 이런 것들을 지원하도록 만들어서 좀 더 쉽게 사용하려 만드는 것이
	// 이 클래스를 만든 첫번째 이유

	// 두번째 이유는
	// 우리가 실제로 2차원 벡터를 이용할 때 자주 하게 되는 연산이 있음
	// (이 벡터의 길이가 어떻게 되는지,
	// 혹은 이 벡터가 2차원 공간인 이 화면에서 각도가 어떻게 되는지)
	// 이런 것들을 필요할 때마다 매번 멤버에 접근해서 만들지 않고
	// 아예 함수로서 손쉽게 만들기 위해 본 함수들을 작성

	// 이 벡터의 길이를 계산하는 함수
	// 벡터의 x,y좌표를 이용해서 피타고라스 법칙으로 빗변의 길이를 구하면
	// 그게 이 벡터의 길이 = 크기가 됨
	float GetLength() const
	{
		return sqrt(x * x + y * y);
	}

	// 이 두 함수를 설명하려면 "단위 벡터"에 대해 설명해야 하는데,
	// 이에 대해서는 직접 이 두 함수를 cpp에서 정의할 때 설명함
	void Normalize();
	Vector2 Normalized() const;
	
	// 이 벡터가 2차원 공간에서 가리키는 각도를 반환하는 함수
	float Angle() const;

	// 두 벡터를 내적하는 함수
	// 내적 자체는 벡터라는 개념 그 자체가 가지고 있는 것이다보니,
	// static을 이용해서 아예 이 클래스 자체가 내적 연산을 지원하도록 하는 것
	static float Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	// 벡터와 행렬을 곱해야 할 때,
	// 이 함수를 통해서 연산하도록 지원하는 함수
	static Vector2 TransformCoord(const Vector2& vec, const Matrix& mt);

};