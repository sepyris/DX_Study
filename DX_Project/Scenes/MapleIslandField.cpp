#include "framework.h"

MapleIslandField::MapleIslandField(UINT area)
	:hill_ground(),
	monster_zen_count()
{
	bg = new BackGroundUV(L"Texture/Image/field.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(3, 3), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y));

	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite.png");
	mushroom[0] = new Mushroom(L"Texture/AnimateScene/Animation/mushroom.png");
	mushroom[1] = new Mushroom(L"Texture/AnimateScene/Animation/mushroom.png");
	mushroom[2] = new Mushroom(L"Texture/AnimateScene/Animation/mushroom.png");
	mushroom[3] = new Mushroom(L"Texture/AnimateScene/Animation/mushroom.png");
	mushroom[4] = new Mushroom(L"Texture/AnimateScene/Animation/mushroom.png");
	mushroom[5] = new Mushroom(L"Texture/AnimateScene/Animation/mushroom.png");
	mushroom[6] = new Mushroom(L"Texture/AnimateScene/Animation/mushroom.png");
	mushroom[7] = new Mushroom(L"Texture/AnimateScene/Animation/mushroom.png");
	
	snail[0] = new Snail(L"Texture/AnimateScene/Animation/snail.png");
	snail[1] = new Snail(L"Texture/AnimateScene/Animation/snail.png");
	snail[2] = new Snail(L"Texture/AnimateScene/Animation/snail.png");
	snail[3] = new Snail(L"Texture/AnimateScene/Animation/snail.png");
	snail[4] = new Snail(L"Texture/AnimateScene/Animation/snail.png");
	snail[5] = new Snail(L"Texture/AnimateScene/Animation/snail.png");
	snail[6] = new Snail(L"Texture/AnimateScene/Animation/snail.png");
	

	CAM->SetTarget(player);
	if (area == 1) {
		player->pos = Vector2(-880, 800);
		CAM->pos = Vector2(-1280, 600);
	}
	else if (area == 2) {
		player->pos = Vector2(510, 600);
		CAM->pos = Vector2(0, 700);
	}
	else if (area == 3) {
		player->pos = Vector2(2220, 900);
		CAM->pos = Vector2(1270, 800);
	}
	else {
		player->pos = Vector2(WIN_CENTER_X, WIN_CENTER_Y);
	}

	ground[0] = new RectCollider(Vector2(WIN_WIDTH*3, 3));
	ground[1] = new RectCollider(Vector2(390, 3));
	ground[2] = new RectCollider(Vector2(910, 3));
	ground[3] = new RectCollider(Vector2(1170, 3));
	ground[4] = new RectCollider(Vector2(390, 3));
	ground[5] = new RectCollider(Vector2(1170, 3));
	ground[6] = new RectCollider(Vector2(800, 3));
	ground[7] = new RectCollider(Vector2(390, 3));
	ground[8] = new RectCollider(Vector2(390, 3));
	ground[9] = new RectCollider(Vector2(1410, 3));
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

	monster_zone[0] = new RectCollider(Vector2(390, 30));
	monster_zone[1] = new RectCollider(Vector2(1410, 30));
	monster_zone[2] = new RectCollider(Vector2(910, 30));
	monster_zone[3] = new RectCollider(Vector2(800, 30));
	monster_zone[4] = new RectCollider(Vector2(1170, 30));
	monster_zone[0]->pos = Vector2(Vector2(-570, 560));
	monster_zone[1]->pos = Vector2(Vector2(-320, 190));
	monster_zone[2]->pos = Vector2(Vector2(935, 65));
	monster_zone[3]->pos = Vector2(Vector2(2160, 65));
	monster_zone[4]->pos = Vector2(Vector2(1580, 430));
	monster_zone_count[0] = 1;
	monster_zone_count[1] = 5;
	monster_zone_count[2] = 2;
	monster_zone_count[3] = 2;
	monster_zone_count[4] = 5;


	left_col[0] = new RectCollider(Vector2(30, 115));
	left_col[0]->pos = Vector2(Vector2(0, 1008));

	right_col[0] = new RectCollider(Vector2(30, 115));
	right_col[0]->pos = Vector2(Vector2(1140,1008));

	ladder[0] = new RectCollider(Vector2(30, 280));
	ladder[1] = new RectCollider(Vector2(30, 350));
	ladder[2] = new RectCollider(Vector2(30, 350));
	ladder[3] = new RectCollider(Vector2(30, 590));
	ladder[0]->pos = Vector2(Vector2(-560, 350));
	ladder[1]->pos = Vector2(Vector2(1110, 260));
	ladder[2]->pos = Vector2(Vector2(2010, 260));
	ladder[3]->pos = Vector2(Vector2(1530, 745));

	left_portal = new RectCollider(Vector2(120, 40));
	left_portal->pos = Vector2(Vector2(-880, 1040));

	center_portal = new RectCollider(Vector2(120, 40));
	center_portal->pos = Vector2(Vector2(530, 925));

	right_portal = new RectCollider(Vector2(120, 40));
	right_portal->pos = Vector2(Vector2(2220, 1040));

	

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
	for (RectCollider* z : monster_zone) {
		if (z != NULL) {
			z->WorldUpdate();
		}
	}


	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			m->Update();
		}
	}
	for (Snail* m : snail) {
		if (m != NULL) {
			m->Update();
		}
	}
	left_portal->WorldUpdate();
	center_portal->WorldUpdate();
	right_portal->WorldUpdate();
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
	for (RectCollider* z : monster_zone) {
		if (z != NULL) {
			delete z;
		}
	}
	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			delete m;
		}
	}
	for (Snail* m : snail) {
		if (m != NULL) {
			delete m;
		}
	}


	delete left_portal;
	delete center_portal;
	delete right_portal;
}

void MapleIslandField::Update()
{
	if (player->pos.y > WIN_HEIGHT * 3) {
		player->pos = Vector2(510, 700);
	}
	CAM->SetTarget(player);
	bg->Update();

	
	std::random_device rd;
	std::mt19937_64 gen(rd());
	for (int i = 0; i < monster_count; i++) {
		std::uniform_int_distribution<int> rand_count(0,2);
		std::uniform_int_distribution<int> rand_x((int)monster_zone[i]->LeftVX(), (int)monster_zone[i]->RightVX());
		std::uniform_int_distribution<int> rand_y((int)monster_zone[i]->TopVX(), (int)monster_zone[i]->TopVX());
		while (monster_zen_count[i] != monster_zone_count[i]) {
			if (rand_count(gen) > 1) {
				for (Snail* m : snail) {
					if (m != NULL) {
						if (!m->Islive()) {
							m->pos = Vector2((float)rand_x(gen), (float)(rand_y(gen) - 100));
							m->IsCreate();
							monster_zen_count[i]++;
							m->SetGroundNum(i);
							m->Setcollider(monster_zone[i]);
							break;
						}
					}
				}
			}
			else {
				for (Mushroom* m : mushroom) {
					if (m != NULL) {
						if (!m->Islive()) {
							m->pos = Vector2((float)rand_x(gen), (float)(rand_y(gen) - 100));
							m->IsCreate();
							monster_zen_count[i]++;
							m->SetGroundNum(i);
							m->Setcollider(monster_zone[i]);
							break;
						}
					}
				}
			}
		}
	}
	bool is_hit = false;

	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			Vector2 collision;
			if (player->GetAtkCollider() != NULL) {
				if (player->GetAtkCollider()->isCollision(m->GetHitCollider(), &collision)) {
					if (m->Islive()) {
						
						m->IsHit();
						is_hit = true;
						//맞으면 살짝 밀리도록 설정
						if (m->pos.x < player->pos.x) {
							m->pos.x -= 300.0f * DELTA;
						}
						else if (m->pos.x > player->pos.x) {
							m->pos.x += 300.0f * DELTA;
						}

						//밀려도 땅을 넘어가지 않도록 설정
						float min = monster_zone[m->GetGroundNum()]->LeftVX();
						float max = monster_zone[m->GetGroundNum()]->RightVX();
						if (m->pos.x > max) {
							m->pos.x -= 300.0f * DELTA;
						}
						if (m->pos.x < min) {
							m->pos.x += 300.0f * DELTA;
						}
					}
				}
			}
		}
	}
	for (Snail* m : snail) {
		if (m != NULL) {
			Vector2 collision;
			if (player->GetAtkCollider() != NULL) {
				if (player->GetAtkCollider()->isCollision(m->GetHitCollider(), &collision)) {
					if (m->Islive()) {
						m->IsHit();
						is_hit = true;

						//맞으면 살짝 밀리도록 설정
						if (m->pos.x < player->pos.x) {
							m->pos.x -= 300.0f * DELTA;
						}
						else if (m->pos.x > player->pos.x) {
							m->pos.x += 300.0f * DELTA;
						}

						//밀려도 땅을 넘어가지 않도록 설정
						float min = monster_zone[m->GetGroundNum()]->LeftVX();
						float max = monster_zone[m->GetGroundNum()]->RightVX();
						if (m->pos.x > max) {
							m->pos.x -= 300.0f * DELTA;
						}
						if (m->pos.x < min) {
							m->pos.x += 300.0f * DELTA;
						}
					}
				}	
			}
		}
	}
	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			Vector2 collision;
			if (player->GetHitCollider()->isCollision(m->GetHitCollider(), &collision)) {
				if (m->Islive()) {
					if (!player->IsHitting()) {
						if (m->pos.x < player->pos.x) {
							player->IsHit(true);
						}
						else if (m->pos.x > player->pos.x) {
							player->IsHit(false);
						}
					}
				}
			}
		}
	}
	for (Snail* m : snail) {
		if (m != NULL) {
			Vector2 collision;
			if (player->GetHitCollider()->isCollision(m->GetHitCollider(), &collision)) {
				if (m->Islive()) {
					if (!player->IsHitting()) {
						if (m->pos.x < player->pos.x) {
							player->IsHit(true);
						}
						else if (m->pos.x > player->pos.x) {
							player->IsHit(false);
						}
					}
				}
			}
		}
	}

	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			if (!m->Islive()) {
				monster_zen_count[m->GetGroundNum()]--;

			}
		}
	}
	for (Snail* m : snail) {
		if (m != NULL) {
			if (!m->Islive()) {
				monster_zen_count[m->GetGroundNum()]--;
			}
		}
	}

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
			for (Mushroom* m : mushroom) {
				if (m != NULL) {
					if (m->GetCollider()->isCollision(g, &collision)) {
						if (m->pos.y < g->pos.y) {
							if (m->GetCollider()->BottomVX() > g->TopVX() - 1.0f) {
								m->pos.y -= collision.y * DELTA * 20.0f;
								m->landing();
							}
						}
					}
				}
			}
			for (Snail* m : snail) {
				if (m != NULL) {
					if (m->GetCollider()->isCollision(g, &collision)) {
						if (m->pos.y < g->pos.y) {
							if (m->GetCollider()->BottomVX() > g->TopVX() - 1.0f) {
								m->pos.y -= collision.y * DELTA * 20.0f;
								m->landing();
							}
						}
					}
				}
			}

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
	if (right_portal != NULL) {
		if (player->GetCollider()->isCollision(right_portal)) {
			if (KEY_DOWN(VK_UP)) {
				program->CreateScene(4, 1);
				return;
			}
		}
	}

	player->Update();
	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			m->Update();
		}
	}
	for (Snail* m : snail) {
		if (m != NULL) {
			m->Update();
		}
	}
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
	for (RectCollider* z : monster_zone) {
		if (z != NULL) {
			z->WorldUpdate();
		}
	}

	left_portal->WorldUpdate();
	center_portal->WorldUpdate();
	right_portal->WorldUpdate();

	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			m->LoadingEnd();
		}
	}
	for (Snail* m : snail) {
		if (m != NULL) {
			m->LoadingEnd();
		}
	}
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
	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			m->Render();
		}
	}
	for (Snail* m : snail) {
		if (m != NULL) {
			m->Render();
		}
	}

	left_portal->Render();
	center_portal->Render();
	right_portal->Render();
	player->Render();
}

void MapleIslandField::PostRender()
{
	player->PostRender();
	for (Mushroom* m : mushroom) {
		if (m != NULL) {
			m->PostRender();
		}
	}
	for (Snail* m : snail) {
		if (m != NULL) {
			m->PostRender();
		}
	}
}
