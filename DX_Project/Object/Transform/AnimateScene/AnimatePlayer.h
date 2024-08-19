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
		FLY,
		MAX = 8
	}action_status;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	vector<Clip*> clips;

	RectCollider* hit_collider;
	RectCollider* foot_collider;
	RectCollider* attack_collider;

	bool is_looking_left;

	UINT clip_cursor;

	float jump_speed;
	float jump_height;
	float init_jump_pos;
	float move_speed;
	float move_pos;

	float hit_point;

	bool is_can_double_jump;
	bool is_jump_attack;

public:
	AnimatePlayer(wstring file);
	~AnimatePlayer();

	void landing();
	void ResetJumpSpeed();
	bool IsHanging();
	void SetIdle();

	RectCollider* GetCollider() { return foot_collider; }
	void Update();
	void Render();
	void PostRender();

	void SetColor(Float4 color) {
		CB->data.colour = color;
	}

	void SetClip(CHAR_STATUS stat);
};