#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	view = new MatrixBuffer();

	projection = new MatrixBuffer();
	Matrix orthographic = XMMatrixOrthographicOffCenterLH
	(
		0.0f, (float)WIN_WIDTH, // X좌표 : 0 ~ (창의 가로 크기)
		(float)WIN_HEIGHT, 0.0f, // Y좌표 : (창의 세로 크기) ~ 0
		-1.0f, 1.0f // Z좌표 : -1.0f ~ 1.0f(초기값)
	);

	projection->Set(orthographic);

	player = new RectCollider(Vector2(50, 50));
	player->pos = Vector2(WIN_CENTER_X, WIN_CENTER_Y);

	enemy = new RectCollider(Vector2(50, 50));
	enemy->pos = Vector2(WIN_CENTER_X/2, WIN_CENTER_Y/2);

	obstackle = new RectCollider(Vector2(50, 400));
	obstackle->pos = Vector2(WIN_CENTER_X / 2, WIN_CENTER_Y);
}

CollisionScene::~CollisionScene()
{
	delete player;
	delete obstackle;
	delete enemy;

	delete view;
	delete projection;
}

void CollisionScene::Update()
{
	player->WorldUpdate();
	enemy->WorldUpdate();
	obstackle->WorldUpdate();
	//player->rot.z += 1.0f * DELTA;

	if (enemy->pos.x < player->pos.x) {
		enemy->pos.x += 20.0f * DELTA;
	}
	if (enemy->pos.x > player->pos.x) {
		enemy->pos.x -= 20.0f * DELTA;
	}
	if (enemy->pos.y < player->pos.y) {
		enemy->pos.y += 20.0f * DELTA;
	}
	if (enemy->pos.y > player->pos.y) {
		enemy->pos.y -= 20.0f * DELTA;
	}
	
	if (player->isPointCollision(mouse_pos)) {
		player->SetColor(1, 0, 0);
	}

	else if (player->isRectCollision(obstackle)) {
		player->SetColor(0, 0, 1);
	}
	else {
		player->SetColor(0, 1, 0);
	}


	if (obstackle->isPointCollision(mouse_pos)) {
		obstackle->SetColor(1, 0, 0);
	}
	else if (obstackle->isRectCollision(player)) {
		obstackle->SetColor(0, 0, 1);
	}
	else {
		obstackle->SetColor(0, 1, 0);
	}

	bool is_collider = false;
	if (player->isRectCollision(obstackle)) {
		is_collider = true;
	}

	if (!is_collider) {
		if (KEY_PRESS(VK_LEFT)) {
			player->pos.x -= 100.0f * DELTA;
		}
		if (KEY_PRESS(VK_RIGHT)) {
			player->pos.x += 100.0f * DELTA;
		}
		if (KEY_PRESS(VK_UP)) {
			player->pos.y -= 100.0f * DELTA;
		}
		if (KEY_PRESS(VK_DOWN)) {
			player->pos.y += 100.0f * DELTA;
		}
	}
	
}

void CollisionScene::Render()
{
	view->SetVS(1);
	projection->SetVS(2);

	player->Render();
	enemy->Render();
	obstackle->Render();
}
/*
과제:
지금 시점에서 적어도 사각형 충돌판정 자체는 만들어 봤으니 이를 응용

피하기 게임을 만들어볼 것

1)플레이어와 장애물 말고 3번째 충돌판정을 적당한 크기로 만들기
이름을 enemy로 칭함
2)enemy는 실시간으로 플레이어의 위치를 추적해서 날아옴

3)플레이어와 충돌했을경우,곧바로 회면 전체중 어딘가로 무작위 순간이동

추가
4)곱다로 순간이동 하는것이 아니라 1초동안 휴면 상태에 들어갔다가
1초가 지나고 나서야 순간이동 하기
(휴면상태동안엔 색을 다른색으로 바꾸기)

5)플레이어가 아니라 장애물에 부딪힌 경우엔 장애물에 가로막히도록 만들어볼것
(플레이어는 막히도록 해도 상관없고 지금처럼 뚫고 가도 상관없음)
*/