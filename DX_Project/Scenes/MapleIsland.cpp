#include "framework.h"

MapleIsland::MapleIsland(float area)
{
	bg = new BackGroundUV(L"Texture/Image/mapleisland.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_X, WIN_CENTER_Y),Vector2(3,3),0.0f,Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y));

	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite.png");
	CAM->SetTarget(player);
	if (area == 3) {
		player->pos = Vector2(2145, 850);
		CAM->pos = Vector2(1280, 500);
	}
	else {
		player->pos = Vector2(WIN_CENTER_X,WIN_CENTER_Y);
	}
	ground[0] = new RectCollider(Vector2(WIN_WIDTH*3, 3));
	ground[1] = new RectCollider(Vector2(150, 3));
	ground[2] = new RectCollider(Vector2(150, 3));
	ground[3] = new RectCollider(Vector2(1680, 3));
	ground[4] = new RectCollider(Vector2(150, 3));
	ground[5] = new RectCollider(Vector2(660, 3));
	ground[6] = new RectCollider(Vector2(600, 3));
	ground[7] = new RectCollider(Vector2(780, 3));
	ground[8] = new RectCollider(Vector2(510, 3));
	ground[9] = new RectCollider(Vector2(1800, 3));
	ground[0]->pos = Vector2(Vector2(WIN_CENTER_X, 1240));
	ground[1]->pos = Vector2(Vector2(665,1160));
	ground[2]->pos = Vector2(Vector2(815,1090));
	ground[3]->pos = Vector2(Vector2(1730,1020));
	ground[4]->pos = Vector2(Vector2(1245,1170));
	ground[5]->pos = Vector2(Vector2(1645,1095));
	ground[6]->pos = Vector2(Vector2(2275,1165));
	ground[7]->pos = Vector2(Vector2(-580,870));
	ground[8]->pos = Vector2(Vector2(-1012,725));
	ground[9]->pos = Vector2(Vector2(-390,650));

	//hill_ground[0] = new RectCollider(Vector2(770, 1));
	//hill_ground[0]->pos = Vector2(Vector2(850, 820));
	//hill_ground[0]->rot.z = 0.46f;

	left_col[0] = new RectCollider(Vector2(10, 75));
	left_col[1] = new RectCollider(Vector2(10, 75));
	left_col[2] = new RectCollider(Vector2(30, 75));
	left_col[3] = new RectCollider(Vector2(30, 75));
	left_col[0]->pos = Vector2(Vector2(745, 1135));
	left_col[1]->pos = Vector2(Vector2(895, 1062));
	left_col[2]->pos = Vector2(Vector2(1182, 1213));
	left_col[3]->pos = Vector2(Vector2(1325, 1137));

	right_col[0] = new RectCollider(Vector2(30, 75));
	right_col[0]->pos = Vector2(Vector2(1965, 1137));

	ladder[0] = new RectCollider(Vector2(60, 309));
	ladder[0]->pos = Vector2(Vector2(-530,1025));
	ladder[1] = new RectCollider(Vector2(60, 459));
	ladder[1]->pos = Vector2(Vector2(-1135,955));

	right_portal = new RectCollider(Vector2(120, 40));
	right_portal->pos = Vector2(Vector2(2145, 1000));

	player->Update();
	for (RectCollider* g : ground) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	for (RectCollider* g : left_col) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	for (RectCollider* g : right_col) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	for (RectCollider* g : hill_ground) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	for (RectCollider* g : ladder) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	right_portal->WorldUpdate();
	
}

MapleIsland::~MapleIsland()
{

	delete player;
	delete bg;
	for (RectCollider* g : ground) {
		if (g != NULL) {
			delete g;
		}
	}
	for (RectCollider* g : left_col) {
		if (g != NULL) {
			delete g;
		}
	}
	for (RectCollider* g : right_col) {
		if (g != NULL) {
			delete g;
		}
	}
	for (RectCollider* g : hill_ground) {
		if (g != NULL) {
			delete g;
		}
	}
	for (RectCollider* g : ladder) {
		if (g != NULL) {
			delete g;
		}
	}
	delete right_portal;
}

void MapleIsland::Update()
{
	if (player->pos.y > WIN_HEIGHT*3) {
		player->pos = Vector2(WIN_CENTER_X + 545, 500);
	}
	CAM->SetTarget(player);
	bg->Update();
	

	for (RectCollider* g : left_col) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetCollider()->isCollision(g, &collision)) {
				player->pos.x -= collision.x*DELTA * 50.0f;
			}
		}
	}
	for (RectCollider* g : right_col) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetCollider()->isCollision(g, &collision)) {
				player->pos.x += collision.x * DELTA * 50.0f;
			}
		}
	}

	for (RectCollider* g : ground) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetCollider()->isCollision(g, &collision)) {
				if (player->pos.y < g->pos.y) {
					if (player->GetCollider()->BottomVX() > g->TopVX() - 1.0f) {
						player->pos.y -= collision.y*DELTA*20.0f;
						player->landing();
					}
				}
			}
		}
	}
	
	for (RectCollider* g : hill_ground) {
		if (g != NULL) {
			if (player->GetCollider()->isCollision(g)) {
				player->pos.y -= DELTA * 100.0f;
				player->landing();
			}
		}
	}
	bool check_hanging = false;
	for (RectCollider* g : ladder) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetCollider()->isCollision(g, &collision)) {
				if (player->IsHanging()) {
					player->pos.x = g->GlobalPos().x;
					player->GetCollider()->pos.x = g->GlobalPos().x;
					check_hanging = true;
				}
			}
		}
	}
	if (!check_hanging) {
		player->SetIdle();
	}

	if (right_portal!= NULL) {
		if (player->GetCollider()->isCollision(right_portal)) {
			if (KEY_DOWN(VK_UP)) {
				program->CreateScene(2,1);
				return;
			}
		}
	}
	
	player->Update();
	for (RectCollider* g : ground) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	for (RectCollider* g : left_col) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	for (RectCollider* g : right_col) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	for (RectCollider* g : hill_ground) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	for (RectCollider* g : ladder) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	right_portal->WorldUpdate();
	player->LoadingEnd();
}

void MapleIsland::Render()
{
	bg->Render();
	for (RectCollider* g : ground) {
		if (g != NULL) {
			g->Render();
		}
	}
	for (RectCollider* g : left_col) {
		if (g != NULL) {
			g->Render();
		}
	}
	for (RectCollider* g : right_col) {
		if (g != NULL) {
			g->Render();
		}
	}
	for (RectCollider* g : hill_ground) {
		if (g != NULL) {
			g->Render();
		}
	}
	for (RectCollider* g : ladder) {
		if (g != NULL) {
			g->Render();
		}
	}
	right_portal->Render();
	player->Render();
}

void MapleIsland::PostRender()
{
	ImGui::SliderFloat2("p.pos", (float*)&player->pos, 0, WIN_WIDTH);
	player->PostRender();
}
