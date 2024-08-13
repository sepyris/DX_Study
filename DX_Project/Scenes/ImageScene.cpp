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
����
1)�����ð��߿� ������� ���ߴ� �������
���ε��� ������Ʈ���� �̹������� ��ü(+ImageRect���� �ҷ����� �̹��� ���� �ּ�)�����ؼ� ��½õ��غ���
���� ���������� ��� �ȴٸ�
����κп��� �ȵȰ������� �����غ���

������->���� �̹������ϵ� �տ��� �����ӿ�ũ���� ���������� ��µɼ� ���� �̹����� ����
�׷��� ������ ����� ������Ʈ���� ���� ����� �ȵȴٸ� �ٸ� �̹����� ���� �õ��Ұ�

��������:���콺�� ��ġ�� ��ٷ� �ٶ󺸵��� ������

2)�̹��� ������Ʈ�� �����̰� ȸ����Ű�µ��� �ڵ带 �ѹ� ������
+ RectUV���� ���Ǵ� StartUV,EndUV�� ���� 0~1�� ���� ������ Ȯ���Ű�� �������� �Ͼ������ Ȯ���غ���
(�� ��� size�� �ǵ��� Ȯ���ϱ� ���� �÷�����)



*/