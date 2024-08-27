#include "framework.h"

StarBridge::StarBridge()
{
	bg = new BackGroundUV(L"Texture/Image/starbridge.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_Y/2, WIN_CENTER_X), Vector2(0.5,1), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y));
	Vector2 test = Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite.png");
	player->SetStar();
	player->pos = Vector2(0, 0);
	CAM->pos = Vector2(-500, -500);
	player->Update();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			star[i][j] = new Star(L"Texture/AnimateScene/Animation/star.png");
		}
	}
}

StarBridge::~StarBridge()
{
}

void StarBridge::Update()
{
	CAM->SetTarget(player);
	bg->WorldUpdate();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			star[i][j]->WorldUpdate();
		}
	}

	player->Update();

	player->LoadingEnd();
}

void StarBridge::Render()
{
	bg->Render();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			star[i][j]->Render();
		}
	}
	player->Render();
}

void StarBridge::PostRender()
{
	Star* test = star[0][0];
	ImGui::SliderFloat2("star", (float*)&test->pos, 0, 30);
	player->PostRender();
}
