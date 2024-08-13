#include "framework.h"

MapleIslandField::MapleIslandField(UINT area)
{
	bg = new BackGroundUV(L"Texture/Image/field.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(3, 3), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y));

	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite2.png");
	CAM->SetTarget(player);
	if (area == 1) {
		player->pos = Vector2(-880, 900);
		CAM->pos = Vector2(-1280, 600);
	}
	else if (area == 2) {
		player->pos = Vector2(510, 800);
		CAM->pos = Vector2(510, 800);
	}
	else if (area == 3) {
		player->pos = Vector2(WIN_CENTER_X + 545, 500);
	}
	else {
		player->pos = Vector2(WIN_CENTER_X, WIN_CENTER_Y);
	}
	

	ground[0] = new RectCollider(Vector2(WIN_WIDTH*3, 1));
	ground[1] = new RectCollider(Vector2(390, 1));
	ground[2] = new RectCollider(Vector2(910, 1));
	ground[3] = new RectCollider(Vector2(1170, 1));
	ground[4] = new RectCollider(Vector2(390, 1));
	ground[5] = new RectCollider(Vector2(1170, 1));
	ground[6] = new RectCollider(Vector2(800, 1));
	ground[7] = new RectCollider(Vector2(390, 1));
	ground[8] = new RectCollider(Vector2(390, 1));
	ground[9] = new RectCollider(Vector2(1410, 1));
	ground[0]->pos = Vector2(Vector2(WIN_CENTER_X, 1060));
	ground[1]->pos = Vector2(Vector2(-325, 820));
	ground[2]->pos = Vector2(Vector2(935, 85));
	ground[3]->pos = Vector2(Vector2(570, 945));
	ground[4]->pos = Vector2(Vector2(1190, 820));
	ground[5]->pos = Vector2(Vector2(1580, 450));
	ground[6]->pos = Vector2(Vector2(2160, 85));
	ground[7]->pos = Vector2(Vector2(-570, 580));
	ground[8]->pos = Vector2(Vector2(-570, 700));
	ground[9]->pos = Vector2(Vector2(-320, 210));

	left_col[0] = new RectCollider(Vector2(3, 115));
	left_col[0]->pos = Vector2(Vector2(-10, 1003));

	right_col[0] = new RectCollider(Vector2(3, 115));
	right_col[0]->pos = Vector2(Vector2(1150,1003));

	ladder[0] = new RectCollider(Vector2(30, 280));
	ladder[1] = new RectCollider(Vector2(30, 350));
	ladder[2] = new RectCollider(Vector2(30, 350));
	ladder[3] = new RectCollider(Vector2(30, 590));
	ladder[0]->pos = Vector2(Vector2(-560, 340));
	ladder[1]->pos = Vector2(Vector2(1110, 250));
	ladder[2]->pos = Vector2(Vector2(2010, 250));
	ladder[3]->pos = Vector2(Vector2(1530, 740));

	left_portal = new RectCollider(Vector2(120, 40));
	left_portal->pos = Vector2(Vector2(-880, 1040));

	center_portal = new RectCollider(Vector2(120, 40));
	center_portal->pos = Vector2(Vector2(530, 925));

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
	left_portal->WorldUpdate();
	center_portal->WorldUpdate();
	//CAM->Update();

}

MapleIslandField::~MapleIslandField()
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
	delete left_portal;
	delete center_portal;
}

void MapleIslandField::Update()
{
	if (player->pos.y > WIN_HEIGHT * 3) {
		player->pos = Vector2(510, 700);
	}
	CAM->SetTarget(player);
	bg->Update();


	for (RectCollider* g : left_col) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetCollider()->isCollision(g, &collision)) {
				if (collision.x <= collision.y) {
					if (player->pos.x < g->pos.x) {
						player->pos.x -= collision.x * DELTA * 100.0f;
					}
				}
			}
		}
	}
	for (RectCollider* g : right_col) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetCollider()->isCollision(g, &collision)) {
				if (collision.x <= collision.y) {
					if (player->pos.x > g->pos.x) {
						player->pos.x += collision.x * DELTA * 100.0f;
					}
				}
			}
		}
	}

	for (RectCollider* g : ground) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetCollider()->isCollision(g, &collision)) {
				if (player->pos.y < g->pos.y) {
					if (player->GetCollider()->BottomVX() > g->TopVX() - 1.0f) {
						player->pos.y -= collision.y * DELTA * 20.0f;
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
					check_hanging = true;
				}
			}
		}
	}
	if (!check_hanging) {
		player->SetIdle();
	}

	if (left_portal != NULL) {
		if (player->GetCollider()->isCollision(left_portal)) {
			if (KEY_DOWN(VK_UP)) {
				program->CreateScene(1, 3);
				return;
			}
		}
	}
	if (center_portal != NULL) {
		if (player->GetCollider()->isCollision(center_portal)) {
			if (KEY_DOWN(VK_UP)) {
				program->CreateScene(3, 2);
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
	left_portal->WorldUpdate();
	center_portal->WorldUpdate();
}

void MapleIslandField::Render()
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
	left_portal->Render();
	center_portal->Render();
	player->Render();
}

void MapleIslandField::PostRender()
{
	ImGui::SliderFloat2("p.pos", (float*)&player->pos, 0, WIN_WIDTH);
	UINT count = 0;
	for (RectCollider* g : ladder) {
		if (g != NULL) {
			ImGui::SliderFloat2(to_string(count).c_str(), (float*)&g->pos, -WIN_WIDTH*3, WIN_WIDTH*3);
			count++;
		}
	}
	player->PostRender();
}
