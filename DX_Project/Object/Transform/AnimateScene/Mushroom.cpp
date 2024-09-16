#include "framework.h"

Mushroom::Mushroom(wstring file)
	:jump_height(0.0f)
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
	frames.clear();
	//��ũ���� ��

	//���� CHAR_STATUS::JUMP
	init_pos = { 73,72 };
	this_frame_size = { 62,64 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f));
	frames.clear();
	//���� ���� ��

	//��Ʈ CHAR_STATUS::HIT
	init_pos = { 6,141 };
	this_frame_size = { 62,65 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 0.5f));
	frames.clear();
	//��Ʈ ���� ��

	//���� CHAR_STATUS::DEAD
	init_pos = { 8,215 };
	this_frame_size = { 61,59 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	init_pos = { 75,218 };
	this_frame_size = { 59,52 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	init_pos = { 141,222 };
	this_frame_size = { 59,44 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 0.2f));
	frames.clear();
	//���� ���� ��


	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif
	VS = new VertexShader(L"Shader/VertexShader/VertexShaderUV.hlsl", 2, flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShaderUv.hlsl", flags);

	CB = new ColourBuffer();

	hit_collider = new RectCollider(Vector2(50, 50));
	foot_collider = new RectCollider(Vector2(20, 10));


	clip_cursor = 0;
	is_looking_left = false;
	action_status = CHAR_STATUS::IDLE;
	jump_speed = 0.0f;
	move_speed = 0;
	move_pos = 0;
	is_live = false;
	hit_point = 10;
}

Mushroom::~Mushroom()
{
	for (Clip* c : clips) {
		if (c != NULL) {
			delete c;
		}
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
		if (action_status != CHAR_STATUS::WALK && action_status != CHAR_STATUS::HIT && action_status != CHAR_STATUS::DEAD) {
			SetClip(CHAR_STATUS::IDLE);
		}
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
	if (is_running) {
		RunningMove();
	}
	else {
		NormalMove();
	}
}

void Mushroom::Render()
{
	if (is_live) {
		VS->Set();
		PS->Set();

		WB->SetVS(0);
		CB->SetPS(0);
	
		clips[(UINT)action_status]->Render();
		//�׵θ� ��ǥ�ø� ���� ����ó��
		hit_collider->Render();
		foot_collider->Render();
	}
}

void Mushroom::PostRender()
{
	
}
void Mushroom::IsCreate()
{
	if (zen_count == 0 && hit_point <= 0) {
		zen_count = Timer::Get()->GetRunTime() + 5.0f;
	}

	if (hit_point > 0) {
		is_live = true;
		SetClip(CHAR_STATUS::IDLE);
	}
}
void Mushroom::IsHit()
{
	if (action_status != CHAR_STATUS::HIT && action_status != CHAR_STATUS::DEAD) {
		hit_point--;
		SetClip(CHAR_STATUS::HIT);
	}
}
void Mushroom::NormalMove()
{
	if (action_status == CHAR_STATUS::HIT) {
		if (!clips[(UINT)CHAR_STATUS::HIT]->isPlay()) {
			clips[(UINT)CHAR_STATUS::HIT]->Play();
			if (hit_point <= 0) {
				SetClip(CHAR_STATUS::DEAD);
			}
			else {
				SetClip(CHAR_STATUS::IDLE);
			}
		}
	}
	if (action_status == CHAR_STATUS::DEAD) {
		if (!clips[(UINT)CHAR_STATUS::DEAD]->isPlay()) {
			clips[(UINT)CHAR_STATUS::DEAD]->Play();
			is_live = false;
			return;
		}
	}
	if (zen_count != 0) {
		if (zen_count < Timer::Get()->GetRunTime()) {
			if (hit_point <= 0) {
				hit_point = 10;
			}
			zen_count = 0;
		}
	}

	

	std::random_device rd;
	std::mt19937_64 gen(rd());
	if (move_check == 0) {
		move_check = Timer::Get()->GetRunTime() + 2.0f;
	}
	if (move_check < Timer::Get()->GetRunTime()) {
		if (action_status != CHAR_STATUS::HIT && action_status != CHAR_STATUS::DEAD) {
			std::uniform_int_distribution<int> rand_count(0, 5);
			//�̵�
			if (rand_count(gen) <= 2) {
				if (now_ground != NULL) {
					if (loading_end) {
						if (action_status != CHAR_STATUS::HIT) {
							SetClip(CHAR_STATUS::WALK);
						}
						int min = (int)now_ground->LeftVX();
						int max = (int)now_ground->RightVX();
						std::uniform_int_distribution<int> rand_count(min + 10, max - 10);
						move = (float)rand_count(gen);
					}
				}
			}
			//����
			else if (rand_count(gen) >= 2) {
				if (action_status != CHAR_STATUS::JUMP && action_status != CHAR_STATUS::HIT) {
					//���� ���� ������ ����
					jump_speed = 100.0f;
					SetClip(CHAR_STATUS::JUMP);
				}
			}
		}
		move_check = 0;
	}
	if (move != 0) {
		if (pos.x < move) {
			move_pos = 40.0f;
			move_speed = -40.0f;
			is_looking_left = true;
		}
		if (pos.x >= move) {
			move_pos = -40.0f;
			move_speed = 40.0f;
			is_looking_left = false;
		}
		if (action_status != CHAR_STATUS::HIT && action_status != CHAR_STATUS::DEAD) {
			SetClip(CHAR_STATUS::WALK);
		}
	}
	if (now_ground != NULL) {
		float min = now_ground->LeftVX();
		float max = now_ground->RightVX();

		if (pos.x > max) {
			pos.x -= 300.0f * DELTA;
		}
		if (pos.x < min) {
			pos.x += 300.0f * DELTA;
		}
	}
	//�߷� ����
	if (loading_end) {
		if (is_live) {
			jump_speed -= 9.8f * 20.0f * DELTA;
			if (jump_speed <= -250.0f) {
				jump_speed = -250.0f;
			}
			pos.y -= jump_speed * DELTA * 5.0f;
		}
	}
	//�̵� ���� ����
	if (action_status != CHAR_STATUS::IDLE && action_status != CHAR_STATUS::HIT && action_status != CHAR_STATUS::DEAD) {
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
		if (move != 0) {
			pos.x -= move_speed * DELTA * 5.0f;
		}
		if (move_pos == 40.0f) {
			if (pos.x >= move - 5) {
				move_pos = 0;
				move_speed = 0;
				move = 0;
				if (action_status != CHAR_STATUS::HIT) {
					SetClip(CHAR_STATUS::IDLE);
				}
			}
		}
		if (move_pos == -40.0f) {
			if (pos.x <= move + 5) {
				move_pos = 0;
				move_speed = 0;
				move = 0;
				if (action_status != CHAR_STATUS::HIT) {
					SetClip(CHAR_STATUS::IDLE);
				}
			}
		}
	}

	hit_collider->pos = pos + Vector2(0, 0);
	foot_collider->pos = pos + Vector2(0, 45);
	clips[(UINT)action_status]->Update();
	scale = clips[(UINT)action_status]->GetFrameSize() * 1.5;

	if (is_looking_left) {
		scale.x *= -1;
	}
	if (is_live) {
		WorldUpdate();

		hit_collider->WorldUpdate();
		foot_collider->WorldUpdate();
	}	
}
void Mushroom::RunningMove()
{
	hit_collider->pos = pos + Vector2(0, 0);
	foot_collider->pos = pos + Vector2(0, 45);
	clips[(UINT)action_status]->Update();
	scale = clips[(UINT)action_status]->GetFrameSize() * 1.5;

	if (is_looking_left) {
		scale.x *= -1;
	}
	WorldUpdate();
	hit_collider->WorldUpdate();
	foot_collider->WorldUpdate();
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
	case Mushroom::CHAR_STATUS::HIT://��Ʈ�ϴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case Mushroom::CHAR_STATUS::DEAD://�״� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	default:
		break;
	}
}
