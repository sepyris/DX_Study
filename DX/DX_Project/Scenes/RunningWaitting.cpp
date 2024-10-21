#include "framework.h"

RunningWaitting::RunningWaitting(UINT area)
{
	bg = new BackGroundUV(L"Texture/Image/RunningWait.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(3, 3), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y));
	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite.png");
	CAM->SetTarget(player);
	if (area == 1) {
		player->pos = Vector2(-1190, 800);
		CAM->pos = Vector2(-1270, 500);
	}
	else if (area == 3) {
		player->pos = Vector2(2440, 600);
		CAM->pos = Vector2(1270, 330);
	}
	else {
		player->pos = Vector2(WIN_CENTER_X, WIN_CENTER_Y);
	}
	ground[0] = new RectCollider(Vector2(WIN_WIDTH * 3, 3));
	ground[1] = new RectCollider(Vector2(755, 3));
	ground[2] = new RectCollider(Vector2(120, 3));
	ground[3] = new RectCollider(Vector2(440, 3));
	ground[4] = new RectCollider(Vector2(110, 3));
	ground[5] = new RectCollider(Vector2(405, 3));
	ground[6] = new RectCollider(Vector2(110, 3));
	ground[7] = new RectCollider(Vector2(110, 3));
	ground[8] = new RectCollider(Vector2(595, 3));
	ground[9] = new RectCollider(Vector2(80, 3));
	ground[10] = new RectCollider(Vector2(80, 3));
	ground[11] = new RectCollider(Vector2(80, 3));
	ground[12] = new RectCollider(Vector2(80, 3));
	ground[13] = new RectCollider(Vector2(80, 3));
	ground[14] = new RectCollider(Vector2(80, 3));
	ground[15] = new RectCollider(Vector2(975, 3));

	ground[0]->pos = Vector2(Vector2(WIN_CENTER_X, 1245));
	ground[1]->pos = Vector2(Vector2(-890, 1030));
	ground[2]->pos = Vector2(Vector2(-417, 1030));
	ground[3]->pos = Vector2(Vector2(-245, 645));
	ground[4]->pos = Vector2(Vector2(455, 645));
	ground[5]->pos = Vector2(Vector2(165, 590));
	ground[6]->pos = Vector2(Vector2(525, 730));
	ground[7]->pos = Vector2(Vector2(605, 810));
	ground[8]->pos = Vector2(Vector2(870, 1138));
	ground[9]->pos = Vector2(Vector2(1175, 1082));
	ground[10]->pos = Vector2(Vector2(1250, 1027));
	ground[11]->pos = Vector2(Vector2(1325, 972));
	ground[12]->pos = Vector2(Vector2(1400, 917));
	ground[13]->pos = Vector2(Vector2(1470, 862));
	ground[14]->pos = Vector2(Vector2(1540, 807));
	ground[15]->pos = Vector2(Vector2(2056, 752));

	hill_ground[0] = new RectCollider(Vector2(200, 3));
	hill_ground[0]->pos = Vector2(Vector2(490, 1200));
	hill_ground[0]->rot.z = -0.65f;
	
	left_col[0] = new RectCollider(Vector2(30, 55));
	left_col[1] = new RectCollider(Vector2(30, 55));
	left_col[2] = new RectCollider(Vector2(30, 55));
	left_col[3] = new RectCollider(Vector2(30, 55));
	left_col[4] = new RectCollider(Vector2(30, 55));
	left_col[5] = new RectCollider(Vector2(30, 55));
	left_col[6] = new RectCollider(Vector2(30, 55));
	left_col[7] = new RectCollider(Vector2(30, 55));
	left_col[0]->pos = Vector2(Vector2(-20, 622));
	left_col[1]->pos = Vector2(Vector2(1150, 1115));
	left_col[2]->pos = Vector2(Vector2(1225, 1060));
	left_col[3]->pos = Vector2(Vector2(1300, 1005));
	left_col[4]->pos = Vector2(Vector2(1370, 950));
	left_col[5]->pos = Vector2(Vector2(1440, 895));
	left_col[6]->pos = Vector2(Vector2(1515, 840));
	left_col[7]->pos = Vector2(Vector2(1585, 785));

	right_col[0] = new RectCollider(Vector2(30, 220));
	right_col[0]->pos = Vector2(Vector2(-520, 1145));

	ladder[0] = new RectCollider(Vector2(40, 340));
	ladder[1] = new RectCollider(Vector2(15, 180));
	ladder[2] = new RectCollider(Vector2(15, 200));
	ladder[3] = new RectCollider(Vector2(40, 310));
	ladder[0]->pos = Vector2(Vector2(-415, 815));
	ladder[1]->pos = Vector2(Vector2(-385, 1120));
	ladder[2]->pos = Vector2(Vector2(-450, 1130));
	ladder[3]->pos = Vector2(Vector2(593, 965));

	left_portal = new RectCollider(Vector2(60, 20));
	left_portal->pos = Vector2(Vector2(-1190, 1020));

	right_portal = new RectCollider(Vector2(60, 20));
	right_portal->pos = Vector2(Vector2(2440, 750));

	info = new ImageRect(L"Texture/Image/run_info.png", Vector2(0, 0), Vector2(1, 1), 0.0f, Vector2(350, 260));
	info->pos = Vector2(Vector2(2056, 500));
	info->GetCollider()->pos = Vector2(Vector2(2056, 500));

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
	right_portal->WorldUpdate();

}

RunningWaitting::~RunningWaitting()
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
	delete right_portal;
}

void RunningWaitting::Update()
{
	if (player->pos.y > WIN_HEIGHT * 3) {
		player->pos = Vector2(WIN_CENTER_X + 545, 500);
	}
	CAM->SetTarget(player);
	bg->Update();

	for (RectCollider* g : left_col) {
		if (g != NULL) {
			Vector2 collision;
			if (player->GetCollider()->isCollision(g, &collision)) {
				player->pos.x -= collision.x * DELTA * 50.0f;
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
				player->pos.y -= DELTA * 300.0f;
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
				program->CreateScene(2, 3);
				return;
			}
		}
	}
	if (right_portal != NULL) {
		if (player->GetCollider()->isCollision(right_portal)) {
			if (KEY_DOWN(VK_UP)) {
				program->CreateScene(6, 1);
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
	info->Update();
	left_portal->WorldUpdate();
	right_portal->WorldUpdate();
}

void RunningWaitting::Render()
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
	info->Render();
	left_portal->Render();
	right_portal->Render();
	player->Render();
}

void RunningWaitting::PostRender()
{
	ImGui::SliderFloat2("p.pos", (float*)&player->pos, 0, WIN_WIDTH);
	player->PostRender();
}
