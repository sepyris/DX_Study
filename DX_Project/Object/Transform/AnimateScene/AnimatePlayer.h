#pragma once

class AnimatePlayer : public Transform {
private:
	enum class CHAR_STATUS {
		IDLE = 0,
		WALK,
		JUMP,
		PRONE,
		RUN,
		ROPE,
		ATTACK,
		HIT,
		FLY,
		FLY_STUN,
		MAX = 10
	}action_status;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	vector<Clip*> clips;

	RectCollider* hit_collider;
	RectCollider* foot_collider;
	ImageRect* attack_collider;

	bool is_looking_left;

	UINT clip_cursor;

	float jump_speed;
	float jump_height;
	float init_jump_pos;
	float move_speed;
	float move_pos;

	float moveup_speed;
	float moveup_pos;

	float hit_point;

	bool is_can_double_jump;
	bool is_jump_attack;
	bool loading_end = false;
	bool is_live = true;

	bool is_star = false;
	bool is_running = false;

	//타이머 설정 변수
	float is_hit_count = 0; // 피격 설정 타이머
	float star_fail = 0; // 다음움직임까지 설정을 위한 타이머
	float loading_time = 0;
	bool hit_check = false;

	//디버그 변수
	bool auto_move = true;

public:
	AnimatePlayer(wstring file);
	~AnimatePlayer();

	void landing();
	void ResetJumpSpeed();
	bool IsHanging();
	void SetIdle();

	RectCollider* GetCollider() { return foot_collider; }
	RectCollider* GetHitCollider() { return hit_collider; }
	RectCollider* GetAtkCollider() { 
		if (attack_collider != NULL) {
			return attack_collider->GetCollider();
		}
		else {
			return NULL;
		}
	}
	void Update();
	void Render();
	void PostRender();
	void LoadingEnd();

	void NormalMove();
	void FlyMove();
	void RunningMove();

	void StarFail();
	bool IsStarFail() {
		if (star_fail == 0) {
			return false;
		}
		else {
			return true;
		}
	}


	void IsHit(bool is_left,int damage = 1);



	void SetNormal() {
		is_star = false;
		is_running = true;
		is_can_double_jump = false;
	}

	void SetStar() { 
		is_star = true;
	}

	void SetRunning() {
		SetClip(CHAR_STATUS::WALK);
		hit_point = 300;
		is_running = true;
		is_can_double_jump = true;
	}
	int GetHealth() { return hit_point; }

	bool IsHitting() {
		if (is_hit_count != 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void SetColor(Float4 color) {
		CB->data.colour = color;
	}

	void SetClip(CHAR_STATUS stat);
};