#pragma once
#define KEY_MAX 256
// 일반적인 키보드의 키는 많아봐야 108개
// -> 255개의 값이면 그걸 절반으로 나눈 128개 데이터의 영역 2개로서
// 키를 표현할 수 있음

class Control : public Singleton<Control>
{
private:
	friend class Singleton;

	enum{
		NONE,
		DOWN,
		UP,
		PRESS,
		MAX
	};
	// 특정 키의 현재 상태를 의미
	// 위에서부터 "누르지 않음"/"지금 막 눌림"/"지금 막 떼짐"/"지금 눌려있음"
	// 추가로 MAX는 이 열거형에 최대 몇 개의 데이터가 들어있는지를 
	// 체크하기 위한 더미

	// 이하의 3개는 각각 키보드의 각 키가
	BYTE cur_state[KEY_MAX]; // 현재 눌려있는지를 저장할 배열
	BYTE old_state[KEY_MAX]; // 직전 타이밍에 눌려있었는지를 저장할 배열
	BYTE map_state[KEY_MAX]; // 위 2개의 정보를 조합해서
	// 최종적으로 각 키의 현재 버젼이 무엇인지를 결정 및 저장하는 배열

	// 위 배열들은 각각의 키가 입력되었는지의 여부를 판단할 때
	// 사용할 비트 플래그들
	// 단, 총 108개 이상의 키를 인식할 예정 = 키보드의 모든 값을 여기서 처리

	Control();
	~Control();

public:
	void Update();

	bool Down(UINT key) { return map_state[key] == DOWN; }
	bool Up(UINT key) { return map_state[key] == UP; }
	bool Press(UINT key) { return map_state[key] == PRESS; }
};
// 프로그램에서 키보드, 마우스 등의 입력장치 데이터를 관리하는 매니저