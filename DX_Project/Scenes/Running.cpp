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
	ground[3] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(550, GROUND_IMAGE_SIZE.y));
	ground[4] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[5] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(500, GROUND_IMAGE_SIZE.y));
	ground[6] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[7] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(200, GROUND_IMAGE_SIZE.y));
	ground[8] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(200, GROUND_IMAGE_SIZE.y));
	ground[9] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[10] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[11] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(500, GROUND_IMAGE_SIZE.y));
	ground[12] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(500, GROUND_IMAGE_SIZE.y));
	ground[13] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(200, GROUND_IMAGE_SIZE.y));
	ground[14] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[15] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(500, GROUND_IMAGE_SIZE.y));
	ground[16] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[17] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[18] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[19] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[20] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));

	wall[0] = new LoopImageRect(WALL_IMAGE_LOC, WALL_IMAGE_SIZE, Vector2(400, 600));
	wall[1] = new LoopImageRect(WALL_IMAGE_LOC, WALL_IMAGE_SIZE, Vector2(200, 600));
	wall[2] = new LoopImageRect(WALL_IMAGE_LOC, WALL_IMAGE_SIZE, Vector2(200, 600));

	hill[0] = new LoopImageRect(HILL_UP_IMAGE_LOC, HILL_IMAGE_SIZE, HILL_IMAGE_SIZE);
	hill[1] = new LoopImageRect(HILL_DOWN_IMAGE_LOC, HILL_IMAGE_SIZE, HILL_IMAGE_SIZE);
	hill[2] = new LoopImageRect(HILL_UP_IMAGE_LOC, HILL_IMAGE_SIZE, HILL_IMAGE_SIZE);
	hill[3] = new LoopImageRect(HILL_UP_IMAGE_LOC, HILL_IMAGE_SIZE, HILL_IMAGE_SIZE);
	hill[4] = new LoopImageRect(HILL_UP_IMAGE_LOC, HILL_IMAGE_SIZE, HILL_IMAGE_SIZE);
	hill[5] = new LoopImageRect(HILL_UP_IMAGE_LOC, HILL_IMAGE_SIZE, HILL_IMAGE_SIZE);
	hill[6] = new LoopImageRect(HILL_DOWN_IMAGE_LOC, HILL_IMAGE_SIZE, HILL_IMAGE_SIZE);
	hill[7] = new LoopImageRect(HILL_DOWN_IMAGE_LOC, HILL_IMAGE_SIZE, HILL_IMAGE_SIZE);
	//1단점프 틈:200
	//2단점프 틈:400
	//대각선발판 길이:300
	//발판 충돌 위치 설정
	//초기위치 고정
	ground[0]->GetCollider()->pos = Vector2(Vector2(500, 1330));

	//이전 발판의 위치 + 이전발판의 사이즈/2 + 이번 발판의 사이즈/2 + 틈,대각
	ground[1]->GetCollider()->pos = Vector2(Vector2(ground[0]->GetCollider()->pos.x + ground[0]->GetSize().x / 2 + ground[1]->GetSize().x / 2 + 200, 1330));
	ground[2]->GetCollider()->pos = Vector2(Vector2(ground[1]->GetCollider()->pos.x + ground[1]->GetSize().x / 2 + ground[2]->GetSize().x / 2 + 400, 1330));
	ground[3]->GetCollider()->pos = Vector2(Vector2(ground[2]->GetCollider()->pos.x + ground[2]->GetSize().x / 2 + ground[3]->GetSize().x / 2 + 200, 1330));
	ground[4]->GetCollider()->pos = Vector2(Vector2(ground[3]->GetCollider()->pos.x + ground[3]->GetSize().x / 2 + ground[4]->GetSize().x / 2 + 300, 1135));
	ground[5]->GetCollider()->pos = Vector2(Vector2(ground[4]->GetCollider()->pos.x + ground[4]->GetSize().x / 2 + ground[5]->GetSize().x / 2 + 300, 1330));
	ground[6]->GetCollider()->pos = Vector2(Vector2(ground[5]->GetCollider()->pos.x + ground[5]->GetSize().x / 2 + ground[6]->GetSize().x / 2 + 200, 1330));
	ground[7]->GetCollider()->pos = Vector2(Vector2(ground[6]->GetCollider()->pos.x + ground[6]->GetSize().x / 2 + ground[7]->GetSize().x / 2, 1250));
	ground[8]->GetCollider()->pos = Vector2(Vector2(ground[7]->GetCollider()->pos.x + ground[7]->GetSize().x / 2 + ground[8]->GetSize().x / 2, 1170));
	ground[9]->GetCollider()->pos = Vector2(Vector2(ground[8]->GetCollider()->pos.x + ground[8]->GetSize().x / 2 + ground[9]->GetSize().x / 2, 1330));
	ground[10]->GetCollider()->pos = Vector2(Vector2(ground[9]->GetCollider()->pos.x + ground[9]->GetSize().x / 2 + ground[10]->GetSize().x / 2 + 400, 1330));
	ground[11]->GetCollider()->pos = Vector2(Vector2(ground[10]->GetCollider()->pos.x + ground[10]->GetSize().x / 2 + ground[11]->GetSize().x / 2 + 200, 1330));
	ground[12]->GetCollider()->pos = Vector2(Vector2(ground[11]->GetCollider()->pos.x + ground[11]->GetSize().x / 2 + ground[12]->GetSize().x / 2 + 200, 1330));
	ground[13]->GetCollider()->pos = Vector2(Vector2(ground[12]->GetCollider()->pos.x + ground[12]->GetSize().x / 2 + ground[13]->GetSize().x / 2 + 300, 1135));
	ground[14]->GetCollider()->pos = Vector2(Vector2(ground[13]->GetCollider()->pos.x + ground[13]->GetSize().x / 2 + ground[14]->GetSize().x / 2 + 300, 940));
	ground[15]->GetCollider()->pos = Vector2(Vector2(ground[14]->GetCollider()->pos.x + ground[14]->GetSize().x / 2 + ground[15]->GetSize().x / 2 + 500, 1330));
	ground[16]->GetCollider()->pos = Vector2(Vector2(ground[15]->GetCollider()->pos.x + ground[15]->GetSize().x / 2 + ground[16]->GetSize().x / 2 + 200, 1330));
	ground[17]->GetCollider()->pos = Vector2(Vector2(ground[16]->GetCollider()->pos.x + ground[16]->GetSize().x / 2 + ground[17]->GetSize().x / 2 + 600, 940));
	ground[18]->GetCollider()->pos = Vector2(Vector2(ground[17]->GetCollider()->pos.x + ground[17]->GetSize().x / 2 + ground[18]->GetSize().x / 2 + 300, 1135));
	ground[19]->GetCollider()->pos = Vector2(Vector2(ground[18]->GetCollider()->pos.x + ground[18]->GetSize().x / 2 + ground[19]->GetSize().x / 2 + 300, 1330));
	ground[20]->GetCollider()->pos = Vector2(Vector2(ground[19]->GetCollider()->pos.x + ground[19]->GetSize().x / 2 + ground[20]->GetSize().x / 2 + 400, 1330));


	hill[0]->GetCollider()->pos = Vector2(Vector2(ground[3]->GetCollider()->pos.x + ground[3]->GetSize().x / 2 + hill[0]->GetSize().x / 2, 1230));
	hill[1]->GetCollider()->pos = Vector2(Vector2(ground[4]->GetCollider()->pos.x + ground[4]->GetSize().x / 2 + hill[1]->GetSize().x / 2, 1230));
	hill[2]->GetCollider()->pos = Vector2(Vector2(ground[12]->GetCollider()->pos.x + ground[12]->GetSize().x / 2 + hill[2]->GetSize().x / 2, 1230));
	hill[3]->GetCollider()->pos = Vector2(Vector2(ground[13]->GetCollider()->pos.x + ground[13]->GetSize().x / 2 + hill[3]->GetSize().x / 2, 1035));
	hill[4]->GetCollider()->pos = Vector2(Vector2(ground[16]->GetCollider()->pos.x + ground[16]->GetSize().x / 2 + hill[4]->GetSize().x / 2, 1230));
	hill[5]->GetCollider()->pos = Vector2(Vector2(hill[4]->GetCollider()->pos.x + hill[4]->GetSize().x / 2 + hill[3]->GetSize().x / 2, 1035));
	hill[6]->GetCollider()->pos = Vector2(Vector2(ground[17]->GetCollider()->pos.x + ground[17]->GetSize().x / 2 + hill[3]->GetSize().x / 2, 1035));
	hill[7]->GetCollider()->pos = Vector2(Vector2(ground[18]->GetCollider()->pos.x + ground[18]->GetSize().x / 2 + hill[7]->GetSize().x / 2, 1230));


	wall[0]->GetCollider()->pos = Vector2(Vector2(ground[2]->GetCollider()->pos.x, 1000));
	wall[1]->GetCollider()->pos = Vector2(Vector2(ground[10]->GetCollider()->pos.x, 1000));
	wall[2]->GetCollider()->pos = Vector2(Vector2(ground[18]->GetCollider()->pos.x, 800));

	//이미지 위치 수정
	for (LoopImageRect* g : ground) {
		if (g != NULL) {
			g->pos = Vector2(g->GetCollider()->pos.x, g->GetCollider()->pos.y + 70);
		}
	}
	for (LoopImageRect* g : wall) {
		if (g != NULL) {
			g->pos = Vector2(g->GetCollider()->pos.x, g->GetCollider()->pos.y);
		}
	}
	for (LoopImageRect* g : hill) {
		if (g != NULL) {
			g->pos = Vector2(g->GetCollider()->pos.x, g->GetCollider()->pos.y-20);
		}
	}
	GroundUpdate();
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
	for (LoopImageRect* g : hill) {
		if (g != NULL) {
			delete g;
		}
	}
	delete bg;
}

void Running::GroundUpdate()
{
	for (LoopImageRect* g : wall) {
		if (g != NULL) {
			g->Update();
		}
	}
	for (LoopImageRect* g : hill) {
		if (g != NULL) {
			g->Update();
		}
	}

	for (LoopImageRect* g : ground) {
		if (g != NULL) {
			g->Update();
		}
	}
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
	for (LoopImageRect* g : hill) {
		if (g != NULL) {
			if (player->GetCollider()->isCollision(g->GetCollider())) {
				player->pos.y -= DELTA * 300.0f;
				player->landing();
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


	
	GroundUpdate();
	exit_button->Update();
	mouse_object->WorldUpdate();
	player->LoadingEnd();
}

void Running::Render()
{
	bg->Render();
	
	for (LoopImageRect* g : wall) {
		if (g != NULL) {
			g->Render();
		}
	}
	for (LoopImageRect* g : hill) {
		if (g != NULL) {
			g->Render();
		}
	}
	for (LoopImageRect* g : ground) {
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
