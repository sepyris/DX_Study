#include "framework.h"

Camera::Camera():
	speed(500),target(nullptr),offset(0,0)
{
	view = new MatrixBuffer();
}

Camera::~Camera()
{
	delete view;
}

void Camera::Update()
{
	if (target != nullptr) {
		//현재 주시중인 대상이 있으면
		FollowMode();//따라가는 모드로서 카메라를 업데이트
	}
	else {
		//없다면
		FreeMode();//자유이동 모드로서 카메라를 업데이트
	}

	//어느쪽이건 실행해서 카메라의 위치가 확정 되었다면
	//뷰 행렬을 업데이트

	SetView();
}

void Camera::PostRender()
{
}

void Camera::SetPos(Vector2 pos)
{
}

void Camera::FreeMode()//카메라를 자유로이 움직일수 있는 모드
{
	if (KEY_PRESS(VK_RBUTTON)) {//마우스 오른쪽 버튼이 눌리고 있는 동안
		//카메라의 위치를 바꾸려고 함

		//여기서는 오프셋이라는 값을 이용해서 카메라의 위치가 화면을 벗어나지 않도록 하는 선에서
		//시점을 바꾸려고 함

		/*
		view행렬은 시점이 어디인지를 정의하는 역할
		2D에서로 그 역할을 한정지어 설명하자면
		이 view가 위치하고 있는 좌표값은
		화면 전체의 왼쪽위가 시작되는 지점을 가리키고 있다
		따라서 보여주고 있는 화면이 전체 화면의 범위를 벗어나지 않도록 하려면
		그 카메라가 위치할수 있는 범위를 지정해줘야 함
		*/
		if (KEY_PRESS('W')) {
			if (offset.y >= -(WIN_HEIGHT - SCREEN_SIZE_Y) / 2.0f) {
				offset.y -= speed * DELTA;
			}
		}
		if (KEY_PRESS('S')) {
			if (offset.y <= (WIN_HEIGHT - SCREEN_SIZE_Y) / 2.0f) {
				//이렇게 한도값을 지정해두면
				//현재 출력하는 화면의 확대/축소에 따라 카메라를 움직일수 있는 영역이 더 많아짐
				// +배경밖으로 카메라가 나가는것을 최대한 억제 가능
				// 
				//다만 현 시점에서는 확대를 했을때는 화면 밖으로 나가는것을 막지 못하고 있음
				// 이는 확대/축소를 하면서 보여지는 화면이 달라진다 하더라도
				// 오프셋값 그 자체는 최소치가 0,0으로 그대로이기 때문에
				// 확대되면서 왼쪽위로 뻗어나가는 배경을 따라잡지 못하기 때문
				//
				offset.y += speed * DELTA;
			}
		}
		if (KEY_PRESS('A')) {
			if (offset.x >= -(WIN_WIDTH - SCREEN_SIZE_X) / 2.0f) {
				offset.x -= speed * DELTA;
			}
		}
		if (KEY_PRESS('D')) {
			if (offset.x <= (WIN_WIDTH - SCREEN_SIZE_X)/2.0f) {
				offset.x += speed * DELTA;
			}
		}
	}
	float test = WIN_WIDTH;
	float test2 = SCREEN_SIZE_X;
	pos = offset;//위에서 이용했던 offset의 데이터를
	//그대로 카메라의 pos에 입력

	left_top = GlobalPos();//현재 이 카메라가 가리키고 있는 공간이
	//실제 좌표로는 정확히 어디인지를 따로 보관하기 위해 저장

	right_bottom = left_top + Vector2(WIN_WIDTH, WIN_HEIGHT);
	//오른쪽 아래는 왼쪽위 좌표에 현재 화면이 출력하는 범위를 더해서 확보

	//이 두개의 값은 필요할때 쓰려고 미리 만들어둔것으로
	//지금 당장은 아무런 역할도 하지 않음
}

void Camera::FollowMode()
{	
	Vector2 target_pos = target->GlobalPos() - Vector2(SCREEN_SIZE_X / 2.0f, SCREEN_SIZE_Y / 2.0f);	

	if (target_pos.y >= -(WIN_HEIGHT - SCREEN_SIZE_Y * 2)-10.0f) {
		target_pos.y = -(WIN_HEIGHT - SCREEN_SIZE_Y * 2) - 10.0f;
	}
	if (target_pos.y <= (WIN_HEIGHT - SCREEN_SIZE_Y * 2) + 10.0f) {
		target_pos.y = (WIN_HEIGHT - SCREEN_SIZE_Y * 2) + 10.0f;
	}
	if (target_pos.x >= -(WIN_WIDTH - SCREEN_SIZE_X * 2) - 10.0f) {
		target_pos.x = -(WIN_WIDTH - SCREEN_SIZE_X * 2) - 10.0f;
	}
	if (target_pos.x <= (WIN_WIDTH - SCREEN_SIZE_X * 2) + 10.0f) {
		target_pos.x = (WIN_WIDTH - SCREEN_SIZE_X * 2) + 10.0f;
	}
	//LERP(s,e,t)(s+(e-s)*t)
	// 
	pos = LERP(pos, target_pos, speed / 100.0f * DELTA);
	//pos = offset;
	// 위의 LERP라는 보간식은 다음과 같은 구조 :
	// start + (end - start) * ratio
	// -> 시작 지점에서 종료 지점까지 방향벡터를 따라가되,
	// 한 번 호출되었을 떄 따라가는 양은 전체 길이에서 입력된 ratio의 값에 비례하여
	// 그 길이가 정해지는 식
	// 비율이라는 특성상, ratio에는 0~1 사이의 값이 들어가야 정상적인 작동이 보장됨
	
}

void Camera::SetView()
//카메라의 위치등을 저장한 뷰 행렬을 만들어내는 함수
//만들어낸 후에는 셰이더의 1번 슬롯에 보냄
{
	WorldUpdate();
	Matrix inv_view = XMMatrixInverse(NULL, world);
	//뷰 행렬은 wvp계산을 하여 구할때
	//계산을 끝낸 월드 행렬의 역행렬을 구해서 만듬

	view->Set(inv_view);//구한 역행렬을 뷰에 세팅
	view->SetVS(1);//셰이더에 세팅

}
