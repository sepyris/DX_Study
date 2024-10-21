#pragma once

class Mushroom : public Transform {
private:
	enum class CHAR_STATUS {
		IDLE = 0,
		WALK,
		JUMP,
		HIT,
		DEAD,
		MAX = 4
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
	bool is_moving_left = false;
	float move = 0;
	int ground_num = 0;
	bool is_dead = false;

	//Ÿ�̸� ���� ����
	float move_check = 0; // ���������ӱ��� ������ ���� Ÿ�̸�
	float zen_count = 0; // ����� �ٽ� ��������� ������ ���� Ÿ�̸�

	RectCollider* now_ground = NULL;

	//�޸���ʿ��� ��ֹ��� ����ϱ� ���� ���� ����
	bool is_running = false;


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
	void IsCreate();
	bool Islive() { return is_live;}
	void LoadingEnd() { loading_end = true; }
	void Setcollider(RectCollider* collider) { now_ground = collider; }
	void SetGroundNum(int num) { ground_num = num; }
	int GetGroundNum() { return ground_num; }
	void IsHit();

	void NormalMove();
	void RunningMove();

	void SetRunning() {
		is_running = true;
	}


	void SetColor(Float4 color) {
		CB->data.colour = color;
	}

	void SetClip(CHAR_STATUS stat);

};