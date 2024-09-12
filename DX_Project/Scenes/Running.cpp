#include "framework.h"

Running::Running()
{
	bg = new BackGroundUV(L"Texture/Image/runningbackground.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_X+WIN_WIDTH, WIN_CENTER_Y+WIN_HEIGHT), Vector2(2, 2), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y));

	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite.png");
	player->SetRunning();
	CAM->SetTarget(player);
	player->pos = Vector2(-470, 1000);
	CAM->pos = Vector2(-400, 700);


	exit_button = new ImageRect(L"Texture/Image/exit_button.png", Vector2(0, 0), Vector2(1, 1), 0.0f, Vector2(150, 75));
	mouse_object = new RectCollider(Vector2(10, 10));

	hp_background = new RectCollider(Vector2(500, 50));
	hp_object = new RectCollider(Vector2(450, 30));

	CreateObject();
	SetObjectPos();

	ObjectUpdate();
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

void Running::CreateObject()
{
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
	ground[21] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[22] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[23] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[24] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[25] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[26] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[27] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[28] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[29] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[30] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[31] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[32] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(200, GROUND_IMAGE_SIZE.y));
	ground[33] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[34] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	//랜덤발판
	ground[35] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[36] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[37] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[38] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[39] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[40] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[41] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[42] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[43] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[44] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[45] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[46] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[47] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[48] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[49] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	//랜덤발판 끝
	ground[50] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[51] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(400, GROUND_IMAGE_SIZE.y));
	ground[52] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(1000, GROUND_IMAGE_SIZE.y));
	ground[53] = new LoopImageRect(GROUND_IMAGE_LOC, GROUND_IMAGE_SIZE, Vector2(3000, GROUND_IMAGE_SIZE.y));

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
	hill[8] = new LoopImageRect(HILL_DOWN_IMAGE_LOC, HILL_IMAGE_SIZE, HILL_IMAGE_SIZE);
	hill[9] = new LoopImageRect(HILL_DOWN_IMAGE_LOC, HILL_IMAGE_SIZE, HILL_IMAGE_SIZE);

	for (int i = 0; i < 20; i++) {
		mushroom[i] = new Mushroom(L"Texture/AnimateScene/Animation/mushroom.png");
	}
	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			m->SetRunning();
		}
	}
}

void Running::SetObjectPos()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());

	//1단점프 틈:200
	//2단점프 틈:400
	//대각선발판 길이:300
	//발판 충돌 위치 설정
	//초기위치 고정
	ground[0]->GetCollider()->pos = Vector2(Vector2(500, 1330));

	//이전 발판의 위치 + 이전발판의 사이즈/2 + 이번 발판의 사이즈/2 + 틈,대각
	ground[1]->GetCollider()->pos = Vector2(Vector2(ground[0]->GetCollider()->pos.x + ground[0]->GetSize().x / 2 + ground[1]->GetSize().x / 2 + 200, 1340));
	ground[2]->GetCollider()->pos = Vector2(Vector2(ground[1]->GetCollider()->pos.x + ground[1]->GetSize().x / 2 + ground[2]->GetSize().x / 2 + 400, 1340));
	ground[3]->GetCollider()->pos = Vector2(Vector2(ground[2]->GetCollider()->pos.x + ground[2]->GetSize().x / 2 + ground[3]->GetSize().x / 2 + 200, 1340));
	ground[4]->GetCollider()->pos = Vector2(Vector2(ground[3]->GetCollider()->pos.x + ground[3]->GetSize().x / 2 + ground[4]->GetSize().x / 2 + 300, 1145));
	ground[5]->GetCollider()->pos = Vector2(Vector2(ground[4]->GetCollider()->pos.x + ground[4]->GetSize().x / 2 + ground[5]->GetSize().x / 2 + 300, 1340));
	ground[6]->GetCollider()->pos = Vector2(Vector2(ground[5]->GetCollider()->pos.x + ground[5]->GetSize().x / 2 + ground[6]->GetSize().x / 2 + 200, 1340));
	ground[7]->GetCollider()->pos = Vector2(Vector2(ground[6]->GetCollider()->pos.x + ground[6]->GetSize().x / 2 + ground[7]->GetSize().x / 2, 1260));
	ground[8]->GetCollider()->pos = Vector2(Vector2(ground[7]->GetCollider()->pos.x + ground[7]->GetSize().x / 2 + ground[8]->GetSize().x / 2, 1180));
	ground[9]->GetCollider()->pos = Vector2(Vector2(ground[8]->GetCollider()->pos.x + ground[8]->GetSize().x / 2 + ground[9]->GetSize().x / 2, 1340));
	ground[10]->GetCollider()->pos = Vector2(Vector2(ground[9]->GetCollider()->pos.x + ground[9]->GetSize().x / 2 + ground[10]->GetSize().x / 2 + 400, 1340));
	ground[11]->GetCollider()->pos = Vector2(Vector2(ground[10]->GetCollider()->pos.x + ground[10]->GetSize().x / 2 + ground[11]->GetSize().x / 2 + 200, 1340));
	ground[12]->GetCollider()->pos = Vector2(Vector2(ground[11]->GetCollider()->pos.x + ground[11]->GetSize().x / 2 + ground[12]->GetSize().x / 2 + 200, 1340));
	ground[13]->GetCollider()->pos = Vector2(Vector2(ground[12]->GetCollider()->pos.x + ground[12]->GetSize().x / 2 + ground[13]->GetSize().x / 2 + 300, 1145));
	ground[14]->GetCollider()->pos = Vector2(Vector2(ground[13]->GetCollider()->pos.x + ground[13]->GetSize().x / 2 + ground[14]->GetSize().x / 2 + 300, 950));
	ground[15]->GetCollider()->pos = Vector2(Vector2(ground[14]->GetCollider()->pos.x + ground[14]->GetSize().x / 2 + ground[15]->GetSize().x / 2 + 500, 1340));
	ground[16]->GetCollider()->pos = Vector2(Vector2(ground[15]->GetCollider()->pos.x + ground[15]->GetSize().x / 2 + ground[16]->GetSize().x / 2 + 200, 1340));
	ground[17]->GetCollider()->pos = Vector2(Vector2(ground[16]->GetCollider()->pos.x + ground[16]->GetSize().x / 2 + ground[17]->GetSize().x / 2 + 600, 950));
	ground[18]->GetCollider()->pos = Vector2(Vector2(ground[17]->GetCollider()->pos.x + ground[17]->GetSize().x / 2 + ground[18]->GetSize().x / 2 + 300, 1145));
	ground[19]->GetCollider()->pos = Vector2(Vector2(ground[18]->GetCollider()->pos.x + ground[18]->GetSize().x / 2 + ground[19]->GetSize().x / 2 + 300, 1340));
	ground[20]->GetCollider()->pos = Vector2(Vector2(ground[19]->GetCollider()->pos.x + ground[19]->GetSize().x / 2 + ground[20]->GetSize().x / 2 + 400, 1340));
	ground[21]->GetCollider()->pos = Vector2(Vector2(ground[20]->GetCollider()->pos.x + ground[20]->GetSize().x / 2 + ground[21]->GetSize().x / 2 + 100, 1260));
	ground[22]->GetCollider()->pos = Vector2(Vector2(ground[21]->GetCollider()->pos.x + ground[21]->GetSize().x / 2 + ground[22]->GetSize().x / 2 + 100, 1180));
	ground[23]->GetCollider()->pos = Vector2(Vector2(ground[22]->GetCollider()->pos.x + ground[22]->GetSize().x / 2 + ground[23]->GetSize().x / 2 + 100, 1180));
	ground[24]->GetCollider()->pos = Vector2(Vector2(ground[23]->GetCollider()->pos.x + ground[23]->GetSize().x / 2 + ground[24]->GetSize().x / 2 + 100, 1100));
	ground[25]->GetCollider()->pos = Vector2(Vector2(ground[24]->GetCollider()->pos.x + ground[24]->GetSize().x / 2 + ground[25]->GetSize().x / 2 + 100, 1260));
	ground[26]->GetCollider()->pos = Vector2(Vector2(ground[25]->GetCollider()->pos.x + ground[25]->GetSize().x / 2 + ground[26]->GetSize().x / 2 + 100, 950));
	ground[27]->GetCollider()->pos = Vector2(Vector2(ground[26]->GetCollider()->pos.x + ground[26]->GetSize().x / 2 + ground[27]->GetSize().x / 2 + 400, 950));
	ground[28]->GetCollider()->pos = Vector2(Vector2(ground[27]->GetCollider()->pos.x + ground[27]->GetSize().x / 2 + ground[28]->GetSize().x / 2 + 100, 1260));
	ground[29]->GetCollider()->pos = Vector2(Vector2(ground[28]->GetCollider()->pos.x + ground[28]->GetSize().x / 2 + ground[29]->GetSize().x / 2 + 200, 1340));
	ground[30]->GetCollider()->pos = Vector2(Vector2(ground[29]->GetCollider()->pos.x + ground[29]->GetSize().x / 2 + ground[30]->GetSize().x / 2, 1260));
	ground[31]->GetCollider()->pos = Vector2(Vector2(ground[30]->GetCollider()->pos.x + ground[30]->GetSize().x / 2 + ground[31]->GetSize().x / 2, 1180));
	ground[32]->GetCollider()->pos = Vector2(Vector2(ground[31]->GetCollider()->pos.x + ground[31]->GetSize().x / 2 + ground[32]->GetSize().x / 2, 1340));
	ground[33]->GetCollider()->pos = Vector2(Vector2(ground[32]->GetCollider()->pos.x + ground[32]->GetSize().x / 2 + ground[33]->GetSize().x / 2, 870));
	ground[34]->GetCollider()->pos = Vector2(Vector2(ground[33]->GetCollider()->pos.x + ground[33]->GetSize().x / 2 + ground[34]->GetSize().x / 2 + 600, 1340));
	int y_pos = 1340;
	for (int i = 35; i < 50; i++) {
		std::uniform_int_distribution<int> rand_count(0, 4);
		switch (rand_count(gen)) {
		case 0:
			y_pos = 1340;
			break;
		case 1:
			y_pos = 1260;
			break;
		case 2:
			y_pos = 1180;
			break;
		case 3:
			y_pos = 1100;
			break;
		case 4:
			//제일 낮은곳에서 제일높은곳으로 갈수 없는 문제가 있어
			//이전에 제일 낮은곳이었으면 다음으로 높은 높이로 설정
			if (y_pos == 1340) {
				y_pos = 1100;
			}
			else {
				y_pos = 1020;
			}

			break;
		}
		ground[i]->GetCollider()->pos = Vector2(Vector2(ground[i - 1]->GetCollider()->pos.x + ground[i - 1]->GetSize().x / 2 + ground[i]->GetSize().x / 2 + 150, y_pos));

	}
	ground[50]->GetCollider()->pos = Vector2(Vector2(ground[49]->GetCollider()->pos.x + ground[49]->GetSize().x / 2 + ground[50]->GetSize().x / 2 + 200, 1340));

	ground[51]->GetCollider()->pos = Vector2(Vector2(ground[50]->GetCollider()->pos.x + ground[50]->GetSize().x / 2 + ground[51]->GetSize().x / 2 + 200, 1340));
	ground[52]->GetCollider()->pos = Vector2(Vector2(ground[51]->GetCollider()->pos.x + ground[51]->GetSize().x / 2 + ground[52]->GetSize().x / 2 + 200, 1100));
	ground[53]->GetCollider()->pos = Vector2(Vector2(ground[52]->GetCollider()->pos.x + ground[52]->GetSize().x / 2 + ground[53]->GetSize().x / 2 + 700, 1340));
	Environment::Get()->GetMainCamera()->SetRunnuingLastPos(ground[53]->GetCollider()->pos.x + ground[53]->GetSize().x / 2);

	for (LoopImageRect* g : ground) {
		if (g != NULL) {
			if (g->GetSize().x == 400) {
				std::uniform_int_distribution<int> rand_count(0, 1);
				if (rand_count(gen) == 1) {
					for (Mushroom* m : mushroom) {
						if (m != NULL) {
							if (!m->Islive()) {
								m->IsCreate();
								m->pos = Vector2(g->GetCollider()->pos.x, g->GetCollider()->pos.y - 50);
								break;
							}
						}
					}
				}
			}
		}
	}

	hill[0]->GetCollider()->pos = Vector2(Vector2(ground[3]->GetCollider()->pos.x + ground[3]->GetSize().x / 2 + hill[0]->GetSize().x / 2, 1240));
	hill[1]->GetCollider()->pos = Vector2(Vector2(ground[4]->GetCollider()->pos.x + ground[4]->GetSize().x / 2 + hill[1]->GetSize().x / 2, 1240));
	hill[2]->GetCollider()->pos = Vector2(Vector2(ground[12]->GetCollider()->pos.x + ground[12]->GetSize().x / 2 + hill[2]->GetSize().x / 2, 1240));
	hill[3]->GetCollider()->pos = Vector2(Vector2(ground[13]->GetCollider()->pos.x + ground[13]->GetSize().x / 2 + hill[3]->GetSize().x / 2, 1045));
	hill[4]->GetCollider()->pos = Vector2(Vector2(ground[16]->GetCollider()->pos.x + ground[16]->GetSize().x / 2 + hill[4]->GetSize().x / 2, 1240));
	hill[5]->GetCollider()->pos = Vector2(Vector2(hill[4]->GetCollider()->pos.x + hill[4]->GetSize().x / 2 + hill[3]->GetSize().x / 2, 1045));
	hill[6]->GetCollider()->pos = Vector2(Vector2(ground[17]->GetCollider()->pos.x + ground[17]->GetSize().x / 2 + hill[3]->GetSize().x / 2, 1045));
	hill[7]->GetCollider()->pos = Vector2(Vector2(ground[18]->GetCollider()->pos.x + ground[18]->GetSize().x / 2 + hill[7]->GetSize().x / 2, 1240));

	hill[8]->GetCollider()->pos = Vector2(Vector2(ground[52]->GetCollider()->pos.x + ground[52]->GetSize().x / 2 + hill[8]->GetSize().x / 2, 1200));
	hill[9]->GetCollider()->pos = Vector2(Vector2(hill[8]->GetCollider()->pos.x + hill[8]->GetSize().x / 2 + hill[9]->GetSize().x / 2, 1395));

	wall[0]->GetCollider()->pos = Vector2(Vector2(ground[2]->GetCollider()->pos.x, 1000));
	wall[1]->GetCollider()->pos = Vector2(Vector2(ground[10]->GetCollider()->pos.x, 1000));
	wall[2]->GetCollider()->pos = Vector2(Vector2(ground[18]->GetCollider()->pos.x, 800));


	//이미지 위치 수정
	for (LoopImageRect* g : ground) {
		if (g != NULL) {
			g->pos = Vector2(g->GetCollider()->pos.x, g->GetCollider()->pos.y + 65);
		}
	}
	for (LoopImageRect* g : wall) {
		if (g != NULL) {
			g->pos = Vector2(g->GetCollider()->pos.x, g->GetCollider()->pos.y);
		}
	}
	for (LoopImageRect* g : hill) {
		if (g != NULL) {
			g->pos = Vector2(g->GetCollider()->pos.x, g->GetCollider()->pos.y - 30);
		}
	}
}

void Running::ObjectUpdate()
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
	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			m->Update();
		}
	}
}

void Running::Update()
{
	//사망시 대기맵으로 이동
	if (player->GetHealth() <= 0) {
		program->CreateScene(4, 3);
		return;
	}
	//나가기 버튼 고정
	exit_button->GetCollider()->pos = CAM->GlobalPos()+Vector2(WIN_WIDTH-150, WIN_HEIGHT-50);
	mouse_object->pos = CAM->GlobalPos() + (mouse_pos);
	//체력바 고정
	hp_background->pos = CAM->GlobalPos() + Vector2(600, 60);
	hp_object->pos = CAM->GlobalPos() + Vector2(600, 60);
	hp_background->SetColor(0.2f, 0.2f, 0.2f, 1);
	hp_object->SetColor(1, 0.36f, 0.36f, 1);

	//체력바 세팅
	//체력바 길이
	hp_object->scale.x = (float)((player->GetHealth()*1.5) / 450.0f);
	//체력바 길이 줄어듬에 따라 위치 조정
	hp_object->pos.x = hp_object->pos.x - ((450 - (float)(player->GetHealth()*1.5)) / 2);

	
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
		player->IsHit(false , 50);
	}
	//러닝 종료로 인한 입장맵으로 이동
	if (player->pos.x > ground[53]->GetCollider()->pos.x + ground[53]->GetSize().x / 2-800) {
		program->CreateScene(4, 3);
		return;
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
				player->pos.y -= DELTA * 400.0f;
				player->landing();
			}
		}
	}
	for (LoopImageRect* g : wall) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetHitCollider()->isCollision(g->GetCollider(), &collision)) {
				player->IsHit(true,20);
			}
		}
	}
	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			Vector2 collision;
			if (player->GetHitCollider()->isCollision(m->GetHitCollider(), &collision)) {
				player->IsHit(true,20);
			}
		}
	}
	player->Update();


	
	ObjectUpdate();
	exit_button->Update();
	hp_background->WorldUpdate();
	hp_object->WorldUpdate();
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
	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			m->Render();
		}
	}
	exit_button->Render();
	mouse_object->Render();
	hp_background->Render();
	hp_object->Render();
	player->Render();
}

void Running::PostRender()
{
	player->PostRender();
}
