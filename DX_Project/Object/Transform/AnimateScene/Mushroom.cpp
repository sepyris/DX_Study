#include "framework.h"

Mushroom::Mushroom(wstring file)
{
	Texture* t = Texture::Add(file);
	//���ϸ��� �̿��� �����̹��� ������ Texture�μ� �ε�

	//�׷��� �ε��� �̹���������� �κ��� ����Ұ����� �����ϴ� �������� ����
	
	vector<Frame*> frames;
	

	//��� CHAR_STATUS::IDLE
	Vector2 init_pos = { 6,4 };
	Vector2 this_frame_size = { 63,58 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos = { 72,6 };
	this_frame_size = { 63,55 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//��� ���� ��

	//��ũ CHAR_STATUS::WALK
	init_pos = { 6,77 };
	this_frame_size = { 64,55 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos = { 73,72 };
	this_frame_size = { 62,64 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos = { 138,77 };
	this_frame_size = { 63,55 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	//��ũ���¿����������� ����� ���� ���� ��� �̿�
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//��ũ ���� ��

	VS = new VertexShader(L"Shader/VertexShader/VertexShaderUV.hlsl", 2);
	PS = new PixelShader(L"Shader/PixelShader/PixelShaderUv.hlsl");

	CB = new ColourBuffer();

	hit_collider = new RectCollider(Vector2(10, 10));
	foot_collider = new RectCollider(Vector2(20, 10));


	clip_cursor = 0;
	is_looking_left = false;
	action_status = CHAR_STATUS::IDLE;
	jump_speed = 0.0f;
	move_speed = 0;
	move_pos = 0;
}

Mushroom::~Mushroom()
{
	for (Clip* c : clips) {
		delete c;
	}
	delete CB;
	delete hit_collider;
	delete foot_collider;
}

void Mushroom::landing()
{
	if (jump_speed <= 0) {
		//�Ҽ��� 6�ڸ� ���ر����� ���е��� �ǽð� ��ǥó���� �̿����� �̻�
		// ���� �����鼭 ������ ��� �浹�ϴ� ������ ���ΰ� ���κ��� Ŀ���� ��Ȳ��
		// �и��� �߻��Ҽ� ����
		//���� �����ÿ� ���� ���¸� ����
		jump_speed = 0;
		pos.y += jump_speed * DELTA * 5.0f;
		SetClip(CHAR_STATUS::IDLE);
		move_pos = 0;
	}
}

void Mushroom::ResetJumpSpeed()
{
	//�������� �Ӹ��� �ھ�����
	//���� �ö󰡴����̶�� �ö��� ���ϰ� ����
	if (jump_speed > 0) {
		jump_speed = 0;
	}
}

void Mushroom::Update()
{

	if (pos.x > 2520) {
		pos.x -= 300.0f * DELTA;
	}
	if (pos.x < -1240) {
		pos.x += 300.0f * DELTA;
	}
	//�߷� ����
		jump_speed -= 9.8f * 20.0f * DELTA;
		if (jump_speed <= -250.0f) {
			jump_speed = -250.0f;
		}
		pos.y -= jump_speed * DELTA * 5.0f;

		//�̵� ���� ����
		move_speed -= 9.8f * move_pos * DELTA;

		if (move_speed < -50.0f) {
			move_speed = -50.0f;
		}
		if (move_speed > 50.0f) {
			move_speed = 50.0f;
		}
		if (move_pos == 0) {
			if (move_speed > 0.0f) {
				move_speed -= 9.8f * DELTA * 20.0f;
			}
			else if (move_speed < 0.0f) {
				move_speed += 9.8f * DELTA * 20.0f;
			}
		}
		pos.x -= move_speed * DELTA * 5.0f;

	/*
	//���帰 ���¿��� ������ �Ұ��ϹǷ� ���� ����
		//����Ű�� ����
	if (KEY_PRESS('C'))
	{
		//���� ���� ���°� �ƴ϶��
		if (action_status != CHAR_STATUS::JUMP) {
			//���� ���� ������ ����
			jump_speed = 100.0f;
			SetClip(CHAR_STATUS::JUMP);
		}
	}


	switch (action_status)
	{
	case Mushroom::CHAR_STATUS::IDLE:
		if (KEY_PRESS(VK_LEFT)) {
			move_pos = -10.0f;
			//pos.x -= 300.0f * DELTA;
			SetClip(CHAR_STATUS::WALK);
			is_looking_left = true;
		}
		else {
			move_pos = 0.0f;
		}
		if (KEY_PRESS(VK_RIGHT)) {
			move_pos = 10.0f;
			//pos.x += 300.0f * DELTA;
			SetClip(CHAR_STATUS::WALK);
			is_looking_left = false;
		}
		else {
			move_pos = 0.0f;
		}


		if (KEY_DOWN('C')) {
			SetClip(CHAR_STATUS::JUMP);
		}
		break;
	case Mushroom::CHAR_STATUS::WALK:
		if (KEY_PRESS(VK_LEFT)) {
			if (move_speed < 0) {
				move_speed = 0.0f;
			}
			move_pos = -10.0f;
			//pos.x -= 300.0f * DELTA;
			SetClip(CHAR_STATUS::WALK);
			is_looking_left = true;
		}
		if (KEY_PRESS(VK_RIGHT)) {
			if (move_speed > 0) {
				move_speed = 0.0f;
			}
			move_pos = 10.0f;
			//pos.x += 300.0f * DELTA;
			SetClip(CHAR_STATUS::WALK);
			is_looking_left = false;
		}
		if (!KEY_PRESS(VK_LEFT) && !KEY_PRESS(VK_RIGHT)) {
			SetClip(CHAR_STATUS::IDLE);
			move_pos = 0;
		}
		if (KEY_DOWN('C')) {
			SetClip(CHAR_STATUS::JUMP);
		}
		break;
	case Mushroom::CHAR_STATUS::JUMP:
		//���� �����϶� �¿� Ű�� ������ �¿�� �̵�
		//�� ����� ���� ����
		if (move_speed > 0) {
			if (KEY_PRESS(VK_LEFT)) {
				move_pos = -20.0f;
			}
			if (KEY_PRESS(VK_RIGHT)) {
				move_pos = 8.0f;
			}
		}
		if (KEY_PRESS(VK_LEFT)) {
			is_looking_left = true;
		}
		if (move_speed < 0) {
			if (KEY_PRESS(VK_RIGHT)) {
				move_pos = 20.0f;
			}
			if (KEY_PRESS(VK_LEFT)) {
				move_pos = -8.0f;
			}
		}
		if (KEY_PRESS(VK_RIGHT)) {
			is_looking_left = false;
		}

		break;
	case Mushroom::CHAR_STATUS::MAX:
		break;
	default:
		break;
	}
	*/
	hit_collider->pos = pos + Vector2(10, 0);
	foot_collider->pos = pos + Vector2(10, 50);
	clips[(UINT)action_status]->Update();
	scale = clips[(UINT)action_status]->GetFrameSize() * 1.5;
	if (is_looking_left) {
		scale.x *= -1;
	}


	WorldUpdate();

	hit_collider->WorldUpdate();
	foot_collider->WorldUpdate();

}

void Mushroom::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[(UINT)action_status]->Render();
	//�׵θ� ��ǥ�ø� ���� ����ó��
	hit_collider->Render();
	foot_collider->Render();
}

void Mushroom::PostRender()
{

}

void Mushroom::SetClip(CHAR_STATUS stat)
{
	if (stat == action_status) {
		return;
	}

	switch (stat)
	{
	case Mushroom::CHAR_STATUS::IDLE://���ߴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case Mushroom::CHAR_STATUS::WALK://�ȴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case Mushroom::CHAR_STATUS::JUMP://�����ϴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	default:
		break;
	}
}
