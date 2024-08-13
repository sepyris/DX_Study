#include "framework.h"

ImageScene::ImageScene()
{
	image = new ImageRect(L"Texture/Image/char1.png",Vector2(WIN_CENTER_X, WIN_CENTER_Y));
	flame = new ImageRect(L"Texture/Image/test.png", Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(0.5f, 0.5f));

	bg[0] = new BackGroundUV(L"Texture/Image/map.png", Vector2(0, 0), Vector2(1, 1), Vector2(WIN_CENTER_X, WIN_CENTER_Y));
	bg[1] = new BackGroundUV(L"Texture/Image/map.png", Vector2(1, 0), Vector2(0, 1), Vector2(WIN_CENTER_X + WIN_WIDTH, WIN_CENTER_Y));

	flame->is_active = false;
}

ImageScene::~ImageScene()
{
	delete image;
	delete flame;
	for (auto b : bg) {
		delete b;
	}
	
}

void ImageScene::Update()
{
	for (auto b : bg) {
		b->Update();
	}

	image->Update();
	flame->Update();
	/*
	if (interval > 0)
	{
		interval -= DELTA;

		if (interval <= 0)
		{
			if (flame->pos.Dot == mouse_pos.Dot) {
				flame->is_active = false;
			}
			interval = 0;
		}
	}
	else
	{
		if (!flame->is_active)
		{
			Vector2 dir = (mouse_pos - flame->pos).Normalized();
			flame->pos += dir * 80 * DELTA;

			interval = 1.0f;
			flame->is_active = true;
		}
	}
	*/


	if (KEY_PRESS(VK_LEFT)) {
		image->pos.x -= 200.0f * DELTA;
	}
	if (KEY_PRESS(VK_RIGHT)) {
		image->pos.x += 200.0f * DELTA;
	}
	if (KEY_PRESS(VK_UP)) {
		image->pos.y -= 200.0f * DELTA;
	}
	if (KEY_PRESS(VK_DOWN)) {
		image->pos.y += 200.0f * DELTA;
	}
	image->rot.z = (mouse_pos - image->pos).Normalized().Angle();
	interval = 1.0f;
}

void ImageScene::Render()
{
	for (auto b : bg) {
		b->Render();
	}
	
	image->Render();
	flame->Render();
}

void ImageScene::PostRender()
{
	ImGui::Text("interval:%f", interval);
}

/*
과제
1)수업시간중에 출력하지 못했던 사람들은
업로드한 프로젝트에서 이미지파일 교체(+ImageRect에서 불러오는 이미지 파일 주소)수정해서 출력시도해볼것
만약 정상적으로 출력 된다면
어느부분에서 안된것인지를 조사해볼것

주의점->가끔 이미지파일들 둥에서 프레임워크에서 정상적으로 출력될수 없는 이미지가 있음
그래서 동작이 보장된 프로젝트에서 조차 출력이 안된다면 다른 이미지를 구해 시도할것

도전과제:마우스의 위치를 곧바로 바라보도록 만들어보기

2)이미지 오브젝트를 움직이고 회전시키는등의 코드를 한번 만들어볼것
+ RectUV에서 사용되는 StartUV,EndUV의 값을 0~1의 범위 밖으로 확장시키면 무슨일이 일어나는지를 확인해볼것
(이 경우 size는 되도록 확인하기 쉽게 늘려볼것)



*/