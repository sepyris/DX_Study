#include "framework.h"

Running::Running()
{
	bg = new BackGroundUV(L"Texture/Image/runningbackground.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_X+WIN_WIDTH, WIN_CENTER_Y+WIN_HEIGHT), Vector2(2, 2), 0.0f, Vector2(SCREEN_SIZE_X, SCREEN_SIZE_Y));

	player = new AnimatePlayer(L"Texture/AnimateScene/Animation/sprite.png");
	player->SetRunning();
	CAM->SetTarget(player);
	player->pos = Vector2(-470, 1000);
	CAM->pos = Vector2(-1100, 700);


	exit_button = new ImageRect(L"Texture/Image/exit_button.png", Vector2(0, 0), Vector2(1, 1), 0.0f, Vector2(150, 75));
	mouse_object = new RectCollider(Vector2(10, 10));

	
	main_ground = new LoopImageRect(L"Texture/Image/footholdloop.png",Vector2(172,150), Vector2(100000, 150));
	main_ground->pos = Vector2(Vector2(WIN_CENTER_X, 1400));
	main_ground->GetCollider()->pos = Vector2(Vector2(WIN_CENTER_X, 1360));

	player->Update();
}

Running::~Running()
{
	delete main_ground;
	delete bg;
}

void Running::Update()
{
	//나가기 버튼 고정
	exit_button->GetCollider()->pos = CAM->GlobalPos()+Vector2(WIN_WIDTH-150, WIN_HEIGHT-50);
	mouse_object->pos = CAM->GlobalPos() + (mouse_pos);
	//카메라가 플레이어 따라가게 설정
	CAM->SetTarget(player);
	//배경 업데이트
	bg->WorldUpdate();
	bg->pos.x = CAM->GlobalPos().x;
	//나가기 버튼 클릭을 위한 마우스 오브젝트 설정
	
	Vector2 collision;
	//나가기 버튼 클릭시
	if (mouse_object->isCollision(exit_button->GetCollider(), &collision)) {
		if (KEY_DOWN(VK_LBUTTON)) {
			//입장맵으로 나가게 설정
			program->CreateScene(4, 3);
			return;
		}
	}
	if (player->pos.y > WIN_HEIGHT * 3) {
		player->pos = Vector2(WIN_CENTER_X + 545, 500);
	}
	bg->Update();

	if (main_ground != NULL) {
		Vector2 collision;
		if (player->GetCollider()->isCollision(main_ground->GetCollider(), &collision)) {
			if (player->pos.y < main_ground->pos.y) {
				if (player->GetCollider()->BottomVX() > main_ground->GetCollider()->TopVX() - 1.0f) {
					player->pos.y -= collision.y * DELTA * 20.0f;
					player->landing();
				}
			}
		}
	}
	main_ground->Update();
	player->Update();
	exit_button->Update();
	mouse_object->WorldUpdate();
	player->LoadingEnd();
}

void Running::Render()
{
	bg->Render();
	main_ground->Render();
	exit_button->Render();
	mouse_object->Render();
	player->Render();
}

void Running::PostRender()
{
}
