#include "framework.h"

StarBridgeWaitting::StarBridgeWaitting(float area)
{
	bg = new BackGroundUV(L"Texture/Image/starbridgewait.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(3, 3), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y));

	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite2.png");
	CAM->SetTarget(player);
	if (area == 2) {
		player->pos = Vector2(WIN_CENTER_X-180, 1000);
		CAM->pos = Vector2(-200, 600);
	}
	else {
		player->pos = Vector2(WIN_CENTER_X, WIN_CENTER_Y);
	}


	ground[0] = new RectCollider(Vector2(WIN_WIDTH*3, 3));
	ground[0]->pos = Vector2(Vector2(WIN_CENTER_X, 1175));


	center_portal = new RectCollider(Vector2(180, 60));
	center_portal->pos = Vector2(Vector2(WIN_CENTER_X-180, 1150));

	player->Update();
	for (RectCollider* g : ground) {
		if (g != NULL) {
			g->WorldUpdate();
		}
	}
	center_portal->WorldUpdate();
}

StarBridgeWaitting::~StarBridgeWaitting()
{

	delete player;
	delete bg;
	for (RectCollider* g : ground) {
		if (g != NULL) {
			delete g;
		}
	}
	delete center_portal;
}

void StarBridgeWaitting::Update()
{
	if (player->pos.y > WIN_HEIGHT * 3) {
		player->pos = Vector2(WIN_CENTER_X + 545, 500);
	}
	CAM->SetTarget(player);
	bg->Update();

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

	if (center_portal != NULL) {
		if (player->GetCollider()->isCollision(center_portal)) {
			if (KEY_DOWN(VK_UP)) {
				program->CreateScene(2, 2);
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
	center_portal->WorldUpdate();
}

void StarBridgeWaitting::Render()
{
	bg->Render();
	for (RectCollider* g : ground) {
		if (g != NULL) {
			g->Render();
		}
	}
	center_portal->Render();
	player->Render();
}

void StarBridgeWaitting::PostRender()
{
	ImGui::SliderFloat2("p.pos", (float*)&player->pos, 0, WIN_WIDTH);

}