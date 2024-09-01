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
	//exit_button = new RectCollider(Vector2(200, 100));
	

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
		stage_star_line[i] = new StarLine(L"Texture/Image/stagestarline.png");
		stage_star_line[i]->GetCollider()->scale.y = 0.3f;
		star_line[i] = new StarLine(L"Texture/Image/starline.png");
		star_line[i]->GetCollider()->scale.y = 0.3f;
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
	std::uniform_int_distribution<int> rand_x(4, 6);
	std::uniform_int_distribution<int> rand_y(4, 6);
	std::uniform_int_distribution<int> rand_x_area(-4, 2);
	std::uniform_int_distribution<int> rand_y_area(-4, 2);

	for (int i = 0; i < 10; i++) {
		int star1_x = rand_x(gen);
		int star1_y = rand_y(gen);
		int star2_x = star1_x + rand_x_area(gen);
		int star2_y = star1_y + rand_y_area(gen);
		int over = 0;
		if (star2_x >= 9) {
			over = star2_x - 9;
			star2_x = over;
		}
		if (star2_y >= 11) {
			over = star2_y - 11;
			star2_y = over;
		}
		if (star2_x < 0) {
			over = star2_x * -1;
			star2_x = over;
		}
		if (star2_y < 0) {
			over = star2_y * -1;
			star2_y = over;
		}
		if (i == 0) {
			stage_star[i].star1 = Vector2(star1_x, star1_y);
			stage_star[i].star2 = Vector2(star2_x, star2_y);
		}
		else {
			star2_x = stage_star[i - 1].star2.x + rand_x_area(gen);
			star2_y = stage_star[i - 1].star2.y + rand_y_area(gen);
			over = 0;
			if (star2_x >= 9) {
				over = star2_x - 10;
				star2_x = over;
			}
			if (star2_y >= 11) {
				over = star2_y - 12;
				star2_y = over;
			}
			if (star2_x < 0) {
				over = star2_x * -1;
				star2_x = over;
			}
			if (star2_y < 0) {
				over = star2_y * -1;
				star2_y = over;
			}
			stage_star[i].star1 = stage_star[i - 1].star2;
			stage_star[i].star2 = Vector2(star2_x, star2_y);
		}
		/*
		int x_pos = stage_star[i].star1.x;
		int y_pos = stage_star[i].star1.y;
		Star* tmp = star[x_pos][y_pos];
		tmp->SetComp();
		*/
		stage_star_line[i]->SetStarOne(stage_star[i].star1);
		stage_star_line[i]->SetStarTwo(stage_star[i].star2);
	}
}

void StarBridge::ResetStage()
{
	for (int i = 0; i < 10; i++) {
		star_line[i]->ResetLine();
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			Star* tmp = star[i][j];
			if (tmp != NULL) {
				tmp->SetNone();
			}
		}
	}
	CreateStage();
}

void StarBridge::Update()
{
	/*
	exit_button->pos = player->pos + Vector2(800, 620);
	if (exit_button->pos.x > SCREEN_SIZE_X+200) {
		exit_button->pos.x = SCREEN_SIZE_X+200;
	}
	if (exit_button->pos.y > SCREEN_SIZE_Y*2 - 100) {
		exit_button->pos.y = SCREEN_SIZE_Y*2 - 100;
	}
	*/
	CAM->SetTarget(player);
	bg->WorldUpdate();
	
	
	//라인을 먼저 생성
	StarLine* check_line = NULL;
	for (int i = 0; i < 10; i++) {
		if (star_line[i]->GetLineStatus() != StarLine::LINE_STATUS::COMP) {
			check_line = star_line[i];
			break;
		}
	}
	if (check_line == NULL) {
		ResetStage();
		return;
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			Star* tmp = star[i][j];
			if (tmp != NULL) {
				Vector2 collision;
				if (player->GetHitCollider()->isCollision(tmp->GetCollider(), &collision)) {
					//키를 눌렀을때활성화 상태로 변경
					if (!player->IsStarFail()) {
						if (KEY_DOWN(VK_SPACE)) {
							//별 하나도 활성화 된 상태가 아닐시
							if (check_line != NULL) {
								if (check_line->GetLineStatus() == StarLine::LINE_STATUS::NONE && active_star_count == 0) {
									tmp->SetActive();
									check_line->SetStarOne(Vector2(i, j));
									check_line->SetLine();
									active_star_count++;
								}
								//별 하나가 활성화 된상태,활성화된 별과 다른 별 일때
								if (check_line->GetLineStatus() == StarLine::LINE_STATUS::SETTING && !(check_line->GetStarOne().x == i && check_line->GetStarOne().y == j) && active_star_count == 1) {
									//tmp->SetActive();
									check_line->SetStarTwo(Vector2(i, j));
									active_star_count++;
								}
							}
						}
					}
				}
			}
		}
	}
	if (active_star_count == 2) {
		bool comp_line = false;
		if (check_line != NULL) {
			for (int i = 0; i < 10; i++) {
				if (star_line[i]->GetLineStatus() == StarLine::LINE_STATUS::COMP) {
					if (check_line->CheckLineComp(star_line[i]->GetStarOne(), star_line[i]->GetStarTwo())) {
						int check_star1_x = check_line->GetStarOne().x;
						int check_star1_y = check_line->GetStarOne().y;
						int check_star2_x = check_line->GetStarTwo().x;
						int check_star2_y = check_line->GetStarTwo().y;
						star[check_star1_x][check_star1_y]->ResetStatus();
						star[check_star2_x][check_star2_y]->ResetStatus();
						check_line->ResetLine();
						player->StarFail();
						break;
					}
				}
			}

			for (int i = 0; i < 10; i++) {
				int star1_x = stage_star_line[i]->GetStarOne().x;
				int star1_y = stage_star_line[i]->GetStarOne().y;
				int star2_x = stage_star_line[i]->GetStarTwo().x;
				int star2_y = stage_star_line[i]->GetStarTwo().y;
				if (check_line->CheckLineComp(Vector2(star1_x, star1_y), Vector2(star2_x, star2_y))) {
					star[star1_x][star1_y]->SetComp();
					star[star2_x][star2_y]->SetComp();
					comp_line = true;
					break;
				}
			}
		}
		if (!comp_line) {
			int check_star1_x = check_line->GetStarOne().x;
			int check_star1_y = check_line->GetStarOne().y;
			int check_star2_x = check_line->GetStarTwo().x;
			int check_star2_y = check_line->GetStarTwo().y;
			star[check_star1_x][check_star1_y]->ResetStatus();
			star[check_star2_x][check_star2_y]->ResetStatus();
			check_line->ResetLine();
			player->StarFail();
		}
		active_star_count = 0;
	}




	for (int i = 0; i < 10; i++) {
		//스테이지 라인 생성
		int star1_x = stage_star_line[i]->GetStarOne().x;
		int star1_y = stage_star_line[i]->GetStarOne().y;
		Vector2 star1_pos = star[star1_x][star1_y]->pos;

		int star2_x = stage_star_line[i]->GetStarTwo().x;
		int star2_y = stage_star_line[i]->GetStarTwo().y;
		Vector2 star2_pos = star[star2_x][star2_y]->pos;

		stage_star_line[i]->GetCollider()->pos = (star1_pos + star2_pos) / 2;
		stage_star_line[i]->GetCollider()->rot.z = (star1_pos - star2_pos).Normalized().Angle();
		stage_star_line[i]->SetSize((star1_pos - star2_pos).GetLength());
		stage_star_line[i]->Update();
		stage_star_line[i]->GetCollider()->WorldUpdate();

		//현재 라인 상태 표시
		//눌렀을때
		if (star_line[i]->GetLineStatus() == StarLine::LINE_STATUS::SETTING) {
			int star1_x = star_line[i]->GetStarOne().x;
			int star1_y = star_line[i]->GetStarOne().y;
			Vector2 star1_pos = star[star1_x][star1_y]->pos;
			star_line[i]->GetCollider()->pos = (star1_pos + player->pos) / 2;
			star_line[i]->GetCollider()->rot.z = (star1_pos - player->pos).Normalized().Angle();
			star_line[i]->SetSize((star1_pos - player->pos).GetLength());
			star_line[i]->Update();
			star_line[i]->GetCollider()->WorldUpdate();
		}
		//완료 됬을때
		if (star_line[i]->GetLineStatus() == StarLine::LINE_STATUS::COMP) {
			int star1_x = star_line[i]->GetStarOne().x;
			int star1_y = star_line[i]->GetStarOne().y;
			Vector2 star1_pos = star[star1_x][star1_y]->pos;
			int star2_x = stage_star_line[i]->GetStarTwo().x;
			int star2_y = stage_star_line[i]->GetStarTwo().y;
			Vector2 star2_pos = star[star2_x][star2_y]->pos;

			star_line[i]->GetCollider()->pos = (star1_pos + star2_pos) / 2;
			star_line[i]->GetCollider()->rot.z = (star1_pos - star2_pos).Normalized().Angle();
			star_line[i]->SetSize((star1_pos - star2_pos).GetLength());
			star_line[i]->Update();
			star_line[i]->GetCollider()->WorldUpdate();
		}
	}

	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			star[i][j]->Update();
		}
	}
	

	player->Update();
	//exit_button->WorldUpdate();
	player->LoadingEnd();
}

void StarBridge::Render()
{
	bg->Render();
	for (int i = 0; i < 10; i++) {
		//미니맵생성전까지 렌더링
		stage_star_line[i]->Render();
		stage_star_line[i]->GetCollider()->Render();

		//라인이 표시되면 렌더링
		if (star_line[i]->GetLineStatus() != StarLine::LINE_STATUS::NONE) {
			star_line[i]->Render();
			star_line[i]->GetCollider()->Render();
		}
		
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			Star* tmp = star[i][j];
			if (tmp != NULL) {
				tmp->Render();
			}			
		}
	}
	player->Render();

	//exit_button->Render();
}

void StarBridge::PostRender()
{
	for (int i = 0; i < 10; i++) {
		ImGui::SliderFloat2("stage[0].star1", (float*)&stage_star[i].star1, -3000, 3000);
		ImGui::SliderFloat2("stage[0].star2", (float*)&stage_star[i].star2, -3000, 3000);
	}
	
	player->PostRender();
}
