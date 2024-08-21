#pragma once

class Snail : public Transform {
private:
	enum class CHAR_STATUS {
		IDLE = 0,
		WALK,
		MAX = 2
	}action_status;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	vector<Clip*> clips;

	RectCollider* hit_collider;
	RectCollider* foot_collider;
	RectCollider* now_ground;

	UINT clip_cursor;

	bool is_looking_left;
	float jump_speed;
	float jump_height;
	float move_speed;
	float move_pos;
	float hit_point;
	bool is_live;
	bool loading_end = false;
	float move_check;
	bool is_moving = false;
	float move = 0;

public:
	Snail(wstring file);
	~Snail();

	void landing();
	void ResetJumpSpeed();

	RectCollider* GetCollider() { return foot_collider; }
	RectCollider* GetHitCollider() { return hit_collider; }
	void Update();
	void Render();
	void PostRender();
	void IsCreate() { is_live = true; }
	bool Islive() { return is_live; }
	void IsDead() { is_live = false; }
	void LoadingEnd() { loading_end = true; }
	void Setcollider(RectCollider* collider) { now_ground = collider;}

	void SetColor(Float4 color) {
		CB->data.colour = color;
	}

	void SetClip(CHAR_STATUS stat);

};