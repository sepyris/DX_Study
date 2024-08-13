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
			//벽과 충돌시 가로막히게 설정
			Vector2 collision;
			if (player->GetCollider()->isCollision(g, &collision)) {

				if (collision.x <= collision.y) {//가로충돌
					if (player->pos.x < g->pos.x) {
						player->pos.x -= collision.x;
					}
					else {
						player->pos.x += collision.x;
					}
				}

				else {//세로충돌
					//위에서 아래로 떨어지다 충돌 하는거라면
					//점프를 중단하는 코드를 넣을것
					if (player->pos.y < g->pos.y) {

						player->pos.y -= collision.y;
						player->landing();
					}
					else {
						//만약 반대로 점프로 올라가던 도중 뭔가에 부딪혔을 경우 라면
						//게임에 따라서는 부딪혔다고 곧바로 낙하를 시작하지 않고
						//본래 점프하고 있었을 시간동안에는
						//같은 높이를 유지하도록 하는 게임도 있음
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
과제: 점프기능을 정상화 하기
지금 시점에서는 점프중에 충돌 했을때
충돌이 일어난 시점에서 점프가 그대로 종료되고
//종료된 시점에 캐릭터가 있던 위치에서 그대로 허공답보를 하는 현상이 발생하고 있음
이를 해결하고 처음에 점프하려 했던 위치까지 자유낙하하게 하려면 어떻게 해야 하는가?
혹은 그걸 더 넘어서서 정상적인 점프(=바닥에 닿을때까지 자유낙하)가 되도록 하려면 어떻게 해야 하는가?

1.충돌판정을 받고 있는 상황에라도 그 충돌판정을 벗어나면 다시 낙하 하도록 만들기
(landing 함수의 사양이 지금 이대로면 안된다는 이야기)


2.원래 위치를 넘어 화면아래 끝까지 자유낙하 하도록 만들기
(바닥을 만들 필요가 있음 + 이 방식이라면 landing함수가 필요한가?)



3.점프중인 애니메이션을 만들어서 점프하는도중에는 해당 애니메이션이 출력 되도록 하고,
충돌체를 밝고 있는 도중에는 점프중이 아니라 판정하도록 하여
해당 애니메이션이 재생ㅇ되지 않게 하도록 만들기

*/