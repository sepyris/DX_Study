#pragma once

class Mushroom : public Transform {
private:
	enum class CHAR_STATUS {
		IDLE = 0,
		WALK,
		JUMP,
		MAX = 3
	}action_status;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	vector<Clip*> clips;

	RectCollider* hit_collider;
	RectCollider* foot_collider;

	UINT clip_cursor;


	bool is_looking_left;
	float jump_speed;
	float jump_height;
	float move_speed;
	float move_pos;
	float hit_point;
	bool is_live;
	bool loading_end = false;

public:
	Mushroom(wstring file);
	~Mushroom();

	void landing();
	void ResetJumpSpeed();

	RectCollider* GetCollider() { return foot_collider; }
	RectCollider* GetHitCollider() { return hit_collider; }
	void Update();
	void Render();
	void PostRender();
	void IsCreate() { is_live = true; }
	bool Islive() { return is_live;}
	void IsDead() { is_live = false; }
	void LoadingEnd() { loading_end = true; }

	void SetColor(Float4 color) {
		CB->data.colour = color;
	}

	void SetClip(CHAR_STATUS stat);

};