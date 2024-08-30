#include "framework.h"

StarBridge::StarBridge()
{
	bg = new BackGroundUV(L"Texture/Image/starbridge.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_Y, WIN_CENTER_X), Vector2(3,3), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y+200));
	Vector2 test = Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite.png");
	player->SetStar();
	player->pos = Vector2(880, 700);
	CAM->pos = Vector2(-400, -20);
	player->Update();

	float init_x_pos = -540;
	float init_y_pos = -1000;
	float x_pos = 0;
	float y_pos = 0;
	for (int i = 0; i < 10; i++) {
		x_pos = init_x_pos + (i * 310);
		for (int j = 0; j < 12; j++) {
			y_pos = init_y_pos + (j * 310);
			star[i][j] = new Star(L"Texture/AnimateScene/Animation/star.png");
			star[i][j]->pos = Vector2(x_pos, y_pos);
		}
	}
	for (int i = 0; i < 20; i++) {
		star_line[i] = new StarLine(L"Texture/Image/starline.png");
		star_line[i]->GetCollider()->scale.y = 0.5f;
	}
	CreateStage();

}

StarBridge::~StarBridge()
{
}

void StarBridge::CreateStage()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> rand_x(0,10);
	std::uniform_int_distribution<int> rand_y(0,12);
	std::uniform_int_distribution<int> rand_x_area(-5, 5);
	std::uniform_int_distribution<int> rand_y_area(-5, 5);

	for (int stage_num = 0; stage_num < 10; stage_num++) {
		for (int i = 0; i < 10; i++) {
			int star1_x = rand_x(gen);
			int star1_y = rand_y(gen);
			int star2_x = star1_x + rand_x_area(gen);
			int star2_y = star1_y + rand_y_area(gen);
			int over = 0;
			if (star2_x > 10) {
				over = star2_x - 10;
				star2_x = over;
			}
			if (star2_y > 12) {
				over = star2_y - 12;
				star2_y = over;
			}
			if (star2_x < 0) {
				over = star2_x + 9;
				star2_x = over;
			}
			if (star2_y < 0) {
				over = star2_y + 11;
				star2_y = over;
			}

			if (i == 0) {
				stage[stage_num][i].star1 = Vector2(star1_x, star1_y);
				stage[stage_num][i].star2 = Vector2(star2_x, star2_y);
			}
			else {
				star2_x = stage[stage_num][i - 1].star2.x + rand_x_area(gen);
				star2_y = stage[stage_num][i - 1].star2.y + rand_y_area(gen);
				over = 0;
				if (star2_x > 10) {
					over = star2_x - 10;
					star2_x = over;
				}
				if (star2_y > 12) {
					over = star2_y - 12;
					star2_y = over;
				}
				if (star2_x < 0) {
					over = star2_x + 9;
					star2_x = over;
				}
				if (star2_y < 0) {
					over = star2_y + 11;
					star2_y = over;
				}

				stage[stage_num][i].star1 = stage[stage_num][i-1].star2;
				stage[stage_num][i].star2 = Vector2(star2_x, star2_y);
			}
		}
	}
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
	for (int i = 0; i < 10; i++) {
		ImGui::SliderFloat2("stage[0].star1", (float*)&stage[0][i].star1, -3000, 3000);
		ImGui::SliderFloat2("stage[0].star2", (float*)&stage[0][i].star2, -3000, 3000);
	}
	
	player->PostRender();
}
