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
		//���� �ֽ����� ����� ������
		FollowMode();//���󰡴� ���μ� ī�޶� ������Ʈ
	}
	else {
		//���ٸ�
		FreeMode();//�����̵� ���μ� ī�޶� ������Ʈ
	}

	//������̰� �����ؼ� ī�޶��� ��ġ�� Ȯ�� �Ǿ��ٸ�
	//�� ����� ������Ʈ

	SetView();
}

void Camera::PostRender()
{
}

void Camera::SetPos(Vector2 pos)
{
}

void Camera::FreeMode()//ī�޶� �������� �����ϼ� �ִ� ���
{
	if (KEY_PRESS(VK_RBUTTON)) {//���콺 ������ ��ư�� ������ �ִ� ����
		//ī�޶��� ��ġ�� �ٲٷ��� ��

		//���⼭�� �������̶�� ���� �̿��ؼ� ī�޶��� ��ġ�� ȭ���� ����� �ʵ��� �ϴ� ������
		//������ �ٲٷ��� ��

		/*
		view����� ������ ��������� �����ϴ� ����
		2D������ �� ������ �������� �������ڸ�
		�� view�� ��ġ�ϰ� �ִ� ��ǥ����
		ȭ�� ��ü�� �������� ���۵Ǵ� ������ ����Ű�� �ִ�
		���� �����ְ� �ִ� ȭ���� ��ü ȭ���� ������ ����� �ʵ��� �Ϸ���
		�� ī�޶� ��ġ�Ҽ� �ִ� ������ ��������� ��
		*/
		if (KEY_PRESS('W')) {
			if (offset.y >= -(WIN_HEIGHT - SCREEN_SIZE_Y) / 2.0f) {
				offset.y -= speed * DELTA;
			}
		}
		if (KEY_PRESS('S')) {
			if (offset.y <= (WIN_HEIGHT - SCREEN_SIZE_Y) / 2.0f) {
				//�̷��� �ѵ����� �����صθ�
				//���� ����ϴ� ȭ���� Ȯ��/��ҿ� ���� ī�޶� �����ϼ� �ִ� ������ �� ������
				// +�������� ī�޶� �����°��� �ִ��� ���� ����
				// 
				//�ٸ� �� ���������� Ȯ�븦 �������� ȭ�� ������ �����°��� ���� ���ϰ� ����
				// �̴� Ȯ��/��Ҹ� �ϸ鼭 �������� ȭ���� �޶����� �ϴ���
				// �����°� �� ��ü�� �ּ�ġ�� 0,0���� �״���̱� ������
				// Ȯ��Ǹ鼭 �������� ������� ����� �������� ���ϱ� ����
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
	pos = offset;//������ �̿��ߴ� offset�� �����͸�
	//�״�� ī�޶��� pos�� �Է�

	left_top = GlobalPos();//���� �� ī�޶� ����Ű�� �ִ� ������
	//���� ��ǥ�δ� ��Ȯ�� ��������� ���� �����ϱ� ���� ����

	right_bottom = left_top + Vector2(WIN_WIDTH, WIN_HEIGHT);
	//������ �Ʒ��� ������ ��ǥ�� ���� ȭ���� ����ϴ� ������ ���ؼ� Ȯ��

	//�� �ΰ��� ���� �ʿ��Ҷ� ������ �̸� �����а�����
	//���� ������ �ƹ��� ���ҵ� ���� ����
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
	// ���� LERP��� �������� ������ ���� ���� :
	// start + (end - start) * ratio
	// -> ���� �������� ���� �������� ���⺤�͸� ���󰡵�,
	// �� �� ȣ��Ǿ��� �� ���󰡴� ���� ��ü ���̿��� �Էµ� ratio�� ���� ����Ͽ�
	// �� ���̰� �������� ��
	// �����̶�� Ư����, ratio���� 0~1 ������ ���� ���� �������� �۵��� �����
	
}

void Camera::SetView()
//ī�޶��� ��ġ���� ������ �� ����� ������ �Լ�
//���� �Ŀ��� ���̴��� 1�� ���Կ� ����
{
	WorldUpdate();
	Matrix inv_view = XMMatrixInverse(NULL, world);
	//�� ����� wvp����� �Ͽ� ���Ҷ�
	//����� ���� ���� ����� ������� ���ؼ� ����

	view->Set(inv_view);//���� ������� �信 ����
	view->SetVS(1);//���̴��� ����

}
