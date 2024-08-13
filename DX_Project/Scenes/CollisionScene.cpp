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

	//특수 스테이지를 위한 더미
	if (dummy_effect != NULL) {
		dummy_effect->WorldUpdate();
	}	
	
	//종료 위치 설정
	if (end_stage != NULL) {
		end_stage->WorldUpdate();
		end_stage->SetColor(0.7f, 0.99f, 0.7f);
	}
	//벽 설정
	for (int i = 0; i < OBSTACKLE_COUNT; i++) {
		if (obstackle[i] != NULL) {
			obstackle[i]->WorldUpdate();
		}
	}
	//적 설정
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (enemy[i] != NULL) {
			enemy[i]->SetColor(0, 0, 1);
			enemy[i]->WorldUpdate();
		}
	}
	//아이템 설정
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
			//충돌시 작업
			//멈추기 위해 설정 했던 변수 초기화
			is_collision = false;
			//스테이지 리셋
			ResetStage();
		}
	}
	else {
		Vector2 collision;
		for (int i = 0; i < ENEMY_COUNT; i++) {
			if (enemy[i] != NULL) {
				//적과 충돌시
				if (player->isCollision(enemy[i])) {
					//인터벌 시간 1초
					interval = 1.0f;
					//충돌 설정
					is_collision = true;
					
				}
			}
		}
		
		for (int i = 0; i < OBSTACKLE_COUNT; i++) {
			if (obstackle[i] != NULL) {
				//벽과 충돌시 가로막히게 설정
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
	//아이템 습득시 위치를 어딘가로 날려버리기
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		if (item[i] != NULL) {
			if (player->isCollision(item[i])) {
				//멀리 날리기
				item[i]->is_active = false;
				item[i]->pos = Vector2(-1000, -1000);
				//얻은 코인 추가
				earn_coin++;
			}
		}
	}
	
	//스테이지 업데이트
	StageUpdate();
	//종료 플래그 확인
	EndCheck();
	
	//적과 충돌시에는 움직이지 않게 설정
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
	//종료위치 렌더
	if (end_stage != NULL) {
		end_stage->Render();
	}
	//벽 렌더
	for (int i = 0; i < OBSTACKLE_COUNT;i++) {
		//만들어진 벽만 렌더
		if (obstackle[i] != NULL) {
			obstackle[i]->Render();
		}
	}
	//적 렌더
	for (int i = 0; i < ENEMY_COUNT; i++) {
		//만들어진 적만 렌더
		if (enemy[i] != NULL) {
			enemy[i]->Render();
		}
	}
	//아이템 렌더
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		//만들어진 아이템만 렌더
		if (item[i] != NULL) {
			item[i]->Render();
		}
	}
	
	player->Render();
}
void CollisionScene::PostRender()
{
	if (ImGui::TreeNode("CollisionScene")) {
		//메뉴중 일부를 접었다 펴게 만들고 싶을때
		for (int i = 0; i < ENEMY_COUNT; i++) {
			if (enemy[i] != NULL) {
				ImGui::SliderFloat2(string("enemy's pos").append(to_string(i).c_str()).c_str(),//이 슬라이더바에 붙일 이름 
					//조심해야 할것:하나가 아닌 둘 이상 쓰게 될 경우
					//같은 이름을 쓸 경우엔 하나의 바로 복수의 오브젝트를 건드리게 되기 때문
					(float*)&(enemy[i]->pos),//이 컴포넌트가 다룰 데이터의 주소
					//지금 이 함수는 실수 2개를 다루기 때문에, 그에 맞게 실수의 데티어를 2개 다루는 배열의 시작점을 전달해야함
					//그 시작점을 주소로서 전달해야 하므로 위와 같이 형변환
					0,//만들어지는 슬라이더바의 최소치
					WIN_WIDTH//만들어지는 슬라이더바의 최대치
				);
				//슬라이더바 를 이용해서 실수 데이터 2개를 관리하는 ImGui 컴포넌트
			}
		}
		ImGui::SliderAngle("player's Rotation", (float*)&(player->rot.z));
		ImGui::SliderFloat3("player's Rotation", (float*)&(player->rot), -2 * M_PI, 2 * M_PI);
		//SliderAngle을 이용해서 회전각을 바꾸는 기능도 있지만
		//회전을 다루는 단위인 radian과는 호환이 되지 않음
		//그래서 SliderAngle대신 SliderFloat을 이요함

		ImGui::SliderFloat2("player's pos", (float*)&(player->pos), 0, WIN_WIDTH);
		ImGui::Text("EarnCoin:%d", earn_coin);
		ImGui::Text("StageCoin:%d", stage_coin);

		ImGui::TreePop();
		//그렇게 만들어진 탄위가 여기서 끝난다고 설정
	}
}
void CollisionScene::ResetStage()
{
	//스테이지 리셋
	//만들어져 있는 스테이지를 삭제
	DeleteStage();
	//현재 스테이지를 생성
	CreateStage(stage);
}

void CollisionScene::CreateStage(int stage)
{
	//스테이지 초기화
	//얻은 코인 초기화
	earn_coin = 0;
	//스테이지 초기화를 위해 스테이지의 코인도 초기화
	stage_coin = 0;
	count = 0;
	//벽 초기화
	for (int i = 0; i < OBSTACKLE_COUNT; i++) {
		obstackle[i] = NULL;
	}
	//적 초기화
	for (int i = 0; i < ENEMY_COUNT; i++) {
		enemy[i] = NULL;
		move_hor[i] = false;
		move_ver[i] = false;
	}
	//아이템 초기화
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		item[i] = NULL;
	}

	//공통 스테이지 테두리 작성
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
		//스테이지내에 플레이어 위치 초기화
		player->pos = Vector2(140, 140);

		//스테이지 내에 종료 위치 초기화
		end_stage = new RectCollider(Vector2(100, 600));
		end_stage->pos = Vector2(1180, 350);

		//벽 추가
		obstackle[4] = new RectCollider(Vector2(100, 550));
		obstackle[4]->pos = Vector2(250, 300);

		obstackle[5] = new RectCollider(Vector2(100, 550));
		obstackle[5]->pos = Vector2(1080, 450);

		//적 추가
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

		//아이템 추가
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
		//스테이지내에 플레이어 위치 초기화
		player->pos = Vector2(140, 350);

		//스테이지 내에 종료 위치 초기화
		end_stage = new RectCollider(Vector2(200, 200));
		end_stage->pos = Vector2(1150, 350);


		//벽 추가
		//위쪽 벽
		obstackle[4] = new RectCollider(Vector2(300, 300));
		obstackle[4]->pos = Vector2(100, 150);

		obstackle[5] = new RectCollider(Vector2(300, 300));
		obstackle[5]->pos = Vector2(1100, 150);

		//벽 추가
		//아래쪽 벽
		obstackle[6] = new RectCollider(Vector2(300, 300));
		obstackle[6]->pos = Vector2(100, 600);

		obstackle[7] = new RectCollider(Vector2(300, 300));
		obstackle[7]->pos = Vector2(1100, 600);

		//벽 추가
		//중앙 벽
		obstackle[8] = new RectCollider(Vector2(400, 100));
		obstackle[8]->pos = Vector2(600, 250);

		obstackle[9] = new RectCollider(Vector2(400, 100));
		obstackle[9]->pos = Vector2(600, 500);

		//적 추가
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

		//아이템 추가
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
		//스테이지내에 플레이어 위치 초기화
		player->pos = Vector2(140, 140);

		//스테이지 내에 종료 위치 초기화
		end_stage = new RectCollider(Vector2(100, 100));
		end_stage->pos = Vector2(640, 365);

		//적 초기화
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

		//아이템 초기화
		//잔득 생성 하기 위해 이중반복문을 이용
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
	//스테이지 코인 갯수 자동으로 설정
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		if (item[i] != NULL) {
			stage_coin++;
		}
	}
	
}

void CollisionScene::DeleteStage()
{
	//벽 삭제
	for (int i = 0; i < OBSTACKLE_COUNT; i++) {
		if (obstackle[i] != NULL) {
			delete obstackle[i];
			obstackle[i] = NULL;
		}
	}
	//적 삭제
	for (int i = 0; i < ENEMY_COUNT; i++) {
		if (enemy[i] != NULL) {
			delete enemy[i];
			enemy[i] = NULL;
		}
	}
	//아이템 삭제
	for (int i = 0; i < ITEM_MAX_COUNT; i++) {
		if (item[i] != NULL) {
			delete item[i];
			item[i] = NULL;
		}
	}
	//더미 삭제
	delete dummy_effect;
	dummy_effect = NULL;

	//종료지점 삭제
	delete end_stage;
	end_stage = NULL;
	
}
void CollisionScene::StageUpdate()
{
	switch (stage) {

	//1스테이지 적 움직이기 설정
	case 1: {
		for (int i = 0; i < ENEMY_COUNT; i++) {
			//좌우로만 움직임을 설정 하기 때문에 움직임 여부는 확인 안함
			if (enemy[i] != NULL) {
				if (move_right[i]) {//한쪽으로 움직이기 설정
					enemy[i]->pos.x += 200.0f * DELTA;
				}
				else {//반대로 움직이기 설정
					enemy[i]->pos.x -= 200.0f * DELTA;
				}
				//어느정도 넘어가면 움직임 반대 설정
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
				//상하좌우로 움직이기 때문에 움직임 여부 확인
				if (move_hor[i]) {
					if (move_right[i]) {//한쪽으로 움직이기 설정
						enemy[i]->pos.x += 200.0f * DELTA;
					}
					else if (!move_right[i]) {
						enemy[i]->pos.x -= 200.0f * DELTA;
					}
				}
				if (move_ver[i]) {
					if (move_down[i]) {//한쪽으로 움직이기 설정
						enemy[i]->pos.y += 200.0f * DELTA;
					}
					else if (!move_down[i]) {
						enemy[i]->pos.y -= 200.0f * DELTA;
					}
				}
				
				
				//어느정도 넘어가면 움직임 반대 설정
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
				//어느정도 넘어가면 움직임 반대 설정
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
			//더미 회전
			dummy_effect->rot.z += 1.0f * DELTA;
			for (int i = 0; i < ENEMY_COUNT; i++) {
				if (enemy[i] != NULL) {
					//적 오브젝트도 더미에 따라 같이 회전
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
	//플레이어의 꼭지점 구하기
	Vector2 half = player->Size() * 0.5f;
	float left = player->GlobalPos().x - half.x;
	float right = player->GlobalPos().x + half.x;
	float top = player->GlobalPos().y - half.y;
	float bottom = player->GlobalPos().y + half.y;

	//플레이어의 꼭지점이 모두 엔드지점안에 들어갔을때
	if (end_stage != NULL) {
		if (end_stage->isPointCollision(Vector2(left, top)) &&
			end_stage->isPointCollision(Vector2(left, bottom)) &&
			end_stage->isPointCollision(Vector2(right, top)) &&
			end_stage->isPointCollision(Vector2(right, bottom))) {
			//스테이지 코인과 얻은 코인이 같을때
			if (stage_coin == earn_coin) {
				stage++;//다음 스테이지로 설정
				ResetStage();//스테이지 리셋
			}
		}
	}
}
