#include "framework.h"

AnimatePlayer::AnimatePlayer(wstring file)
{
	Texture* t = Texture::Add(file);
	//파일명을 이용해 실제이미지 파일을 Texture로서 로딩

	//그렇게 로딩된 이미지에서어느 부분을 사용할것인지 결정하는 변수들을 정의
	Vector2 init_pos = { 3,5 };
	//이미지의 어느 좌표부터 사용할것인지
	Vector2 this_frame_size = { 82,78 };
	//사용할 스프라이트의 크기가 얼마인지

	//Clips에 저장할 애니메이션을 만들기 위해 미리 만들어두는 프레임 모음집을 만들어둠
	vector<Frame*> frames;

	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos += Vector2(88, 0);

	//대기 CHAR_STATUS::IDLE
	for (int i = 0; i < 4; i++) {
		frames.push_back(
			new Frame(
				file,
				init_pos.x + i * (this_frame_size.x + 6),
				init_pos.y,
				this_frame_size.x,
				this_frame_size.y
			));
		//frame의 이 생성자는
		//사용할 file에서 앞에 2개의 x,y 좌표부터 시작해
		//뒤쪽 2개의 a,b값만큼의 가로/세로 범위만큼의 영역을 지정,
		//이미지 파일의 해당 영역만을 이용하여
		//애니메이션의 한 프레임을 만들어내는 생성자
	}

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	//이 함수는 어디까지나 이벡터에 저장하고 있던 주소들만을 지울뿐이지 할당 해제까지는 하지 않음
	//그래서 이렇게 clear를 이용해도 frames안에 들어있던 프레임들은 유지됨
	//이를 이용해서 안심하고 비우고 다음애니메이션을 추가하는 작업을 하면 된다.
	frames.clear();
	//대기 상태 끝

	//워크 CHAR_STATUS::WALK
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
		//frame의 이 생성자는
		//사용할 file에서 앞에 2개의 x,y 좌표부터 시작해
		//뒤쪽 2개의 a,b값만큼의 가로/세로 범위만큼의 영역을 지정,
		//이미지 파일의 해당 영역만을 이용하여
		//애니메이션의 한 프레임을 만들어내는 생성자
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//워크 상태 끝

	//점프 CHAR_STATUS::JUMP
	init_pos = { 3,181 };
	this_frame_size = { 82,78 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP));
	frames.clear();
	//점프 상태 끝

	//엎드리기 CHAR_STATUS::PRONE
	init_pos = { 3,262 };
	this_frame_size = { 117,84 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP));
	frames.clear();
	//엎드리기 상태 끝

	//달리기 CHAR_STATUS::RUN
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
		//frame의 이 생성자는
		//사용할 file에서 앞에 2개의 x,y 좌표부터 시작해
		//뒤쪽 2개의 a,b값만큼의 가로/세로 범위만큼의 영역을 지정,
		//이미지 파일의 해당 영역만을 이용하여
		//애니메이션의 한 프레임을 만들어내는 생성자
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//달리기 상태 끝

	//메달리기 CHAR_STATUS::ROPE
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
		//frame의 이 생성자는
		//사용할 file에서 앞에 2개의 x,y 좌표부터 시작해
		//뒤쪽 2개의 a,b값만큼의 가로/세로 범위만큼의 영역을 지정,
		//이미지 파일의 해당 영역만을 이용하여
		//애니메이션의 한 프레임을 만들어내는 생성자
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//메달리기 상태 끝

	//공격 CHAR_STATUS::ATTACK
	init_pos = { 2,441 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));

	init_pos += Vector2(84, 0);
	for (int i = 0; i < 2; i++) {
		frames.push_back(
			new Frame(
				file,
				init_pos.x + i * (this_frame_size.x + 6),
				init_pos.y,
				this_frame_size.x,
				this_frame_size.y
			));
		//frame의 이 생성자는
		//사용할 file에서 앞에 2개의 x,y 좌표부터 시작해
		//뒤쪽 2개의 a,b값만큼의 가로/세로 범위만큼의 영역을 지정,
		//이미지 파일의 해당 영역만을 이용하여
		//애니메이션의 한 프레임을 만들어내는 생성자
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 0.15f));
	frames.clear();
	//공격 상태 끝

	//히트 CHAR_STATUS::HIT
	init_pos = { 3,181 };
	this_frame_size = { 82,78 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	init_pos = { 3,5 };
	this_frame_size = { 82,78 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 0.5f));
	frames.clear();
	//히트 상태 끝

	//플라이 CHAR_STATUS::FLY
	init_pos = { 3,181 };
	this_frame_size = { 82,78 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 0.5f));
	frames.clear();
	//플라이 상태 끝

	VS = new VertexShader(L"Shader/VertexShader/VertexShaderUV.hlsl", 2);
	PS = new PixelShader(L"Shader/PixelShader/PixelShaderUv.hlsl");

	CB = new ColourBuffer();

	//collider = new RectCollider(clips[(UINT)action_status]->GetFrameOrigSize() * 3.0f);
	//충돌 판정의 크기를 잡는법은 몇가지가 있음
	//1)사용하는 스프라이트 자체의 크기를 가져와서 적용 시키는것
	//그러나 이는 사용하는 스프라이트가
	// 딱 사용할 영역만 가져오는식으로 이뤄졌을대만 가능하고
	// 프레임 추가의 용이성을 위해 배경까지 전부 가져온 경우는
	// 실제 스프라이트와 프레임의 크기 가 불일치 하기때문에 제대로 잡히지 않음
	// 
	//2)노가다
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
		//소수점 6자리 수준까지의 정밀도로 실시간 좌표처리가 이워지는 이상
		// 벽을 긁으면서 점프할 경우 충돌하는 영역이 가로가 세로보다 커지는 상황은
		// 분명히 발생할수 있음
		//땅에 착지시에 점프 상태를 변경
		jump_speed = 0;
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
			SetClip(CHAR_STATUS::IDLE);
			is_can_double_jump = false;
			move_pos = 0;
		}
	}
}

void AnimatePlayer::ResetJumpSpeed()
{
	//구조물에 머리를 박았을때
	//위로 올라가는중이라면 올라가지 못하게 설정
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
	if (is_star) {
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
		if (!KEY_PRESS(VK_UP) && !KEY_PRESS(VK_DOWN)) {
			moveup_pos = 0;
		}
		if (!KEY_PRESS(VK_LEFT) && !KEY_PRESS(VK_RIGHT)) {
			move_pos = 0;
		}
		if (loading_end) {
			move_speed -= 9.8f * move_pos * DELTA;
			moveup_speed -= 9.8f * moveup_pos * DELTA;
			if (move_speed < -50.0f) {
				move_speed = -50.0f;
			}
			if (move_speed > 50.0f) {
				move_speed = 50.0f;
			}
			if (moveup_speed < -70.0f) {
				moveup_speed = -70.0f;
			}
			if (moveup_speed > 70.0f) {
				moveup_speed = 70.0f;
			}
			pos.x -= move_speed * DELTA * 5.0f;
			pos.y -= moveup_speed * DELTA * 5.0f;
		}

		clips[(UINT)action_status]->Update();
		scale = clips[(UINT)action_status]->GetFrameSize() * 1.5;
		hit_collider->scale = Vector2(3, 3);
		hit_collider->pos = pos + Vector2(0, 0);
		hit_collider->WorldUpdate();
		if (is_looking_left) {
			scale.x *= -1;
		}
		WorldUpdate();
		return;
	}

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
	//가속도 설정
	if (loading_end) {
		if (action_status != CHAR_STATUS::ROPE) {
			jump_speed -= 9.8f * 20.0f * DELTA;
			if (jump_speed <= -250.0f) {
				jump_speed = -250.0f;
			}
			pos.y -= jump_speed * DELTA * 5.0f;
		}
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
			else if(move_speed < 0.0f) {
				move_speed += 9.8f * DELTA * 20.0f;
			}
		}
		pos.x -= move_speed * DELTA*5.0f;
	}
	
	
	//엎드린 상태에서 점프가 불가하므로 조건 설정
	if (action_status != CHAR_STATUS::PRONE) {
		//점프키를 누름
		if (KEY_PRESS('C'))
		{
			if (action_status == CHAR_STATUS::ROPE) {
				if (!KEY_PRESS(VK_RIGHT) && !KEY_PRESS(VK_LEFT)) {
					return;
				}
			}
			//만약 점프 상태가 아니라면
			if (action_status != CHAR_STATUS::JUMP &&action_status != CHAR_STATUS::ATTACK && action_status != CHAR_STATUS::HIT) {
				//점프 관련 설정을 변경
				jump_speed = 100.0f;
				SetClip(CHAR_STATUS::JUMP);
			}
		}
	}
	//점프중에 점프를 누름
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
		//공격키를 누름
		if (KEY_DOWN('A'))
		{
			if (action_status == CHAR_STATUS::JUMP) {
				is_jump_attack = true;
			}
			SetClip(CHAR_STATUS::ATTACK);
			if (attack_collider == NULL) {
				attack_collider = new ImageRect(L"Texture/Image/attack.png",Vector2(80,100));
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

	//걸으면서 단차로 이동시 점프 상태로 변경
	if (jump_speed < -10.0f && action_status != CHAR_STATUS::ROPE && action_status != CHAR_STATUS::ATTACK && action_status != CHAR_STATUS::HIT) {
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
		//점프 상태일때 좌우 키를 누를시 좌우로 이동
		//단 모션은 변경 없음
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
		//엎드린 상태에서 좌우 이동시 이동 상태로 변경
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
		if (KEY_PRESS(VK_DOWN)) {
			foot_collider->pos.y += 5.0f;
		}
		else {
			foot_collider->pos.y = pos.y;
		}
		if (!KEY_PRESS(VK_LEFT) && !KEY_PRESS(VK_RIGHT)) {
			move_pos = 0;
		}
		//엎드린 상태일때 아래키를 누르지 않으면 대기상태로 변경
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
	case AnimatePlayer::CHAR_STATUS::HIT: {
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
			foot_collider->pos.y += 1.0f;
		}
		if (KEY_PRESS(VK_DOWN)) {
			foot_collider->pos.y -= 3.0f;
		}
	}
	if (action_status == AnimatePlayer::CHAR_STATUS::PRONE) {
		if (KEY_PRESS(VK_DOWN)) {
			foot_collider->pos.y -= 3.0f;
		}
	}


	WorldUpdate();
	hit_collider->WorldUpdate();
	foot_collider->WorldUpdate();

	if (attack_collider != NULL) {
		attack_collider->Update();
	}
}

void AnimatePlayer::IsHit(bool is_left)
{
	if (action_status != CHAR_STATUS::HIT) {
		hit_point--;
		move_speed = 0;
		if (is_left) {
			move_pos =7.0f;
		}
		else {
			move_pos = -7.0f;
		}
		jump_speed = 50.0f;

		SetClip(CHAR_STATUS::HIT);
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
	//테두리 비표시를 위해 각주처리
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
}

void AnimatePlayer::SetClip(CHAR_STATUS stat)
//이 오브젝트가 지금 당장 출력하고 있는 애니메이션 클립을
//다른 애니메이션으로 바꾸면서,동시에 그 과정에서 필연적으로 진행 되어야 할
//여러 작업들을 같이 수행하도록 하는 함수
{
	if (stat == action_status) {
		//이 함수가 매개변수로 받은 상태가 이 오브젝트의 현재 상태와 동일 하다면
		//TODO:일단은 비워둠
		return;//애니메이션 변경없이 그대로 코드 종료
	}

	switch (stat)//가능한 상태들을 전부 추가 
		//앞으로는 이 함수를 통해 다음상태가 들어오게 되면
		//그 상태에 맞게 애니메이션 변경작업이 이뤄지게 될 것
	{
	case AnimatePlayer::CHAR_STATUS::IDLE://멈추는 상태가 될 경우
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::WALK://걷는 상태가 될 경우
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::JUMP://점프하는 상태가 될 경우
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::PRONE://엎드리는 상태가 될 경우
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::RUN://달리기 상태가 될 경우
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::ROPE://메달릴경우
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::ATTACK://공격상태
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::HIT://히트상태
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case AnimatePlayer::CHAR_STATUS::FLY://플라이상태
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	default:
		break;
	}
}
