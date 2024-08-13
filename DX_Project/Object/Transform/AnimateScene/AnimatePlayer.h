#pragma once

class AnimatePlayer : public Transform {
private:
	enum class CHAR_STATUS {
		IDLE = 0,
		//이는 벡터의 인덱스의 역할도 할수 있다.
		//만약 하나의 상태에 하나의 애니메이션만 할당이 되어있다면
		//이 열거형을 가지는 변수의 값을 곧바로 전체 Clips의 인덱스로 사용하는것으로서
		//우리가 원하는 애니메이션을 쓸수 있게 된다.

		WALK,
		JUMP,
		PRONE,
		RUN,
		ROPE,
		ATTACK,
		MAX = 7//마지막에 MAX를 넣는것으로
		//이 MAX를 호출해 그 값을 확인 함으로서
		//이 열거형에 총 몇개의 데이터가 들어가 있는지를 확인할수 있다.
	}action_status;

	//캐릭터의 현재 상태를 정의 하는 열거형 클래스
	//그리고 그 열거형 클래스의 멤버를 만드는것

	/*
	유한 상태 머신
	상태라는 개념을 만들어두면
	이후에 같은 명령이 들어온다 하더라도 현재 상태에 따라서 서로 다른 작업 혹은 결과물을 내도록 하는 식으로
	프로그램을 구성하는 디자인 패턴을 유한 상태 머신 이라고 부름


	*/

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	vector<Clip*> clips;
	//애니메이션에 사용될 스프라이트들
	//정확히는 그 스프라이트들을 통해서 만들어낸 각각의 애니메이션을
	//저장하는 자료구조

	RectCollider* hit_collider;
	RectCollider* foot_collider;
	RectCollider* attack_collider;

	bool is_looking_left;

	UINT clip_cursor;

	float jump_speed;
	float jump_height;
	float init_jump_pos;

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


/*
*점프기능구현
 화면 아래를 기준으로 했을때 y축으로 일시적으로 올라갔다가 내려오게 하는 기능
 이를 위해선 점프라는 최대 높이와 착지 를 정의할 필요가 있다

 점프하는 높이는 최대 높이를 정하는걸로 취급하는게 아니라
 점프하는 순간 얼마나 강한 힘(=초기 속도)으로 점프했는지를 지정한 뒤
 중력 가속도를 받아 점차 올라가는 속도가 느려지게 하다가 결국은 떨어지게 하는 식

 착지의 경우 위와는 다르게 정의하기가 좀 난감
 일단 무언가 바닥에 닿아서 더이상 떨어지지 않는 상태로 정의 하는것도 가능
  어떤것과 충돌 했는지 따지는것은 그냥 Scene그 자체에서 충돌 처리를 검사할때
  어떤 오브젝트끼리 충돌 했는지 관리하여 검사하면 그만이므로
  충돌한 오브젝트가 무엇인가를 판별하는 작업은 고려하지 않아도 됨

  단,애초에 이 방법을 쓰려면 "다른 오브젝트" 자체를 구현해야함
  따라서 발판 역할을 할 무언가를 만들어야 함

 그외에도 일정 좌표에 도달하게 되면 착지한것으로 판단 하는것도 가능
  이 방식은 구성한 맵에 따라서 그 값을 조정해야 하는 경우가 생기기도 하고,
  무엇보다 추락사 를 구현할수 없음
 아니면 초기 위치에서 얼마나 높이 올라갔었는지 판단 하는 방식으로도 가능
  이 방식은 추락 자체를 구현할 수 없다.

*발판등에 올라가는 기능 + 피격 기능
 이것들은 전부 피격 판정에 맞게 만들어져야 하므로,
 자연적으로 충돌처리를 구현해야 함
*공격 기능 구현
 공격 그자체의 매커니즘과 공격을 위해 만들어야 할 새로운 오브젝트 등의 구성에 걸리는 시간이 많은 탓에
 시간이 오래 걸릴수 밖에 없음
 일단 적이라는 개념이 만들어져있어야 공격이 의미를 가지므로
  필연적으로 적을 만든뒤에 우선순위가 밀릴수밖에 없다

*/