#include "framework.h"
#include "AnimateScene.h"

AnimateScene::AnimateScene()
{
	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite1.png");
	player->pos = Vector2(WIN_CENTER_X + 200, WIN_HEIGHT - 200);

	ground[0] = new RectCollider(Vector2(300, 80));
	ground[0]->pos = Vector2(Vector2(150, WIN_HEIGHT - 180));

	ground[1] = new RectCollider(Vector2(WIN_WIDTH / 2, 80));
	ground[1]->pos = Vector2(WIN_WIDTH / 4, WIN_HEIGHT - 100);

	ground[2] = new RectCollider(Vector2(WIN_WIDTH, 80));
	ground[2]->pos = Vector2(WIN_CENTER_X, WIN_HEIGHT - 20);

	ground[3] = new RectCollider(Vector2(300, 80));
	ground[3]->pos = Vector2(WIN_CENTER_X, WIN_CENTER_Y - 100);

	CAM->SetTarget(player);
}

AnimateScene::~AnimateScene()
{
	delete player;

	for (RectCollider* g : ground) {
		delete g;
	}
}

void AnimateScene::Update()
{
	if (KEY_DOWN(VK_F1)) {
		CAM->SetTarget(player);
	}
	else if (KEY_DOWN(VK_F2)) {
		CAM->SetTarget(nullptr);
	}

	if (player->pos.y > WIN_HEIGHT + 150) {
		player->pos = Vector2(WIN_CENTER_X + 200, WIN_HEIGHT - 200);
		player->ResetJumpSpeed();
		//program->SelectScene();
	}

	for (RectCollider* g : ground) {
		if (g != NULL) {
			//���� �浹�� ���θ����� ����
			Vector2 collision;
			if (player->GetCollider()->isCollision(g, &collision)) {

				if (collision.x <= collision.y) {//�����浹
					if (player->pos.x < g->pos.x) {
						player->pos.x -= collision.x;
					}
					else {
						player->pos.x += collision.x;
					}
				}

				else {//�����浹
					//������ �Ʒ��� �������� �浹 �ϴ°Ŷ��
					//������ �ߴ��ϴ� �ڵ带 ������
					if (player->pos.y < g->pos.y) {

						player->pos.y -= collision.y;
						player->landing();
					}
					else {
						//���� �ݴ�� ������ �ö󰡴� ���� ������ �ε����� ��� ���
						//���ӿ� ���󼭴� �ε����ٰ� ��ٷ� ���ϸ� �������� �ʰ�
						//���� �����ϰ� �־��� �ð����ȿ���
						//���� ���̸� �����ϵ��� �ϴ� ���ӵ� ����
						player->ResetJumpSpeed();
						player->pos.y += collision.y;
						
					}
				}
			}
		}
	}

	player->Update();
	for (RectCollider* g : ground) {
		if (g != NULL) {
			g->WorldUpdate();
		}

	}


}

void AnimateScene::Render()
{
	for (RectCollider* g : ground) {
		g->Render();
	}
	player->Render();
}

void AnimateScene::PostRender()
{
	player->PostRender();
}
/*
����: ��������� ����ȭ �ϱ�
���� ���������� �����߿� �浹 ������
�浹�� �Ͼ �������� ������ �״�� ����ǰ�
//����� ������ ĳ���Ͱ� �ִ� ��ġ���� �״�� ����亸�� �ϴ� ������ �߻��ϰ� ����
�̸� �ذ��ϰ� ó���� �����Ϸ� �ߴ� ��ġ���� ���������ϰ� �Ϸ��� ��� �ؾ� �ϴ°�?
Ȥ�� �װ� �� �Ѿ�� �������� ����(=�ٴڿ� ���������� ��������)�� �ǵ��� �Ϸ��� ��� �ؾ� �ϴ°�?

1.�浹������ �ް� �ִ� ��Ȳ���� �� �浹������ ����� �ٽ� ���� �ϵ��� �����
(landing �Լ��� ����� ���� �̴�θ� �ȵȴٴ� �̾߱�)


2.���� ��ġ�� �Ѿ� ȭ��Ʒ� ������ �������� �ϵ��� �����
(�ٴ��� ���� �ʿ䰡 ���� + �� ����̶�� landing�Լ��� �ʿ��Ѱ�?)



3.�������� �ִϸ��̼��� ���� �����ϴµ��߿��� �ش� �ִϸ��̼��� ��� �ǵ��� �ϰ�,
�浹ü�� ��� �ִ� ���߿��� �������� �ƴ϶� �����ϵ��� �Ͽ�
�ش� �ִϸ��̼��� ��������� �ʰ� �ϵ��� �����

*/