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

	UINT clip_cursor;

	bool is_looking_left;
	float jump_speed;
	float jump_height;
	float move_speed;
	float move_pos;
	float hit_point;

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

	void SetColor(Float4 color) {
		CB->data.colour = color;
	}

	void SetClip(CHAR_STATUS stat);

};