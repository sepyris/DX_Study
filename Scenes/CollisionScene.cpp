#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	view = new MatrixBuffer();

	projection = new MatrixBuffer();
	Matrix orthographic = XMMatrixOrthographicOffCenterLH
	(
		0.0f, (float)WIN_WIDTH, // X��ǥ : 0 ~ (â�� ���� ũ��)
		(float)WIN_HEIGHT, 0.0f, // Y��ǥ : (â�� ���� ũ��) ~ 0
		-1.0f, 1.0f // Z��ǥ : -1.0f ~ 1.0f(�ʱⰪ)
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
����:
���� �������� ��� �簢�� �浹���� ��ü�� ����� ������ �̸� ����

���ϱ� ������ ���� ��

1)�÷��̾�� ��ֹ� ���� 3��° �浹������ ������ ũ��� �����
�̸��� enemy�� Ī��
2)enemy�� �ǽð����� �÷��̾��� ��ġ�� �����ؼ� ���ƿ�

3)�÷��̾�� �浹�������,��ٷ� ȸ�� ��ü�� ��򰡷� ������ �����̵�

�߰�
4)���ٷ� �����̵� �ϴ°��� �ƴ϶� 1�ʵ��� �޸� ���¿� ���ٰ�
1�ʰ� ������ ������ �����̵� �ϱ�
(�޸���µ��ȿ� ���� �ٸ������� �ٲٱ�)

5)�÷��̾ �ƴ϶� ��ֹ��� �ε��� ��쿣 ��ֹ��� ���θ������� ������
(�÷��̾�� �������� �ص� ������� ����ó�� �հ� ���� �������)
*/