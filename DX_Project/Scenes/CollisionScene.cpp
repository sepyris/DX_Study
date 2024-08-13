#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{

	player = new RectCollider(Vector2(50, 50));

	CreateStage(stage);
	interval = 0;
}

CollisionScene::~CollisionScene()
{
	delete player;


	DeleteStage();
	
}

void CollisionScene::Update()
{
	if (is_collision) {
		player->SetColor(0, 0, 0);
	}
	else {
		player->SetColor(1, 0, 0);
	}

	//Ư�� ���������� ���� ����
	if (dummy_effect != NULL) {
		dummy_effect->WorldUpdate();
	}	
	
	//���� ��ġ ����
	if (end_stage != NULL) {
		end_stage->WorldUpdate();
		end_stage->SetColor(0.7f, 0.99f, 0.7f);
	}
	//�� ����
	for (int i = 0; i < OBSTACKLE_COUNT; i++) {
		if (obstackle[i] != NULL) {
			obstackle[i]->WorldUpdate();
		}
	}
	//�� ����
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (enemy[i] != NULL) {
			enemy[i]->SetColor(0, 0, 1);
			enemy[i]->WorldUpdate();
		}
	}
	//������ ����
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		if (item[i] != NULL) {
			item[i]->SetColor(1, 1, 0);
			item[i]->WorldUpdate();
		}
	}

	player->WorldUpdate();

	if (interval > 0) {
		interval -= DELTA;
		if (interval <= 0) {
			//�浹�� �۾�
			//���߱� ���� ���� �ߴ� ���� �ʱ�ȭ
			is_collision = false;
			//�������� ����
			ResetStage();
		}
	}
	else {
		Vector2 collision;
		for (int i = 0; i < ENEMY_COUNT; i++) {
			if (enemy[i] != NULL) {
				//���� �浹��
				if (player->isCollision(enemy[i])) {
					//���͹� �ð� 1��
					interval = 1.0f;
					//�浹 ����
					is_collision = true;
					
				}
			}
		}
		
		for (int i = 0; i < OBSTACKLE_COUNT; i++) {
			if (obstackle[i] != NULL) {
				//���� �浹�� ���θ����� ����
				if (player->isCollision(obstackle[i], &collision)) {
					if (collision.x < collision.y) {
						if (player->pos.x < obstackle[i]->pos.x) {
							player->pos.x -= collision.x;
						}
						else {
							player->pos.x += collision.x;
						}
					}
					else {
						if (player->pos.y < obstackle[i]->pos.y) {
							player->pos.y -= collision.y;
						}
						else {
							player->pos.y += collision.y;
						}
					}
				}
			}
		}
	}
	//������ ����� ��ġ�� ��򰡷� ����������
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		if (item[i] != NULL) {
			if (player->isCollision(item[i])) {
				//�ָ� ������
				item[i]->is_active = false;
				item[i]->pos = Vector2(-1000, -1000);
				//���� ���� �߰�
				earn_coin++;
			}
		}
	}
	
	//�������� ������Ʈ
	StageUpdate();
	//���� �÷��� Ȯ��
	EndCheck();
	
	//���� �浹�ÿ��� �������� �ʰ� ����
	if (!is_collision) {
		if (KEY_PRESS(VK_LEFT)) {
			player->pos.x -= 200.0f * DELTA;
		}
		if (KEY_PRESS(VK_RIGHT)) {
			player->pos.x += 200.0f * DELTA;
		}
		if (KEY_PRESS(VK_UP)) {
			player->pos.y -= 200.0f * DELTA;
		}
		if (KEY_PRESS(VK_DOWN)) {
			player->pos.y += 200.0f * DELTA;
		}
	}

	
}

void CollisionScene::Render()
{
	//������ġ ����
	if (end_stage != NULL) {
		end_stage->Render();
	}
	//�� ����
	for (int i = 0; i < OBSTACKLE_COUNT;i++) {
		//������� ���� ����
		if (obstackle[i] != NULL) {
			obstackle[i]->Render();
		}
	}
	//�� ����
	for (int i = 0; i < ENEMY_COUNT; i++) {
		//������� ���� ����
		if (enemy[i] != NULL) {
			enemy[i]->Render();
		}
	}
	//������ ����
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		//������� �����۸� ����
		if (item[i] != NULL) {
			item[i]->Render();
		}
	}
	
	player->Render();
}
void CollisionScene::PostRender()
{
	if (ImGui::TreeNode("CollisionScene")) {
		//�޴��� �Ϻθ� ������ ��� ����� ������
		for (int i = 0; i < ENEMY_COUNT; i++) {
			if (enemy[i] != NULL) {
				ImGui::SliderFloat2(string("enemy's pos").append(to_string(i).c_str()).c_str(),//�� �����̴��ٿ� ���� �̸� 
					//�����ؾ� �Ұ�:�ϳ��� �ƴ� �� �̻� ���� �� ���
					//���� �̸��� �� ��쿣 �ϳ��� �ٷ� ������ ������Ʈ�� �ǵ帮�� �Ǳ� ����
					(float*)&(enemy[i]->pos),//�� ������Ʈ�� �ٷ� �������� �ּ�
					//���� �� �Լ��� �Ǽ� 2���� �ٷ�� ������, �׿� �°� �Ǽ��� ��Ƽ� 2�� �ٷ�� �迭�� �������� �����ؾ���
					//�� �������� �ּҷμ� �����ؾ� �ϹǷ� ���� ���� ����ȯ
					0,//��������� �����̴����� �ּ�ġ
					WIN_WIDTH//��������� �����̴����� �ִ�ġ
				);
				//�����̴��� �� �̿��ؼ� �Ǽ� ������ 2���� �����ϴ� ImGui ������Ʈ
			}
		}
		ImGui::SliderAngle("player's Rotation", (float*)&(player->rot.z));
		ImGui::SliderFloat3("player's Rotation", (float*)&(player->rot), -2 * M_PI, 2 * M_PI);
		//SliderAngle�� �̿��ؼ� ȸ������ �ٲٴ� ��ɵ� ������
		//ȸ���� �ٷ�� ������ radian���� ȣȯ�� ���� ����
		//�׷��� SliderAngle��� SliderFloat�� �̿���

		ImGui::SliderFloat2("player's pos", (float*)&(player->pos), 0, WIN_WIDTH);
		ImGui::Text("EarnCoin:%d", earn_coin);
		ImGui::Text("StageCoin:%d", stage_coin);

		ImGui::TreePop();
		//�׷��� ������� ź���� ���⼭ �����ٰ� ����
	}
}
void CollisionScene::ResetStage()
{
	//�������� ����
	//������� �ִ� ���������� ����
	DeleteStage();
	//���� ���������� ����
	CreateStage(stage);
}

void CollisionScene::CreateStage(int stage)
{
	//�������� �ʱ�ȭ
	//���� ���� �ʱ�ȭ
	earn_coin = 0;
	//�������� �ʱ�ȭ�� ���� ���������� ���ε� �ʱ�ȭ
	stage_coin = 0;
	count = 0;
	//�� �ʱ�ȭ
	for (int i = 0; i < OBSTACKLE_COUNT; i++) {
		obstackle[i] = NULL;
	}
	//�� �ʱ�ȭ
	for (int i = 0; i < ENEMY_COUNT; i++) {
		enemy[i] = NULL;
		move_hor[i] = false;
		move_ver[i] = false;
	}
	//������ �ʱ�ȭ
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		item[i] = NULL;
	}

	//���� �������� �׵θ� �ۼ�
	obstackle[0] = new RectCollider(Vector2(WIN_WIDTH * 2, 150));
	obstackle[0]->pos = Vector2(0, 0);

	obstackle[1] = new RectCollider(Vector2(150, WIN_HEIGHT * 2));
	obstackle[1]->pos = Vector2(0, 0);

	obstackle[2] = new RectCollider(Vector2(150, WIN_HEIGHT * 2));
	obstackle[2]->pos = Vector2(WIN_WIDTH, 0);

	obstackle[3] = new RectCollider(Vector2(WIN_WIDTH * 2, 150));
	obstackle[3]->pos = Vector2(0, WIN_HEIGHT);
	
	switch (stage) {

	case 1: {
		//������������ �÷��̾� ��ġ �ʱ�ȭ
		player->pos = Vector2(140, 140);

		//�������� ���� ���� ��ġ �ʱ�ȭ
		end_stage = new RectCollider(Vector2(100, 600));
		end_stage->pos = Vector2(1180, 350);

		//�� �߰�
		obstackle[4] = new RectCollider(Vector2(100, 550));
		obstackle[4]->pos = Vector2(250, 300);

		obstackle[5] = new RectCollider(Vector2(100, 550));
		obstackle[5]->pos = Vector2(1080, 450);

		//�� �߰�
		move_right[0] = true;
		enemy[0] = new CircleCollider(25);
		enemy[0]->pos = Vector2(350, 200);

		move_right[1] = true;
		enemy[1] = new CircleCollider(25);
		enemy[1]->pos = Vector2(350, 350);

		move_right[2] = true;
		enemy[2] = new CircleCollider(25);
		enemy[2]->pos = Vector2(350, 500);

		move_right[3] = false;
		enemy[3] = new CircleCollider(25);
		enemy[3]->pos = Vector2(1000, 275);

		move_right[4] = false;
		enemy[4] = new CircleCollider(25);
		enemy[4]->pos = Vector2(1000, 425);

		move_right[5] = false;
		enemy[5] = new CircleCollider(25);
		enemy[5]->pos = Vector2(1000, 575);

		move_right[6] = false;
		enemy[6] = new CircleCollider(25);
		enemy[6]->pos = Vector2(1000, 125);

		//������ �߰�
		item[0] = new CircleCollider(25);
		item[0]->pos = Vector2(350, 200);

		item[1] = new CircleCollider(25);
		item[1]->pos = Vector2(350, 350);

		item[2] = new CircleCollider(25);
		item[2]->pos = Vector2(350, 500);

		item[3] = new CircleCollider(25);
		item[3]->pos = Vector2(1000, 275);

		item[4] = new CircleCollider(25);
		item[4]->pos = Vector2(1000, 425);

		item[5] = new CircleCollider(25);
		item[5]->pos = Vector2(1000, 575);

		item[6] = new CircleCollider(25);
		item[6]->pos = Vector2(1000, 125);
		
		break;
	}
	case 2:
		//������������ �÷��̾� ��ġ �ʱ�ȭ
		player->pos = Vector2(140, 350);

		//�������� ���� ���� ��ġ �ʱ�ȭ
		end_stage = new RectCollider(Vector2(200, 200));
		end_stage->pos = Vector2(1150, 350);


		//�� �߰�
		//���� ��
		obstackle[4] = new RectCollider(Vector2(300, 300));
		obstackle[4]->pos = Vector2(100, 150);

		obstackle[5] = new RectCollider(Vector2(300, 300));
		obstackle[5]->pos = Vector2(1100, 150);

		//�� �߰�
		//�Ʒ��� ��
		obstackle[6] = new RectCollider(Vector2(300, 300));
		obstackle[6]->pos = Vector2(100, 600);

		obstackle[7] = new RectCollider(Vector2(300, 300));
		obstackle[7]->pos = Vector2(1100, 600);

		//�� �߰�
		//�߾� ��
		obstackle[8] = new RectCollider(Vector2(400, 100));
		obstackle[8]->pos = Vector2(600, 250);

		obstackle[9] = new RectCollider(Vector2(400, 100));
		obstackle[9]->pos = Vector2(600, 500);

		//�� �߰�
		move_right[0] = false;
		move_hor[0] = true;
		enemy[0] = new CircleCollider(40);
		enemy[0]->pos = Vector2(900, 375);

		move_down[1] = false;
		move_ver[1] = true;
		enemy[1] = new CircleCollider(40);
		enemy[1]->pos = Vector2(880, 130);

		move_down[2] = true;
		move_ver[2] = true;
		enemy[2] = new CircleCollider(40);
		enemy[2]->pos = Vector2(320, 600);

		//������ �߰�
		item[0] = new CircleCollider(25);
		item[0]->pos = Vector2(600, 375);

		item[1] = new CircleCollider(25);
		item[1]->pos = Vector2(880, 130);

		item[2] = new CircleCollider(25);
		item[2]->pos = Vector2(320, 600);

		item[3] = new CircleCollider(25);
		item[3]->pos = Vector2(320, 130);

		item[4] = new CircleCollider(25);
		item[4]->pos = Vector2(880, 600);

		break;

	case 3:
		//������������ �÷��̾� ��ġ �ʱ�ȭ
		player->pos = Vector2(140, 140);

		//�������� ���� ���� ��ġ �ʱ�ȭ
		end_stage = new RectCollider(Vector2(100, 100));
		end_stage->pos = Vector2(640, 365);

		//�� �ʱ�ȭ
		dummy_effect = new RectCollider(Vector2(0, 0));
		dummy_effect->pos = Vector2(640, 365);
		enemy[0] = new CircleCollider(40);
		enemy[1] = new CircleCollider(40);
		enemy[2] = new CircleCollider(40);
		enemy[3] = new CircleCollider(40);

		enemy[4] = new CircleCollider(40);
		enemy[5] = new CircleCollider(40);
		enemy[6] = new CircleCollider(40);
		enemy[7] = new CircleCollider(40);

		//������ �ʱ�ȭ
		//�ܵ� ���� �ϱ� ���� ���߹ݺ����� �̿�
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 4; j++) {
				item[count] = new CircleCollider(25);
				item[count]->pos = Vector2(140 + (i * 100), 140 + (j * 150));
				count++;
			}
		}
		break;

	default:

		break;
	}
	//�������� ���� ���� �ڵ����� ����
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		if (item[i] != NULL) {
			stage_coin++;
		}
	}
	
}

void CollisionScene::DeleteStage()
{
	//�� ����
	for (int i = 0; i < OBSTACKLE_COUNT; i++) {
		if (obstackle[i] != NULL) {
			delete obstackle[i];
			obstackle[i] = NULL;
		}
	}
	//�� ����
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (enemy[i] != NULL) {
			delete enemy[i];
			enemy[i] = NULL;
		}
	}
	//������ ����
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		if (item[i] != NULL) {
			delete item[i];
			item[i] = NULL;
		}
	}
	//���� ����
	delete dummy_effect;
	dummy_effect = NULL;

	//�������� ����
	delete end_stage;
	end_stage = NULL;
	
}
void CollisionScene::StageUpdate()
{
	switch (stage) {

	//1�������� �� �����̱� ����
	case 1: {
		for (int i = 0; i < ENEMY_COUNT; i++) {
			//�¿�θ� �������� ���� �ϱ� ������ ������ ���δ� Ȯ�� ����
			if (enemy[i] != NULL) {
				if (move_right[i]) {//�������� �����̱� ����
					enemy[i]->pos.x += 200.0f * DELTA;
				}
				else {//�ݴ�� �����̱� ����
					enemy[i]->pos.x -= 200.0f * DELTA;
				}
				//������� �Ѿ�� ������ �ݴ� ����
				if (enemy[i]->pos.x > 1000.0f) {
					if (move_right[i] == true) {
						move_right[i] = false;
					}
				}
				if (enemy[i]->pos.x < 350.0f) {
					if (move_right[i] == false) {
						move_right[i] = true;
					}
				}
			}
		}
		break;
	}
	case 2:
		for (int i = 0; i < ENEMY_COUNT; i++) {
			if (enemy[i] != NULL) {
				//�����¿�� �����̱� ������ ������ ���� Ȯ��
				if (move_hor[i]) {
					if (move_right[i]) {//�������� �����̱� ����
						enemy[i]->pos.x += 200.0f * DELTA;
					}
					else if (!move_right[i]) {
						enemy[i]->pos.x -= 200.0f * DELTA;
					}
				}
				if (move_ver[i]) {
					if (move_down[i]) {//�������� �����̱� ����
						enemy[i]->pos.y += 200.0f * DELTA;
					}
					else if (!move_down[i]) {
						enemy[i]->pos.y -= 200.0f * DELTA;
					}
				}
				
				
				//������� �Ѿ�� ������ �ݴ� ����
				if (enemy[i]->pos.x > 900.0f) {
					if (move_right[i] == true) {
						move_right[i] = false;
					}
				}
				if (enemy[i]->pos.x < 300.0f) {
					if (move_right[i] == false) {
						move_right[i] = true;
					}
				}
				//������� �Ѿ�� ������ �ݴ� ����
				if (enemy[i]->pos.y > 600.0f) {
					if (move_down[i] == true) {
						move_down[i] = false;
					}
				}
				if (enemy[i]->pos.y < 130.0f) {
					if (move_down[i] == false) {
						move_down[i] = true;
					}
				}
			}
		}
		break;
	case 3:
		if (dummy_effect != NULL) {
			//���� ȸ��
			dummy_effect->rot.z += 1.0f * DELTA;
			for (int i = 0; i < ENEMY_COUNT; i++) {
				if (enemy[i] != NULL) {
					//�� ������Ʈ�� ���̿� ���� ���� ȸ��
					enemy[0]->pos = (Vector2)dummy_effect->pos + dummy_effect->Down() * 400.0f;
					enemy[1]->pos = (Vector2)dummy_effect->pos + dummy_effect->Up() * 400.0f;
					enemy[2]->pos = (Vector2)dummy_effect->pos + dummy_effect->Left() * 400.0f;
					enemy[3]->pos = (Vector2)dummy_effect->pos + dummy_effect->Right() * 400.0f;

					enemy[4]->pos = (Vector2)dummy_effect->pos + dummy_effect->Down() * 150.0f;
					enemy[5]->pos = (Vector2)dummy_effect->pos + dummy_effect->Up() * 150.0f;
					enemy[6]->pos = (Vector2)dummy_effect->pos + dummy_effect->Left() * 150.0f;
					enemy[7]->pos = (Vector2)dummy_effect->pos + dummy_effect->Right() * 150.0f;
				}
			}
		}

		break;
	default:
		break;
	}
}
void CollisionScene::EndCheck()
{
	//�÷��̾��� ������ ���ϱ�
	Vector2 half = player->Size() * 0.5f;
	float left = player->GlobalPos().x - half.x;
	float right = player->GlobalPos().x + half.x;
	float top = player->GlobalPos().y - half.y;
	float bottom = player->GlobalPos().y + half.y;

	//�÷��̾��� �������� ��� ���������ȿ� ������
	if (end_stage != NULL) {
		if (end_stage->isPointCollision(Vector2(left, top)) &&
			end_stage->isPointCollision(Vector2(left, bottom)) &&
			end_stage->isPointCollision(Vector2(right, top)) &&
			end_stage->isPointCollision(Vector2(right, bottom))) {
			//�������� ���ΰ� ���� ������ ������
			if (stage_coin == earn_coin) {
				stage++;//���� ���������� ����
				ResetStage();//�������� ����
			}
		}
	}
}
