#include "framework.h"

Transform::Transform(Vector2 p, Vector2 s, float a, Matrix* parent)
	: pos(p), scale(s), rot(Float3(0.0f, 0.0f, a)), parent(parent), is_active(true)
{
	/*
	// 본 생성자에서는
	// SRT 변환 행렬을 만들어 이를 저장해둠

	S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	R = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	T = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	
	world = S * R * T;

	이 내용들은 이제 WorldUpdate를 호출해서 할 예정이므로 여기선 하지 않음
	*/

	world = XMMatrixIdentity();
	// 단위행렬로 world 행렬 초기화

	right = Vector2(1, 0);
	up = Vector2(0, -1);
	// 오른쪽과 위를 가리키는 벡터 역시 일단은 초기화

	WB = new MatrixBuffer();
	
	WorldUpdate();
	// 위에 만들어진 멤버들을 이용하여 초기화
}

Transform::~Transform()
{
}

void Transform::WorldTransform(Matrix* parent)
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	Matrix R = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	Matrix T = XMMatrixTranslation(pos.x, pos.y, 0.0f);

	world = S * R * T;

	if (parent != NULL)
		world *= *parent;
}

void Transform::WorldUpdate()
{

	S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	/*
	오브젝트의 Scale(=크기)을 행렬로 만들어 저장
	이 함수는 Transform에 등록된 scale을 4X4 행렬의 형태로 변환시켜주는 함수
	
	실제로는 다음과 같이 행렬을 구성
	scale.x = a, scale.y = b, scale.z = c라 하면
	( a 0 0 0 )
	( 0 b 0 0 )
	( 0 0 c 0 )
	( 0 0 0 1 )
	위와 같은 행렬을 구성해서 반환
	*/

	R = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	//R = XMMatrixRotationZ(rot.z);
	/*
	트랜스폼의 3개 축 각각의 회전도를 행렬에 저장
	...해야 하나, 우리는 3개 축 전부를 쓰지 않고
	z축 하나만 쓸 것이기 때문에 위쪽 함수 대신 아래쪽 함수를 사용함
	(3D로 넘어가게 된다면 아래가 아니라 위쪽을 써야 함)

	아래쪽 함수가 실제로 어떤 값을 반환하는지까지만 설명
	위쪽 함수가 실제로는 3개의 행렬을 만들어 이를 전부 곱한 행렬을 반환한다면
	아래쪽 함수는 그 만들어지는 3개 행렬 중 z축에 대응하는 마지막 하나만을
	직접 반환하는 함수

	아래쪽 함수는 rot.z = a라고 가정시 다음과 같은 행렬이 만들어짐
	( cos(a) -sin(a) 0 0 )
	( sin(a) cos(a)  0 0 )
	(   0       0    1 0 )
	(   0       0    0 1 )
	이런 식으로 Z축 그 자체에 올라타지 않는 부분인
	11, 12, 21, 22번 값에 삼각함수가 적용되는 식으로 작동함
	다른 함수들(X,Y) 역시 마찬가지에 위치만 다르다
	*/
	T = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	/*
	오브젝트의 "투영", 즉 "이동"을 행렬에 저장
	그냥 간단히 말해 좌표에 따른 이동을 이 행렬을 통해 저장한다고 보면 OK

	( 1 0 0 0 )
	( 0 1 0 0 )
	( 0 0 1 0 )
	( x y z 1 )
	좌표에 따라 위와 같은 행렬이 만들어지게 됨
	*/

	P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
	IP = XMMatrixInverse(NULL, P);
	// 피벗을 사용하다고 전제했을 때 SRT 변환 행렬에 추가해야 할 2개 행렬
	// P : T와 거의 동일한 역할을 하나,
	// 이 트랜스폼의 중심점이 아닌 다른 지점에서 회전을 하겠다는 이야기
	// IP : P의 역행렬
	// 계산과정에서 P의 역행렬을 미리 곱해뒀야 문제가 생기지 않기 때문

	// 특별히 피벗의 값을 지정하지 않으면 단위 행렬이 만들어지니
	// 지금은 신경쓰지 않아도 OK

	world = IP * S * R * T * P;
	// 피벗까지 포함하면 위와 같이 만들어짐

	// 만약 부모가 존재하는 트랜스폼이면
	if (parent != NULL)
		world *= *parent;

	// 여기까지 World 행렬을 구하는 과정이었고
	// 이 뒤부터는 그 뒤에 이 트랜스폼에 저장할 자료들을
	// 이 행렬에서 추출하는 과정

	WB->Set(world);

	XMStoreFloat4x4(&mat_world, world);
	// 4x4 행렬로 이뤄진 데이터에서 데이터들을 추출,
	// XMFloat4x4 자료형으로 이뤄진 행렬에 그 값들을 복사하는 함수

	right = Vector2(mat_world._11, mat_world._12);
	up = Vector2(mat_world._21, mat_world._22);
	// 이 트랜스폼이 보고 있는 방향을 기준으로 위와 오른쪽을 재정의
	// (= 현 시점의 이 오브젝트의 회전에 따라 
	// 위나 오른쪽의 기준이 달라질 수 있기 때문에 재정의하는 것)

	XMVECTOR outS, outR, outT;
	// 변환 완료된 월드 행렬에서 추출한 Scale, Rotation, Translocation 데이터를
	// 저장할 변수

	XMMatrixDecompose(&outS, &outR, &outT, world);
	// 월드 행렬에서 데이털르 추출, 각각의 변수에 해당 데이터들을 저장
	XMStoreFloat2(&global_scale, outS);
	// 같은 이름의 4x4 버젼과 마찬가지로, 실수 2개로 이뤄진 데이터를 복사
}
