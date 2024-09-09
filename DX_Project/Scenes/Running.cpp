#include "framework.h"

Running::Running()
{
	bg = new BackGroundUV(L"Texture/Image/runningbackground.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_X+WIN_WIDTH, WIN_CENTER_Y+WIN_HEIGHT), Vector2(2, 2), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y));

	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite.png");
	player->SetRunning();
	CAM->SetTarget(player);
	player->pos = Vector2(-470, 1000);
	CAM->pos = Vector2(-1100, 700);


	exit_button = new ImageRect(L"Texture/Image/exit_button.png", Vector2(0, 0), Vector2(1, 1), 0.0f, Vector2(150, 75));
	mouse_object = new RectCollider(Vector2(10, 10));

	//초기x위치:-1000
	ground[0] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(3000, GROUND_IMAGE_SIZE.y));
	ground[1] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[2] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(2000, GROUND_IMAGE_SIZE.y));

	wall[0] = new LoopImageRect(WALL_IMAGE_LOC, WALL_IMAGE_SIZE, Vector2(500, 600));
	
	//1단점프 틈:200
	//2단점프 틈:400
	//발판 충돌 위치 설정
	ground[0]->GetCollider()->pos = Vector2(Vector2(500, 1330));
	ground[1]->GetCollider()->pos = Vector2(Vector2(2700, 1330));
	ground[2]->GetCollider()->pos = Vector2(Vector2(4500, 1330));

	wall[0]->GetCollider()->pos = Vector2(Vector2(4700, 1000));

	//이미지 위치 수정
	for (LoopImageRect* g : ground) {
		if (g != NULL) {
			g->pos = Vector2(g->GetCollider()->pos.x, IMAGE_Y_POS);
		}
	}
	for (LoopImageRect* g : wall) {
		if (g != NULL) {
			g->pos = Vector2(g->GetCollider()->pos.x, 1000);
		}
	}

	for (LoopImageRect* g : ground) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	player->Update();
}

Running::~Running()
{
	for (LoopImageRect* g : ground) {
		if (g != NULL) {
			delete g;
		}
	}
	for (LoopImageRect* g : wall) {
		if (g != NULL) {
			delete g;
		}
	}
	delete bg;
}

void Running::Update()
{
	//나가기 버튼 고정
	exit_button->GetCollider()->pos = CAM->GlobalPos()+Vector2(WIN_WIDTH-150, WIN_HEIGHT-50);
	mouse_object->pos = CAM->GlobalPos() + (mouse_pos);
	//카메라가 플레이어 따라가게 설정
	CAM->SetTarget(player);
	//배경 업데이트
	bg->WorldUpdate();
	bg->pos.x = CAM->GlobalPos().x;
	//나가기 버튼 클릭을 위한 마우스 오브젝트 설정
	
	Vector2 collision;
	//나가기 버튼 클릭시
	if (mouse_object->isCollision(exit_button->GetCollider(), &collision)) {
		if (KEY_DOWN(VK_LBUTTON)) {
			//입장맵으로 나가게 설정
			program->CreateScene(4, 3);
			return;
		}
	}
	if (player->pos.y > WIN_HEIGHT * 3) {
		
		player->pos = Vector2(player->pos.x + 200, 700);
	}
	bg->Update();

	for (LoopImageRect* g : ground) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetCollider()->isCollision(g->GetCollider(), &collision)) {
				if (player->pos.y < g->pos.y) {
					if (player->GetCollider()->BottomVX() > g->GetCollider()->TopVX() - 1.0f) {
						player->pos.y -= collision.y * DELTA * 20.0f;
						player->landing();
					}
				}
			}
		}
	}
	for (LoopImageRect* g : wall) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetHitCollider()->isCollision(g->GetCollider(), &collision)) {
				//충돌 관련 내용 수정 필요
				player->IsHit(true);
			}
		}
	}
	player->Update();


	for (LoopImageRect* g : ground) {
		if (g != NULL) {
			g->Update();
		}
	}
	for (LoopImageRect* g : wall) {
		if (g != NULL) {
			g->Update();
		}
	}
	
	exit_button->Update();
	mouse_object->WorldUpdate();
	player->LoadingEnd();
}

void Running::Render()
{
	bg->Render();
	for (LoopImageRect* g : ground) {
		if (g != NULL) {
			g->Render();
		}
	}
	for (LoopImageRect* g : wall) {
		if (g != NULL) {
			g->Render();
		}
	}
	exit_button->Render();
	mouse_object->Render();
	player->Render();
}

void Running::PostRender()
{
	player->PostRender();
}
