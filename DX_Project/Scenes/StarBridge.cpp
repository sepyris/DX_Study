#include "framework.h"

StarBridge::StarBridge()
{
	bg = new BackGroundUV(L"Texture/Image/starbridge.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_Y, WIN_CENTER_X), Vector2(3,3), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y+200));
	mini_map = new MiniMap(L"Texture/Image/minimap.png");
	Vector2 test = Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite.png");
	player->SetStar();
	player->pos = Vector2(880, 700);
	CAM->pos = Vector2(-400, -20);
	player->Update();
	exit_button = new ImageRect(L"Texture/Image/exit_button.png",Vector2(0, 0),Vector2(1,1),0.0f,Vector2(200,100));
	mouse_object = new RectCollider(Vector2(10, 10));

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
	InitStage();
	CreateStage();

}

StarBridge::~StarBridge()
{
}

void StarBridge::InitStage()
{
	int stage = 0;
	stage_star_fix[stage][0].SetStar(1,0,2,2);
	stage_star_fix[stage][1].SetStar(2,2,5,2);
	stage_star_fix[stage][2].SetStar(5,2,4,4);
	stage_star_fix[stage][3].SetStar(2,2,4,4);
	stage_star_fix[stage][4].SetStar(4,4,2,8);
	stage_star_fix[stage][5].SetStar(2,8,3,10);
	stage_star_fix[stage][6].SetStar(3,10,5,9);
	stage_star_fix[stage][7].SetStar(5,9,6,7);
	stage_star_fix[stage][8].SetStar(6,7,8,8);
	stage_star_fix[stage][9].SetStar(8,8,7,10);
	stage_star_fix[stage][10].SetStar(7,10,5,9);
	stage_star_fix[stage][11].SetStar(99,99,99,99);

	stage++;
	stage_star_fix[stage][0].SetStar(2,2,3,4);
	stage_star_fix[stage][1].SetStar(3,4,1,4);
	stage_star_fix[stage][2].SetStar(1,4,2,2);
	stage_star_fix[stage][3].SetStar(3,4,2,6);
	stage_star_fix[stage][4].SetStar(2,6,7,6);
	stage_star_fix[stage][5].SetStar(7,6,8,4);
	stage_star_fix[stage][6].SetStar(7,6,6,8);
	stage_star_fix[stage][7].SetStar(6,8,7,11);
	stage_star_fix[stage][8].SetStar(6,8,3,8);
	stage_star_fix[stage][9].SetStar(3,8,2,6);
	stage_star_fix[stage][10].SetStar(3,8,2,11);
	stage_star_fix[stage][11].SetStar(99, 99, 99, 99);

	stage++;
	stage_star_fix[stage][0].SetStar(3,3,2,5);
	stage_star_fix[stage][1].SetStar(2,5,3,7);
	stage_star_fix[stage][2].SetStar(3,7,1,11);
	stage_star_fix[stage][3].SetStar(3,7,4,5);
	stage_star_fix[stage][4].SetStar(4,5,6,4);
	stage_star_fix[stage][5].SetStar(6,4,8,4);
	stage_star_fix[stage][6].SetStar(8,4,6,5);
	stage_star_fix[stage][7].SetStar(6,5,5,7);
	stage_star_fix[stage][8].SetStar(5,7,4,5);
	stage_star_fix[stage][9].SetStar(5,7,7,8);
	stage_star_fix[stage][10].SetStar(7,8,8,10);
	stage_star_fix[stage][11].SetStar(99, 99, 99, 99);

	stage++;
	stage_star_fix[stage][0].SetStar(9,1,7,0);
	stage_star_fix[stage][1].SetStar(7,0,6,2);
	stage_star_fix[stage][2].SetStar(6,2,7,4);
	stage_star_fix[stage][3].SetStar(7,4,8,6);
	stage_star_fix[stage][4].SetStar(8,6,3,7);
	stage_star_fix[stage][5].SetStar(3,7,1,8);
	stage_star_fix[stage][6].SetStar(1,8,2,6);
	stage_star_fix[stage][7].SetStar(2,6,7,4);
	stage_star_fix[stage][8].SetStar(99, 99, 99, 99);

	stage++;
	stage_star_fix[stage][0].SetStar(0,7,2,6);
	stage_star_fix[stage][1].SetStar(2,6,4,4);
	stage_star_fix[stage][2].SetStar(4,4,3,2);
	stage_star_fix[stage][3].SetStar(4,4,6,5);
	stage_star_fix[stage][4].SetStar(6,5,8,4);
	stage_star_fix[stage][5].SetStar(8,4,9,2);
	stage_star_fix[stage][6].SetStar(6,5,5,7);
	stage_star_fix[stage][7].SetStar(5,7,5,9);
	stage_star_fix[stage][8].SetStar(5,9,3,10);
	stage_star_fix[stage][9].SetStar(3,10,1,9);
	stage_star_fix[stage][10].SetStar(5,9,2,6);
	stage_star_fix[stage][11].SetStar(99, 99, 99, 99);

	stage++;
	stage_star_fix[stage][0].SetStar(1,7,2,5);
	stage_star_fix[stage][1].SetStar(2,5,3,1);
	stage_star_fix[stage][2].SetStar(3,1,7,3);
	stage_star_fix[stage][3].SetStar(7,3,9,7);
	stage_star_fix[stage][4].SetStar(9,7,3,1);
	stage_star_fix[stage][5].SetStar(9,7,7,9);
	stage_star_fix[stage][6].SetStar(7,9,8,11);
	stage_star_fix[stage][7].SetStar(99, 99, 99, 99);

	stage++;
	stage_star_fix[stage][0].SetStar(4,4,6,3);
	stage_star_fix[stage][1].SetStar(6,3,7,5);
	stage_star_fix[stage][2].SetStar(7,5,6,7);
	stage_star_fix[stage][3].SetStar(6,7,4,8);
	stage_star_fix[stage][4].SetStar(4,8,2,7);
	stage_star_fix[stage][5].SetStar(2,7,1,5);
	stage_star_fix[stage][6].SetStar(1,5,2,3);
	stage_star_fix[stage][7].SetStar(2,3,4,4);
	stage_star_fix[stage][8].SetStar(99, 99, 99, 99);

	stage++;
	stage_star_fix[stage][0].SetStar(8,1,5,4);
	stage_star_fix[stage][1].SetStar(5,4,3,5);
	stage_star_fix[stage][2].SetStar(3,5,5,7);
	stage_star_fix[stage][3].SetStar(5,7,7,7);
	stage_star_fix[stage][4].SetStar(3,5,2,7);
	stage_star_fix[stage][5].SetStar(2,7,0,8);
	stage_star_fix[stage][6].SetStar(0,8,2,11);
	stage_star_fix[stage][7].SetStar(2,11,3,9);
	stage_star_fix[stage][8].SetStar(3,9,5,9);
	stage_star_fix[stage][9].SetStar(5,9,7,10);
	stage_star_fix[stage][10].SetStar(99, 99, 99, 99);

	stage++;
	stage_star_fix[stage][0].SetStar(4,3,5,5);
	stage_star_fix[stage][1].SetStar(5,5,7,5);
	stage_star_fix[stage][2].SetStar(7,5,5,7);
	stage_star_fix[stage][3].SetStar(5,7,6,9);
	stage_star_fix[stage][4].SetStar(6,9,4,8);
	stage_star_fix[stage][5].SetStar(4,8,2,9);
	stage_star_fix[stage][6].SetStar(2,9,3,7);
	stage_star_fix[stage][7].SetStar(3,7,1,5);
	stage_star_fix[stage][8].SetStar(1,5,3,5);
	stage_star_fix[stage][9].SetStar(3,5,4,3);
	stage_star_fix[stage][10].SetStar(99, 99, 99, 99);

	stage++;
	stage_star_fix[stage][0].SetStar(1,1,2,3);
	stage_star_fix[stage][1].SetStar(0,3,2,3);
	stage_star_fix[stage][2].SetStar(2,3,4,2);
	stage_star_fix[stage][3].SetStar(4,2,6,3);
	stage_star_fix[stage][4].SetStar(6,3,8,3);
	stage_star_fix[stage][5].SetStar(6,1,6,3);
	stage_star_fix[stage][6].SetStar(2,3,2,6);
	stage_star_fix[stage][7].SetStar(2,6,0,7);
	stage_star_fix[stage][8].SetStar(0,7,0,9);
	stage_star_fix[stage][9].SetStar(2,6,3,8);
	stage_star_fix[stage][10].SetStar(6,3,5,6);
	stage_star_fix[stage][11].SetStar(5,6,5,8);
	stage_star_fix[stage][12].SetStar(5,6,6,8);
	stage_star_fix[stage][13].SetStar(99, 99, 99, 99);
}

void StarBridge::CreateStage()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> rand_stage(0, 9);
	//���� �������� ������ ����
	int tmp_stage = rand_stage(gen);
	//���� ���������� �ߺ��Ͻ� �ٽ� ������
	if (now_stage == tmp_stage) {
		while (now_stage == tmp_stage) {
			tmp_stage = rand_stage(gen);
		}
		now_stage = tmp_stage;
	}
	else {
		now_stage = tmp_stage;
	}
	
	
	//���� �������� ����
	//�ִ�ġ ��ŭ ������
	for (int i = 0; i < 20; i++) {
		//���������� ������ ����ġ�� (99,99)�� ������ ���̻� ���� ���ϰ� ����
		if (stage_star_fix[now_stage][i].star1.x == 99 && stage_star_fix[now_stage][i].star1.y == 99 && stage_star_fix[now_stage][i].star2.x == 99 && stage_star_fix[now_stage][i].star2.y == 99) {
			star_line_count = i;
			break;
		}
		else {
			//�������� ����ġ ����
			stage_star_line[i]->SetStarOne(stage_star_fix[now_stage][i].star1);
			stage_star_line[i]->SetStarTwo(stage_star_fix[now_stage][i].star2);
			stage_star[i].star1 = stage_star_fix[now_stage][i].star1;
			stage_star[i].star2 = stage_star_fix[now_stage][i].star2;
		}
	}
	//�̴ϸʿ� �� ����
	mini_map->SetStar(stage_star, star_line_count);
}

void StarBridge::ResetStage()
{
	//�������� ����
	for (int i = 0; i < star_line_count; i++) {
		//���� ���� �ʱ�ȭ
		star_line[i]->ResetLine();
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			Star* tmp = star[i][j];
			if (tmp != NULL) {
				//�� ���� �ʱ�ȭ
				tmp->SetNone();
			}
		}
	}
	//�������� ����
	CreateStage();
}

void StarBridge::Update()
{
	//������ ��ư ����
	exit_button->GetCollider()->pos = CAM->GlobalPos() + Vector2(2300, 1300);
	//�̴ϸ� ��ġ ����
	mini_map->pos = CAM->GlobalPos() + Vector2(2350, 250);
	//ī�޶� �÷��̾� ���󰡰� ����
	CAM->SetTarget(player);
	//��� ������Ʈ
	bg->WorldUpdate();
	//�̴ϸ� ������Ʈ
	mini_map->Update();
	//������ ��ư Ŭ���� ���� ���콺 ������Ʈ ����
	mouse_object->pos = CAM->GlobalPos()+(mouse_pos*2);
	Vector2 collision;
	//������ ��ư Ŭ����
	if (mouse_object->isCollision(exit_button->GetCollider(),&collision)) {
		if (KEY_DOWN(VK_LBUTTON)) {
			//��������� ������ ����
			program->CreateScene(3, 1);
			return;
		}
	}
	
	//ó�� ������� ������ ���� �ϱ� ���� ���� üũ
	StarLine* check_line = NULL;
	for (int i = 0; i < star_line_count; i++) {
		if (star_line[i]->GetLineStatus() != StarLine::LINE_STATUS::COMP) {
			check_line = star_line[i];
			break;
		}
	}
	if (check_line == NULL) {
		ResetStage();
		return;
	}
	//�� ������ ��ŭ �ݺ�
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			Star* tmp = star[i][j];
			if (tmp != NULL) {
				Vector2 collision;
				//�÷��̾�� ���� �浹��
				if (player->GetHitCollider()->isCollision(tmp->GetCollider(), &collision)) {
					//Ű�� �������� ���� Ȱ��ȭ ���·� ����
					if (!player->IsStarFail()) {
						if (KEY_DOWN(VK_SPACE)) {
							//�� �ϳ��� Ȱ��ȭ �� ���°� �ƴҽ�
							if (check_line != NULL) {
								if (check_line->GetLineStatus() == StarLine::LINE_STATUS::NONE && active_star_count == 0) {
									tmp->SetActive();
									check_line->SetStarOne(Vector2(i, j));
									check_line->SetLine();
									active_star_count++;
								}
								//�� �ϳ��� Ȱ��ȭ �Ȼ���,Ȱ��ȭ�� ���� �ٸ� �� �϶�
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

	
	//Ȱ��ȭ�� ���� 2�� �Ͻ�
	if (active_star_count == 2) {
		//�ϼ� üũ
		bool comp_line = false;
		//�ߺ� üũ
		bool is_duplication = false;
		if (check_line != NULL) {
			//�ߺ� üũ
			for (int i = 0; i < star_line_count; i++) {
				if (star_line[i]->GetLineStatus() == StarLine::LINE_STATUS::COMP) {
					if (check_line->CheckLineComp(star_line[i]->GetStarOne(), star_line[i]->GetStarTwo())) {
						is_duplication = true;
						break;
					}
				}
			}
			//�ߺ��� �ƴҽ�
			if (!is_duplication) {
				//���� üũ
				for (int i = 0; i < star_line_count; i++) {
					int star1_x = stage_star_line[i]->GetStarOne().x;
					int star1_y = stage_star_line[i]->GetStarOne().y;
					int star2_x = stage_star_line[i]->GetStarTwo().x;
					int star2_y = stage_star_line[i]->GetStarTwo().y;
					if (check_line->CheckLineComp(Vector2(star1_x, star1_y), Vector2(star2_x, star2_y))) {
						star[star1_x][star1_y]->SetComp();
						star[star2_x][star2_y]->SetComp();
						S_STAGE minimap_star;
						minimap_star.SetStar(star1_x, star1_y, star2_x, star2_y);
						mini_map->SetCompStar(minimap_star);
						comp_line = true;
						break;
					}
				}
			}
		}
		//������ �ƴҽ�
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
		//Ȱ��ȭ�� �� üũ �ϴ� ī��Ʈ 0���� ����
		active_star_count = 0;
	}




	for (int i = 0; i < star_line_count; i++) {
		//�������� ���� ����
		/*
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
		*/

		//���� ���� ���� ǥ��
		//��������
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
		//�Ϸ� ������
		if (star_line[i]->GetLineStatus() == StarLine::LINE_STATUS::COMP) {
			int star1_x = star_line[i]->GetStarOne().x;
			int star1_y = star_line[i]->GetStarOne().y;
			Vector2 star1_pos = star[star1_x][star1_y]->pos;
			int star2_x = star_line[i]->GetStarTwo().x;
			int star2_y = star_line[i]->GetStarTwo().y;
			Vector2 star2_pos = star[star2_x][star2_y]->pos;

			star_line[i]->GetCollider()->pos = (star1_pos + star2_pos) / 2;
			star_line[i]->GetCollider()->rot.z = (star1_pos - star2_pos).Normalized().Angle();
			star_line[i]->SetSize((star1_pos - star2_pos).GetLength());
			star_line[i]->Update();
			star_line[i]->GetCollider()->WorldUpdate();
		}
	}

	//�� ������Ʈ
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			star[i][j]->Update();
		}
	}
	

	player->Update();
	exit_button->Update();
	mouse_object->WorldUpdate();
	player->LoadingEnd();
}

void StarBridge::Render()
{
	bg->Render();
	
	for (int i = 0; i < star_line_count; i++) {
		//�̴ϸʻ��������� ������
		/*
		stage_star_line[i]->Render();
		stage_star_line[i]->GetCollider()->Render();	
		*/
	}
	//������ ǥ�õǸ� ������
	for (int i = 0; i < star_line_count; i++) {
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
	exit_button->Render();
	mouse_object->Render();
	mini_map->Render();
}

void StarBridge::PostRender()
{
	for (int i = 0; i < 10; i++) {
		ImGui::SliderFloat2("stage[0].star1", (float*)&stage_star[i].star1, -3000, 3000);
		ImGui::SliderFloat2("stage[0].star2", (float*)&stage_star[i].star2, -3000, 3000);
	}
	ImGui::SliderFloat2("mouse", (float*)&mouse_object->pos, -3000, 3000);
	ImGui::SliderFloat2("exit", (float*)&exit_button->GetCollider()->pos, -3000, 3000);
	
	
	player->PostRender();
}
