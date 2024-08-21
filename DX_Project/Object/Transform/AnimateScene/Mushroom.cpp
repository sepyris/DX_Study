#include "framework.h"

Mushroom::Mushroom(wstring file)
{
	Texture* t = Texture::Add(file);
	//파일명을 이용해 실제이미지 파일을 Texture로서 로딩

	//그렇게 로딩된 이미지에서어느 부분을 사용할것인지 결정하는 변수들을 정의
	
	vector<Frame*> frames;
	

	//대기 CHAR_STATUS::IDLE
	Vector2 init_pos = { 6,4 };
	Vector2 this_frame_size = { 63,58 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos = { 72,6 };
	this_frame_size = { 63,55 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//대기 상태 끝

	//워크 CHAR_STATUS::WALK
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
	//워크상태 끝

	//점프 CHAR_STATUS::JUMP
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
	//점프 상태 끝

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
		//소수점 6자리 수준까지의 정밀도로 실시간 좌표처리가 이워지는 이상
		// 벽을 긁으면서 점프할 경우 충돌하는 영역이 가로가 세로보다 커지는 상황은
		// 분명히 발생할수 있음
		//땅에 착지시에 점프 상태를 변경
		jump_speed = 0;
		pos.y += jump_speed * DELTA * 5.0f;
		SetClip(CHAR_STATUS::IDLE);
		move_pos = 0;
	}
}

void Mushroom::ResetJumpSpeed()
{
	//구조물에 머리를 박았을때
	//위로 올라가는중이라면 올라가지 못하게 설정
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
	//중력 적용
	if (loading_end) {
		jump_speed -= 9.8f * 20.0f * DELTA;
		if (jump_speed <= -250.0f) {
			jump_speed = -250.0f;
		}
		pos.y -= jump_speed * DELTA * 5.0f;
	}
	//이동 관성 적용
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
	hit_collider->pos = pos + Vector2(0, 0);
	foot_collider->pos = pos + Vector2(0, 40);
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
	//테두리 비표시를 위해 각주처리
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
	case Mushroom::CHAR_STATUS::IDLE://멈추는 상태가 될 경우
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case Mushroom::CHAR_STATUS::WALK://걷는 상태가 될 경우
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case Mushroom::CHAR_STATUS::JUMP://점프하는 상태가 될 경우
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	default:
		break;
	}
}
