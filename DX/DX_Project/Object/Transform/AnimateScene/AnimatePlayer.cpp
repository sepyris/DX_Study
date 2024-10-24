#include "framework.h"

AnimatePlayer::AnimatePlayer(wstring file)
	:attack_collider(NULL),
	hit_point(0),
	jump_height(0)
{
	Texture* t = Texture::Add(file);
	//���ϸ��� �̿��� �����̹��� ������ Texture�μ� �ε�

	//�׷��� �ε��� �̹���������� �κ��� ����Ұ����� �����ϴ� �������� ����
	Vector2 init_pos = { 3,5 };
	//�̹����� ��� ��ǥ���� ����Ұ�����
	Vector2 this_frame_size = { 82,78 };
	//����� ��������Ʈ�� ũ�Ⱑ ������

	//Clips�� ������ �ִϸ��̼��� ����� ���� �̸� �����δ� ������ �������� ������
	vector<Frame*> frames;

	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos += Vector2(88, 0);

	//��� CHAR_STATUS::IDLE
	for (int i = 0; i < 4; i++) {
		frames.push_back(
			new Frame(
				file,
				init_pos.x + i * (this_frame_size.x + 6),
				init_pos.y,
				this_frame_size.x,
				this_frame_size.y
			));
		//frame�� �� �����ڴ�
		//����� file���� �տ� 2���� x,y ��ǥ���� ������
		//���� 2���� a,b����ŭ�� ����/���� ������ŭ�� ������ ����,
		//�̹��� ������ �ش� �������� �̿��Ͽ�
		//�ִϸ��̼��� �� �������� ������ ������
	}

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	//�� �Լ��� �������� �̺��Ϳ� �����ϰ� �ִ� �ּҵ鸸�� ��������� �Ҵ� ���������� ���� ����
	//�׷��� �̷��� clear�� �̿��ص� frames�ȿ� ����ִ� �����ӵ��� ������
	//�̸� �̿��ؼ� �Ƚ��ϰ� ���� �����ִϸ��̼��� �߰��ϴ� �۾��� �ϸ� �ȴ�.
	frames.clear();
	//��� ���� ��

	//��ũ CHAR_STATUS::WALK
	init_pos = { 3,93 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos += Vector2(88, 0);
	for (int i = 0; i < 3; i++) {
		frames.push_back(
			new Frame(
				file,
				init_pos.x + i * (this_frame_size.x + 6),
				init_pos.y,
				this_frame_size.x,
				this_frame_size.y
			));
		//frame�� �� �����ڴ�
		//����� file���� �տ� 2���� x,y ��ǥ���� ������
		//���� 2���� a,b����ŭ�� ����/���� ������ŭ�� ������ ����,
		//�̹��� ������ �ش� �������� �̿��Ͽ�
		//�ִϸ��̼��� �� �������� ������ ������
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//��ũ ���� ��

	//���� CHAR_STATUS::JUMP
	init_pos = { 3,181 };
	this_frame_size = { 82,78 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP));
	frames.clear();
	//���� ���� ��

	//���帮�� CHAR_STATUS::PRONE
	init_pos = { 3,262 };
	this_frame_size = { 117,84 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP));
	frames.clear();
	//���帮�� ���� ��

	//�޸��� CHAR_STATUS::RUN
	init_pos = { 3,93 };
	this_frame_size = { 82,78 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos += Vector2(88, 0);
	for (int i = 0; i < 3; i++) {
		frames.push_back(
			new Frame(
				file,
				init_pos.x + i * (this_frame_size.x + 6),
				init_pos.y,
				this_frame_size.x,
				this_frame_size.y
			));
		//frame�� �� �����ڴ�
		//����� file���� �տ� 2���� x,y ��ǥ���� ������
		//���� 2���� a,b����ŭ�� ����/���� ������ŭ�� ������ ����,
		//�̹��� ������ �ش� �������� �̿��Ͽ�
		//�ִϸ��̼��� �� �������� ������ ������
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//�޸��� ���� ��

	//�޴޸��� CHAR_STATUS::ROPE
	init_pos = { 3,357 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos += Vector2(88, 0);
	for (int i = 0; i < 1; i++) {
		frames.push_back(
			new Frame(
				file,
				init_pos.x + i * (this_frame_size.x + 6),
				init_pos.y,
				this_frame_size.x,
				this_frame_size.y
			));
		//frame�� �� �����ڴ�
		//����� file���� �տ� 2���� x,y ��ǥ���� ������
		//���� 2���� a,b����ŭ�� ����/���� ������ŭ�� ������ ����,
		//�̹��� ������ �ش� �������� �̿��Ͽ�
		//�ִϸ��̼��� �� �������� ������ ������
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//�޴޸��� ���� ��

	//���� CHAR_STATUS::ATTACK
	init_pos = { 2,441 };
	this_frame_size = { 82,79 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos += Vector2(88, 0);
	for (int i = 0; i < 2; i++) {
		frames.push_back(
			new Frame(
				file,
				init_pos.x + i * (this_frame_size.x),
				init_pos.y,
				this_frame_size.x,
				this_frame_size.y
			));
		//frame�� �� �����ڴ�
		//����� file���� �տ� 2���� x,y ��ǥ���� ������
		//���� 2���� a,b����ŭ�� ����/���� ������ŭ�� ������ ����,
		//�̹��� ������ �ش� �������� �̿��Ͽ�
		//�ִϸ��̼��� �� �������� ������ ������
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 0.2f));
	frames.clear();
	//���� ���� ��

	//��Ʈ CHAR_STATUS::HIT
	init_pos = { 3,181 };
	this_frame_size = { 82,78 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();
	//��Ʈ ���� ��

	//�ö��� CHAR_STATUS::FLY
	init_pos = { 2,529 };
	this_frame_size = { 82,85 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos = { 90,529 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 0.5f));
	frames.clear();
	//�ö��� ���� ��

	//�ö��̽��� CHAR_STATUS::FLY
	init_pos = { 2,622 };
	this_frame_size = { 82,85 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos = { 90,622 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 0.5f));
	frames.clear();
	//�ö��̽��� ���� ��


	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif
	VS = new VertexShader(L"Shader/VertexShader/VertexShaderUV.hlsl", 2, flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShaderUv.hlsl", flags);

	CB = new ColourBuffer();

	//collider = new RectCollider(clips[(UINT)action_status]->GetFrameOrigSize() * 3.0f);
	//�浹 ������ ũ�⸦ ��¹��� ����� ����
	//1)����ϴ� ��������Ʈ ��ü�� ũ�⸦ �����ͼ� ���� ��Ű�°�
	//�׷��� �̴� ����ϴ� ��������Ʈ��
	// �� ����� ������ �������½����� �̷������븸 �����ϰ�
	// ������ �߰��� ���̼��� ���� ������ ���� ������ ����
	// ���� ��������Ʈ�� �������� ũ�� �� ����ġ �ϱ⶧���� ����� ������ ����
	// 
	//2)�밡��
	hit_collider = new RectCollider(Vector2(10, 10));
	foot_collider = new RectCollider(Vector2(20, 10));


	clip_cursor = 0;
	is_looking_left = false;
	action_status = CHAR_STATUS::IDLE;
	jump_speed = 0.0f;
	init_jump_pos = 0.0f;
	is_can_double_jump = false;
	is_jump_attack = false;
	move_speed = 0;
	move_pos = 0;
	moveup_speed = 0;
	moveup_pos = 0;
}

AnimatePlayer::~AnimatePlayer()
{
	for (Clip* c : clips) {
		delete c;
	}
	delete CB;
	delete hit_collider;
	delete foot_collider;
	if (attack_collider != NULL) {
		delete attack_collider;
	}
}

void AnimatePlayer::landing()
{
	if (jump_speed <= 0) {
		//�Ҽ��� 6�ڸ� ���ر����� ���е��� �ǽð� ��ǥó���� �̿����� �̻�
		// ���� �����鼭 ������ ��� �浹�ϴ� ������ ���ΰ� ���κ��� Ŀ���� ��Ȳ��
		// �и��� �߻��Ҽ� ����
		//���� �����ÿ� ���� ���¸� ����
		if (move_speed > 0) {
			jump_speed = -move_speed * 0.7f;
		}
		else {
			jump_speed = move_speed * 0.7f;
		}
		

		pos.y += jump_speed * DELTA * 5.0f;
		is_jump_attack = false;
		if (action_status == CHAR_STATUS::ROPE && action_status != CHAR_STATUS::HIT) {
			if (!KEY_PRESS(VK_UP) && !KEY_PRESS(VK_DOWN)) {
				SetClip(CHAR_STATUS::IDLE);
				is_can_double_jump = false;
				move_pos = 0;
			}
		}
		if (action_status == CHAR_STATUS::JUMP) {
			if (is_running) {
				SetClip(CHAR_STATUS::WALK);
				is_can_double_jump = true;
			}
			else {
				SetClip(CHAR_STATUS::IDLE);
				is_can_double_jump = false;
			}
			move_pos = 0;
		}
	}
}

void AnimatePlayer::ResetJumpSpeed()
{
	//�������� �Ӹ��� �ھ�����
	//���� �ö󰡴����̶�� �ö��� ���ϰ� ����
	if (jump_speed > 0) {
		jump_speed = 0;
	}
}

bool AnimatePlayer::IsHanging()
{
	if (KEY_PRESS(VK_UP)) {
		if (action_status == CHAR_STATUS::IDLE || action_status == CHAR_STATUS::JUMP) {
			SetClip(CHAR_STATUS::ROPE);
		}
	}
	if (KEY_PRESS(VK_DOWN)) {
		if (action_status == CHAR_STATUS::IDLE || action_status == CHAR_STATUS::PRONE || action_status == CHAR_STATUS::ROPE) {
			foot_collider->pos.y -= 3.0f;
			SetClip(CHAR_STATUS::ROPE);
		}
	}
	if (action_status == CHAR_STATUS::ROPE) {
		SetClip(CHAR_STATUS::ROPE);
		jump_speed = 0;
		if (!KEY_PRESS(VK_LEFT) && !KEY_PRESS(VK_RIGHT)) {
			move_speed = 0;
		}
		return true;
	}
	else {
		return false;
	}

}

void AnimatePlayer::SetIdle()
{
	if (action_status == CHAR_STATUS::ROPE) {
		SetClip(CHAR_STATUS::JUMP);
	}
}

void AnimatePlayer::Update()
{
	if (is_hit_count != 0) {
		//��Ʈ�� ��¦��¦ ����
		if (hit_check) {
			SetColor(Float4(0, 0, 0, 0));
			hit_check = false;
		}
		else {
			SetColor(Float4(1, 1, 1, 1));
			hit_check = true;
		}
		if (is_hit_count < Timer::Get()->GetRunTime()) {
			is_hit_count = 0;
			SetColor(Float4(1, 1, 1, 1));
			hit_check = true;
		}
	}

	if (is_star) {
		FlyMove();
	}
	else if (is_running) {
		RunningMove();
	}
	else {
		NormalMove();
	}
}

void AnimatePlayer::IsHit(bool is_left, int damage)
{
	if (is_hit_count == 0) {
		is_hit_count = Timer::Get()->GetRunTime() + 2.0f;
		hit_point -= damage;
		move_speed = 0;
		if (is_left) {
			move_pos =7.0f;
		}
		else {
			move_pos = -7.0f;
		}
		jump_speed = 50.0f;

		if (hit_point <= 0) {
			is_live = false;
		}
	}

}

void AnimatePlayer::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[(UINT)action_status]->Render();
	//�׵θ� ��ǥ�ø� ���� ����ó��
	hit_collider->Render();
	if (!is_star) {
		foot_collider->Render();
	}
	if (attack_collider != NULL) {
		attack_collider->Render();
	}	
}

void AnimatePlayer::PostRender()
{
	ImGui::SliderFloat2("p.pos", (float*)&pos, -3000, 3000);	
	ImGui::SliderFloat("move_speed", (float*)&move_speed, -3000, 3000);
}

void AnimatePlayer::NormalMove()
{
	if (!is_live) {

	}
	if (action_status == CHAR_STATUS::HIT) {
		if (!clips[(UINT)action_status]->isPlay()) {
			clips[(UINT)action_status]->Play();
			SetClip(CHAR_STATUS::IDLE);
		}
	}

	if (pos.x > 2520) {
		pos.x -= 300.0f * DELTA;
	}
	if (pos.x < -1240) {
		pos.x += 300.0f * DELTA;
	}
	//���ӵ� ����
	if (action_status != CHAR_STATUS::ROPE) {
		jump_speed -= 9.8f * 20.0f * DELTA;
		if (jump_speed <= -250.0f) {
			jump_speed = -250.0f;
		}
		pos.y -= jump_speed * DELTA * 5.0f;
	}
	if (action_status != CHAR_STATUS::ROPE) {
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
	}

	//���帰 ���¿��� ������ �Ұ��ϹǷ� ���� ����
	if (action_status != CHAR_STATUS::PRONE) {
		//����Ű�� ����
		if (KEY_PRESS('C'))
		{
			if (action_status == CHAR_STATUS::ROPE) {
				if (!KEY_PRESS(VK_RIGHT) && !KEY_PRESS(VK_LEFT)) {
					return;
				}
			}
			//���� ���� ���°� �ƴ϶��
			if (action_status != CHAR_STATUS::JUMP && action_status != CHAR_STATUS::ATTACK && action_status != CHAR_STATUS::HIT) {
				//���� ���� ������ ����
				jump_speed = 100.0f;
				SetClip(CHAR_STATUS::JUMP);
			}
		}
	}
	//�����߿� ������ ����
	if (KEY_DOWN('C'))
	{
		if (action_status == CHAR_STATUS::JUMP && is_can_double_jump && action_status != CHAR_STATUS::ATTACK && action_status != CHAR_STATUS::HIT) {
			is_can_double_jump = false;
			if (jump_speed < 0) {
				jump_speed = 100.0f;
			}
			else {
				jump_speed += 100.0f;
			}
		}
	}
	if (action_status != CHAR_STATUS::PRONE && action_status != CHAR_STATUS::ROPE) {
		//����Ű�� ����
		if (KEY_PRESS('A'))
		{
			if (action_status == CHAR_STATUS::JUMP) {
				is_jump_attack = true;
			}
			if (action_status != CHAR_STATUS::ATTACK) {
				SetClip(CHAR_STATUS::ATTACK);
				if (attack_collider == NULL) {
					attack_collider = new ImageRect(L"Texture/Image/attack.png", Vector2(80, 100));
				}
			}
		}
	}
	if (action_status == CHAR_STATUS::ATTACK || action_status != CHAR_STATUS::HIT) {
		if (!clips[(UINT)CHAR_STATUS::ATTACK]->isPlay()) {
			clips[(UINT)CHAR_STATUS::ATTACK]->Play();
			SetClip(CHAR_STATUS::IDLE);
			is_jump_attack = false;
			if (attack_collider != NULL) {
				delete attack_collider;
				attack_collider = NULL;
			}
		}
	}

	//�����鼭 ������ �̵��� ���� ���·� ����
	if (jump_speed < -50.0f && action_status != CHAR_STATUS::ROPE && action_status != CHAR_STATUS::ATTACK && action_status != CHAR_STATUS::HIT) {
		SetClip(CHAR_STATUS::JUMP);
	}


	switch (action_status)
	{
	case AnimatePlayer::CHAR_STATUS::IDLE:
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
		if (KEY_PRESS(VK_DOWN)) {
			SetClip(CHAR_STATUS::PRONE);
		}
		break;
	case AnimatePlayer::CHAR_STATUS::WALK:
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
		if (!KEY_PRESS(VK_LEFT) && !KEY_PRESS(VK_RIGHT) && action_status != CHAR_STATUS::HIT) {
			SetClip(CHAR_STATUS::IDLE);
			move_pos = 0;
		}
		if (KEY_DOWN('C')) {
			SetClip(CHAR_STATUS::JUMP);
		}
		break;
	case AnimatePlayer::CHAR_STATUS::JUMP:
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
	case AnimatePlayer::CHAR_STATUS::PRONE:
		//���帰 ���¿��� �¿� �̵��� �̵� ���·� ����
		if (KEY_PRESS(VK_LEFT)) {
			move_pos = -10.0f;
			SetClip(CHAR_STATUS::WALK);
			is_looking_left = true;
		}
		if (KEY_PRESS(VK_RIGHT)) {
			move_pos = 10.0f;
			SetClip(CHAR_STATUS::WALK);
			is_looking_left = false;
		}
		if (!KEY_PRESS(VK_LEFT) && !KEY_PRESS(VK_RIGHT)) {
			move_pos = 0;
		}
		//���帰 �����϶� �Ʒ�Ű�� ������ ������ �����·� ����
		if (!KEY_PRESS(VK_DOWN)) {
			SetClip(CHAR_STATUS::IDLE);
		}
		break;
	case AnimatePlayer::CHAR_STATUS::RUN:
		break;
	case AnimatePlayer::CHAR_STATUS::ROPE:

		if (KEY_PRESS(VK_UP)) {
			pos.y -= 300.0f * DELTA;
			move_pos = 0.0f;
		}
		if (KEY_PRESS(VK_DOWN)) {
			pos.y += 300.0f * DELTA;
			move_pos = 0.0f;
		}
		if (KEY_PRESS(VK_LEFT)) {
			move_pos = -50.0f;
			move_speed = 50.0f;
		}
		if (KEY_PRESS(VK_RIGHT)) {
			move_pos = 50.0f;
			move_speed = -50.0f;
		}
		break;
	case AnimatePlayer::CHAR_STATUS::ATTACK:
		if (attack_collider != NULL) {
			attack_collider->pos = pos + Vector2(50, 0);
			attack_collider->GetCollider()->pos = pos + Vector2(50, 0);
			if (is_looking_left) {
				attack_collider->pos.x = pos.x - 50;
				attack_collider->GetCollider()->pos.x = pos.x - 50;
			}
			attack_collider->Update();
		}
		if (is_jump_attack) {
			if (move_pos < 0) {
				if (KEY_PRESS(VK_LEFT)) {
					move_pos = -25.0f;
					is_looking_left = true;
				}
			}
			if (move_pos > 0) {
				if (KEY_PRESS(VK_RIGHT)) {
					move_pos = 25.0f;
					is_looking_left = false;
				}
			}
		}
		else {
			move_pos = 0;
			move_speed = 0;
		}
		break;
	case AnimatePlayer::CHAR_STATUS::HIT:
		if (KEY_PRESS(VK_LEFT)) {
			if (move_speed < 0) {
				move_speed = 0.0f;
			}
			move_pos = -10.0f;
			is_looking_left = true;
		}
		if (KEY_PRESS(VK_RIGHT)) {
			if (move_speed > 0) {
				move_speed = 0.0f;
			}
			move_pos = 10.0f;
			is_looking_left = false;
		}
		if (!KEY_PRESS(VK_LEFT) && !KEY_PRESS(VK_RIGHT) && action_status != CHAR_STATUS::HIT) {
			move_pos = 0;
		}
		break;
	case AnimatePlayer::CHAR_STATUS::MAX:
		break;
	default:
		break;
	}
	hit_collider->pos = pos + Vector2(10, 0);
	foot_collider->pos = pos + Vector2(10, 50);
	clips[(UINT)action_status]->Update();
	scale = clips[(UINT)action_status]->GetFrameSize() * 1.5;
	if (is_looking_left) {
		scale.x *= -1;
		if (attack_collider != NULL) {
			attack_collider->GetCollider()->scale.x = -1;
		}

		hit_collider->pos.x = pos.x - 3;
		foot_collider->pos.x = pos.x - 3;
	}
	if (action_status == AnimatePlayer::CHAR_STATUS::ROPE) {
		hit_collider->pos.x = pos.x;
		foot_collider->pos.x = pos.x;
	}
	if (action_status == AnimatePlayer::CHAR_STATUS::IDLE) {
		if (KEY_PRESS(VK_UP)) {
			foot_collider->pos.y -= 1.0f;
		}
		if (KEY_PRESS(VK_DOWN)) {
			foot_collider->pos.y += 5.0f;
		}
	}
	if (action_status == AnimatePlayer::CHAR_STATUS::PRONE) {
		if (KEY_PRESS(VK_DOWN)) {
			foot_collider->pos.y += 5.0f;
		}
	}
	WorldUpdate();
	hit_collider->WorldUpdate();
	foot_collider->WorldUpdate();

	if (attack_collider != NULL) {
		attack_collider->Update();
	}
}

void AnimatePlayer::FlyMove()
{
	if (star_fail != 0) {
		if (star_fail < Timer::Get()->GetRunTime()) {
			star_fail = 0;
			move_pos = 0;
			move_speed = 0;
			moveup_pos = 0;
			moveup_speed = 0;
			SetClip(CHAR_STATUS::FLY);
			
		}
		clips[(UINT)action_status]->Update();
		WorldUpdate();
		return;
	}

	if (pos.x > 2800) {
		pos.x -= 500.0f * DELTA;
		move_pos = 0;
		move_speed = 0;
	}
	if (pos.x < -1100) {
		pos.x += 500.0f * DELTA;
		move_pos = 0;
		move_speed = 0;
	}

	if (pos.y < -1400) {
		pos.y += 500.0f * DELTA;
		moveup_pos = 0;
		moveup_speed = 0;
	}
	if (pos.y > 2850) {
		pos.y -= 500.0f * DELTA;
		moveup_pos = 0;
		moveup_speed = 0;
	}
	
	SetClip(CHAR_STATUS::FLY);
	if (KEY_PRESS(VK_UP)) {
		moveup_pos = -10.0f;
	}
	if (KEY_PRESS(VK_DOWN)) {
		moveup_pos = 10.0f;
	}
	if (KEY_PRESS(VK_LEFT)) {
		is_looking_left = true;
		move_pos = -10.0f;
	}
	if (KEY_PRESS(VK_RIGHT)) {
		is_looking_left = false;
		move_pos = 10.0f;
	}

	move_speed -= (9.8f * DELTA) * move_pos;
	moveup_speed -= (9.8f * DELTA) * moveup_pos;

	if (!KEY_PRESS(VK_UP) && !KEY_PRESS(VK_DOWN)) {
		moveup_pos = 0;
		if (moveup_speed > 0) {
			moveup_speed -= (9.8f * DELTA) * 20.0f;
		}
		else {
			moveup_speed += (9.8f * DELTA) * 20.0f;
		}
	}
	if (!KEY_PRESS(VK_LEFT) && !KEY_PRESS(VK_RIGHT)) {
		move_pos = 0;
		if (move_speed < 0) {
			move_speed += (9.8f * DELTA) * 20.0f;
		}
		else {
			move_speed -= (9.8f * DELTA) * 20.0f;
		}
	}

	if (move_speed < -100.0f) {
		move_speed = -100.0f;
	}
	if (move_speed > 100.0f) {
		move_speed = 100.0f;
	}
	if (moveup_speed < -100.0f) {
		moveup_speed = -100.0f;
	}
	if (moveup_speed > 100.0f) {
		moveup_speed = 100.0f;
	}
	pos.x -= move_speed * DELTA * 5.0f;
	pos.y -= moveup_speed * DELTA * 5.0f;

	clips[(UINT)action_status]->Update();
	scale = clips[(UINT)action_status]->GetFrameSize() * 1.5;
	hit_collider->scale = Vector2(3, 3);
	hit_collider->pos = pos + Vector2(0, 0);
	hit_collider->WorldUpdate();
	if (is_looking_left) {
		scale.x *= -1;
	}
	WorldUpdate();
}

void AnimatePlayer::RunningMove()
{
	
	if (KEY_PRESS(VK_F5)) {
		auto_move = true;
	}
	if (KEY_PRESS(VK_F6)) {
		auto_move = false;
	}
	//�����̵��� ���� �ӵ� ����
	if (auto_move) {
		move_speed = -70.0f;
		if (KEY_PRESS('A')) {
			move_speed = -100.0f;
		}
		pos.x -= move_speed * DELTA * 5.0f;
	}
	//���ӵ� ����
	if (action_status != CHAR_STATUS::ROPE) {
		jump_speed -= 9.8f * 30.0f * DELTA;
		if (jump_speed <= -250.0f) {
			jump_speed = -250.0f;
		}
		pos.y -= jump_speed * DELTA * 5.0f;
	}

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
	//�����߿� ������ ����
	if (KEY_DOWN('C'))
	{
		if (action_status == CHAR_STATUS::JUMP && is_can_double_jump) {
			is_can_double_jump = false;
			if (jump_speed < 0) {
				jump_speed = 80.0f;
			}
			else {
				jump_speed += 80.0f;
			}
		}
	}

	//�����鼭 ������ �̵��� ���� ���·� ����
	if (jump_speed < -100.0f) {
		SetClip(CHAR_STATUS::JUMP);
	}
	
	switch (action_status)
	{
	case AnimatePlayer::CHAR_STATUS::IDLE:
		if (KEY_DOWN('C')) {
			SetClip(CHAR_STATUS::JUMP);
		}
		if (KEY_PRESS(VK_DOWN)) {
			SetClip(CHAR_STATUS::PRONE);
		}
		break;
	case AnimatePlayer::CHAR_STATUS::WALK:
		if (KEY_DOWN('C')) {
			SetClip(CHAR_STATUS::JUMP);
		}
		if (KEY_PRESS(VK_DOWN)) {
			SetClip(CHAR_STATUS::PRONE);
		}
		break;
	case AnimatePlayer::CHAR_STATUS::JUMP:
		break;
	case AnimatePlayer::CHAR_STATUS::PRONE:
		//���帰 �����϶� �Ʒ�Ű�� ������ ������ �����·� ����
		if (!KEY_PRESS(VK_DOWN)) {
			SetClip(CHAR_STATUS::WALK);
		}
		break;
	case AnimatePlayer::CHAR_STATUS::RUN:
		break;
	case AnimatePlayer::CHAR_STATUS::ROPE:
		break;
	case AnimatePlayer::CHAR_STATUS::ATTACK:
		break;
	case AnimatePlayer::CHAR_STATUS::HIT:
		break;
	case AnimatePlayer::CHAR_STATUS::MAX:
		break;
	default:
		break;
	}
	hit_collider->pos = pos + Vector2(10, 0);
	foot_collider->pos = pos + Vector2(10, 50);
	clips[(UINT)action_status]->Update();
	scale = clips[(UINT)action_status]->GetFrameSize() * 1.5;
	if (action_status == AnimatePlayer::CHAR_STATUS::PRONE) {
		if (KEY_PRESS(VK_DOWN)) {
			hit_collider->pos.y += 40.0f;
		}
	}
	WorldUpdate();
	hit_collider->WorldUpdate();
	foot_collider->WorldUpdate();
}

void AnimatePlayer::StarFail()
{
	if (star_fail == 0) {
		star_fail = Timer::Get()->GetRunTime() + 2.0f;
		SetClip(CHAR_STATUS::FLY_STUN);
	}
}

void AnimatePlayer::SetClip(CHAR_STATUS stat)
//�� ������Ʈ�� ���� ���� ����ϰ� �ִ� �ִϸ��̼� Ŭ����
//�ٸ� �ִϸ��̼����� �ٲٸ鼭,���ÿ� �� �������� �ʿ������� ���� �Ǿ�� ��
//���� �۾����� ���� �����ϵ��� �ϴ� �Լ�
{
	if (stat == action_status) {
		//�� �Լ��� �Ű������� ���� ���°� �� ������Ʈ�� ���� ���¿� ���� �ϴٸ�
		//TODO:�ϴ��� �����
		return;//�ִϸ��̼� ������� �״�� �ڵ� ����
	}

	switch (stat)//������ ���µ��� ���� �߰� 
		//�����δ� �� �Լ��� ���� �������°� ������ �Ǹ�
		//�� ���¿� �°� �ִϸ��̼� �����۾��� �̷����� �� ��
	{
	case AnimatePlayer::CHAR_STATUS::IDLE://���ߴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::WALK://�ȴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::JUMP://�����ϴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::PRONE://���帮�� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::RUN://�޸��� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::ROPE://�޴޸����
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::ATTACK://���ݻ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::HIT://��Ʈ����
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::FLY://�ö��̻���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::FLY_STUN://�ö��̻���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	default:
		break;
	}
}