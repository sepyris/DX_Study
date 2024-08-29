#include "framework.h"

StarBridge::StarBridge()
{
	bg = new BackGroundUV(L"Texture/Image/starbridge.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_Y, WIN_CENTER_X), Vector2(3,3), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y));
	Vector2 test = Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite.png");
	player->SetStar();
	player->pos = Vector2(0, 0);
	CAM->pos = Vector2(-360, -640);
	player->Update();

	float init_x_pos = -540;
	float init_y_pos = -1000;
	float x_pos = 0;
	float y_pos = 0;
	for (int i = 0; i < 10; i++) {
		x_pos = init_x_pos + (i * 200);
		for (int j = 0; j < 12; j++) {
			y_pos = init_y_pos + (j * 300);
			star[i][j] = new Star(L"Texture/AnimateScene/Animation/star.png");
			star[i][j]->pos = Vector2(x_pos, y_pos);
		}
	}
	for (int i = 0; i < 20; i++) {
		star_line[i] = new StarLine(L"Texture/Image/starline.png");
		star_line[i]->GetCollider()->scale.y = 0.5f;
	}
	

}

StarBridge::~StarBridge()
{
}

void StarBridge::Update()
{
	CAM->SetTarget(player);
	bg->WorldUpdate();
	//
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			Star* tmp = star[i][j];
			if (tmp != NULL) {
				Vector2 collision;
				if (player->GetHitCollider()->isCollision(tmp->GetCollider(), &collision)) {
					tmp->SetActive();
				}
				if (tmp->IsActive()) {
					star_line[0]->GetCollider()->pos = (player->pos + tmp->pos) / 2;
					star_line[0]->GetCollider()->rot.z = (tmp->pos - player->pos).Normalized().Angle();
					star_line[0]->SetSize((tmp->pos - player->pos).GetLength());
					star_line[0]->Update();
					star_line[0]->GetCollider()->WorldUpdate();
					
					//star_line[0]->SetLine();
				}
			}
		}
	}
	

	//
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			star[i][j]->Update();
		}
	}
	player->Update();

	player->LoadingEnd();
}

void StarBridge::Render()
{
	bg->Render();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			Star* tmp = star[i][j];
			if (tmp != NULL) {
				if (tmp->IsActive()) {
					star_line[0]->Render();
					star_line[0]->GetCollider()->Render();
					/*
					if (star_line != NULL) {
						
					}
					*/
				}
				tmp->Render();
				
			}			
		}
	}
	player->Render();
}

void StarBridge::PostRender()
{
	ImGui::SliderFloat2("star_line.pos", (float*)&star_line[0]->pos, -3000, 3000);
	ImGui::SliderFloat2("star_line.scale", (float*)&star_line[0]->scale, -3000, 3000);
	player->PostRender();
}
