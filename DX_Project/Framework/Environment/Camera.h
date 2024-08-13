#pragma once
class Camera :public Transform {
private:
	MatrixBuffer* view;

	float speed;//카메라의 이동속도를 정하는 변수

	Transform* target;//카메라가 따라갈 대상

	Vector2 offset; //카메라의 전체 화면내에서의 위치 를 기록하는 등
	//여러 방면에서 사용할 2차원 벡터

	Vector2 left_top;//카메라가 가리키고 있는 영역의 왼쪽위 지점
	Vector2 right_bottom;//카메라가 가리키고 있는 영역의 오른쪽 아래 지점
	//카메라가 가리키는 영역은 전체 화면과는 값이 다른 영역이 될수 있기에
	//이를 계산하기 위해 사용하는 값

public:
	Camera();
	~Camera();

	void Update();
	void PostRender();

	void SetPos(Vector2 pos);
	void SetTarget(Transform* target) {
		this->target = target;
	};


private:
	void FreeMode();
	void FollowMode();

	void SetView();
};