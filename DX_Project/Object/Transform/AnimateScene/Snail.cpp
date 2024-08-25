#include "framework.h"

Snail::Snail(wstring file)
{
	Texture* t = Texture::Add(file);
	//���ϸ��� �̿��� �����̹��� ������ Texture�μ� �ε�

	//�׷��� �ε��� �̹���������� �κ��� ����Ұ����� �����ϴ� �������� ����

	vector<Frame*> frames;

	//��� CHAR_STATUS::IDLE
	Vector2 init_pos = { 5,4 };
	Vector2 this_frame_size = { 35,34 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//��� ���� ��

	//��ũ CHAR_STATUS::WALK
	init_pos = { 7,49 };
	this_frame_size = { 35,34 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	init_pos = { 54,49 };
	this_frame_size = { 37,34 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	init_pos = { 105,49 };
	this_frame_size = { 39,34 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	init_pos = { 159,49 };
	this_frame_size = { 41,34 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//��ũ���� ��
	
	//��Ʈ CHAR_STATUS::HIT
	init_pos = { 7,96 };
	this_frame_size = { 41,39 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 0.5f));
	frames.clear();
	//��Ʈ���³�
	VS = new VertexShader(L"Shader/VertexShader/VertexShaderUV.hlsl", 2);
	PS = new PixelShader(L"Shader/PixelShader/PixelShaderUv.hlsl");

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
	hit_point = 5;

}

Snail::~Snail()
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

void Snail::landing()
{
	if (jump_speed <= 0) {
		//�Ҽ��� 6�ڸ� ���ر����� ���е��� �ǽð� ��ǥó���� �̿����� �̻�
		// ���� �����鼭 ������ ��� �浹�ϴ� ������ ���ΰ� ���κ��� Ŀ���� ��Ȳ��
		// �и��� �߻��Ҽ� ����
		//���� �����ÿ� ���� ���¸� ����
		jump_speed = 0;
		pos.y += jump_speed * DELTA * 5.0f;
		if (action_status != CHAR_STATUS::WALK && action_status != CHAR_STATUS::HIT) {
			SetClip(CHAR_STATUS::IDLE);
		}
		move_pos = 0;
	}
}

void Snail::ResetJumpSpeed()
{
	//�������� �Ӹ��� �ھ�����
	//���� �ö󰡴����̶�� �ö��� ���ϰ� ����
	if (jump_speed > 0) {
		jump_speed = 0;
	}
}

void Snail::Update()
{
	if (action_status == CHAR_STATUS::HIT) {
		if (!clips[(UINT)action_status]->isPlay()) {
			clips[(UINT)action_status]->Play();
			SetClip(CHAR_STATUS::IDLE);
		}
	}
	if (zen_count != 0) {
		if (zen_count < Timer::Get()->GetRunTime()) {
			//is_live = true;
			hit_point = 5;
			zen_count = 0;
		}
	}
	
	if (hit_point <= 0) {
		is_live = false;
		return;
	}

	std::random_device rd;
	std::mt19937_64 gen(rd());
	if (move_check == 0) {
		move_check = Timer::Get()->GetRunTime() + 2;
	}
	if (move_check < Timer::Get()->GetRunTime()) {
		std::uniform_int_distribution<int> rand_count(0, 5);

		//�̵�
		if (rand_count(gen) <= 2) {
			if (now_ground != NULL) {
				if (loading_end) {
					if (action_status != CHAR_STATUS::HIT) {
						SetClip(CHAR_STATUS::WALK);
					}

					
					int min = now_ground->LeftVX();
					int max = now_ground->RightVX();
					std::uniform_int_distribution<int> rand_count(min + 10, max - 10);
					move = rand_count(gen);
				}
			}
		}
		//����
		else if (rand_count(gen) > 2) {
			move_pos = 0;
			move_speed = 0;
			if (action_status != CHAR_STATUS::HIT) {
				SetClip(CHAR_STATUS::IDLE);
			}
			
		}
		move_check = 0;
	}
	if (move != 0) {
		if (pos.x < move) {
			move_pos = 20.0f;
			move_speed = -20.0f;
			is_looking_left = true;
		}
		if (pos.x >= move) {
			move_pos = -20.0f;
			move_speed = 20.0f;
			is_looking_left = false;
		}
		if (action_status != CHAR_STATUS::HIT) {
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
	if (action_status != CHAR_STATUS::IDLE) {
		move_speed -= 9.8f * move_pos * DELTA;
		if (move_speed < -20.0f) {
			move_speed = -20.0f;
		}
		if (move_speed > 20.0f) {
			move_speed = 20.0f;
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
		if (move_pos == 20.0f) {
			if (pos.x >= move - 5) {
				move_pos = 0;
				move_speed = 0;
				move = 0;
				if (action_status != CHAR_STATUS::HIT) {
					SetClip(CHAR_STATUS::IDLE);
				}
				
			}
		}

		if (move_pos == -20.0f) {
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
	foot_collider->pos = pos + Vector2(0, 30);
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

void Snail::Render()
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

void Snail::PostRender()
{

}
void Snail::IsCreate()
{
	if (zen_count == 0) {
		zen_count = Timer::Get()->GetRunTime() + 5;
	}
	is_live = true;
}
void Snail::IsHit()
{
	if (action_status != CHAR_STATUS::HIT) {
		hit_point--;
		SetClip(CHAR_STATUS::HIT);
		if (hit_point <= 0) {
			is_live = false;
		}
		
	}	
}
void Snail::SetClip(CHAR_STATUS stat)
{
	if (stat == action_status) {
		return;
	}

	switch (stat)
	{
	case Snail::CHAR_STATUS::IDLE://���ߴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case Snail::CHAR_STATUS::WALK://�ȴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case Snail::CHAR_STATUS::HIT://�ȴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	default:
		break;
	}
}
