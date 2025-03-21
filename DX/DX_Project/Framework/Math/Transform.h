#pragma once


class Transform
{
protected:
	Matrix world;
	// 이 오브젝트가 속한 "월드"의 행렬
	// 추후 설명하겠지만 WVP 변환에 사용되는 W(=World)로,
	// 오브젝트를 만들 떄 어디를 기준점으로 할 것인지를 행렬의 형태로 저장해서
	// 이를 WVP 변환에 이용하는 것

	MatrixBuffer* WB; // 월드를 셰이더 쪽에 건넬 때 사용할 상수 버퍼

	Vector2 pivot; // 오브젝트와 연결된 다른 오브젝트가 회전해야 할 경우 사용함
	// 기존의 공전용 더미데이터와 비슷한 역할을 하되
	// 자기 자신은 그대로 있으면서 pivot을 사용하는 오브젝트가 구심점으로 사용
	// ...말은 이렇지만 실제로 쓰기 전까지는 제대로 설명하기 힘든 개념
	// 그래서 지금은 그냥 이런 게 있다 정도로만 기억할 것

	Matrix* parent; // 이 Transform이 위치 등을 의존하고 있는 부모 오브젝트,
	// 정확히는 그 부모 오브젝트가 가지고 있는 월드 행렬의 주소

	Matrix S, R, T, P, IP;
	// SRT 변환 행렬을 계산하는 데 필요한 행렬들
	// 기존에는 생성자나 업데이트에서 잠깐 만들고 끝냈었지만,
	// 이제는 멤버로서 저장

	XMFLOAT4X4 mat_world;
	// world 행렬을 좀 손쉽게 사용하기 위해서
	// XMMATRIX라는 자료형인 world 행렬 대신
	// 그나마 사용하기 쉬운 4x4 실수를 저장하는 데이터로서 저장하는 멤버

	Vector2 global_scale;
	// 실제 화면에 표시되는 기준으로 했을 때
	// 이 오브젝트가 대략 어느 정도의 크기를 가졌는지
	// 이 2차원 벡터에 저장하는 역할

	Vector2 right;
	Vector2 up;
	// 이 Transform이 현재 보고 있는 방향을 angle, 각도가 아닌
	// 방향축으로 정의하여 저장한 것
	// 각각 이 인스턴스가 보고 있는 방향 기준으로 오른쪽, 위가 어디인지를 정의

public:
	bool is_active;//이 트랜스폼이 활성화 상태인지 아닌지를 기록하는 변수

	Vector2 pos; // 이 Transform이 위치한 좌표
	Float2 scale; // 이 Transform의 크기를 결정할 설정값
	Float3 rot; // 이 Transform이 x축, y축, z축 기준으로 각각 얼마나 회전했는지
	// 그 회전도를 저장하는 설정값
	// 단, 지금 우리는 2D만 다루기 때문에 
	// 2D에서 사용되는 축인 z축 회전만을 이용하게 됨

	// 이상의 3개 패러미터는 Transform에서 특히 자주 사용하게 되는 값으로,
	// SRT 변환이라는 개념에 사용되는 중요한 패러미터기 때문에
	// public으로 공개하고 있는 것

	Transform(Vector2 p = Float2(0, 0), Vector2 s = Vector2(1,1), 
		float a = 0, Matrix* parent = NULL);
	~Transform();

	// 그 중요한 3개 패러미터 중 회전만큼은
	// 본 프로젝트가 2D를 다루고 있다는 걸 감안할 때 약간 비직관적인 면이 있어서
	// (실제 데이터는 실수 3개를 저장하지만 직접 사용하는 건 z값 하나 뿐)
	// 조금이나마 쉽게 이해하고 다룰 수 있게 하기 위해
	// public임에도 불구하고 접근자와 지정자를 정의
	float GetAngle() { return rot.z; }
	void SetAngle(float a) { rot.z = a; }

	void WorldTransform(Matrix* parent = NULL);
	// 이 오브젝트의 world 행렬을 업데이트하는 함수
	// 이 함수를 실행하는 것으로 
	// 이 Transform이 실제 3D 공간에서 어떤 상황에 놓여있는지를 명확히 정의

	void WorldUpdate();
	// 위의 WorldTransform은 단순하게 SRT 변환 행렬"만"을
	// 그 자리에서 S,R,T 행렬을 패러미터를 통해 만들어가면서 도출하고
	// 그대로 끝나는 함수였음
	// 그러나 이제는 저것들을 미리 만들어서 저장해둔 뒤
	// 업데이트 때마다 그 행렬의 내용을 업데이트하는 식으로 관리하고,
	// 그렇게 관리되는 행렬들을 통해 SRT 변환 행렬을 계산하여 저장한 뒤
	// 추가적으로 그 과정에서 정리된 행렬들의 데이터를 추출해
	// 부가적인 자료들을 저장하는 과정이 추가된 함수

	Matrix* GetWorld() { return &world; }
	// world 행렬은 public이 아니므로 밖에서 참조할 수 있도록 접근자 설정

	Vector2 GlobalPos() // 실제 그래픽상에서의 표기 좌표를 반환하는 함수
	{
		return Vector2(mat_world._41, mat_world._42);
		// 업데이트 후 최종적으로 구성된 4x4 행렬에서
		// T 변환에 사용되었던 데이터만 가져와 반환
	}

	// 실제 그래픽 상 = 전제 World 상에서 적용되고 있는 scale 값을 반환하는 함수
	Vector2 GlobalScale()
	{
		return global_scale;
	}

	// 이 Transform이 현재 보는 방향을 기준으로 상하좌우를 확인해 반환하는 함수
	Vector2 Right() { return right.Normalized(); }
	Vector2 Left() { return right.Normalized() * -1.0f; }
	Vector2 Up() { return up.Normalized(); }
	Vector2 Down() { return up.Normalized() * -1.0f; }

};