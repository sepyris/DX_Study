#pragma once
//시간과 관련된 내용들을 담당하는 유틸리티 클래스

class Timer : public Singleton<Timer> {

public:
	friend class Singleton;

	float time_scale; //1초를 표한하는데 필요한 성능 카운터
	float time_elapsed;//경과시간을 체크및 기록하는 멤버변수

	//아래의 2개 변수는 타임 스탬프로 사용할 변수
	//__int64:이 자료형은 64비트짜리 정수, 즉 long long int를 의미
	__int64 cur_time;
	__int64 last_time;
	__int64 period_frequency;
	//현재 컴퓨터의 사양이 메인루프를 몇번 돌릴수 있는지를 저장하는 멤버
	// 기본적으로 컴퓨터의 사양에 따라서 프로그램의 메인루프가 돌아가는 속도가 달라
	// 사양의 좋고 나쁨에 따라 초당 실행되는 횟수가 달라지기 마련
	// 이를 제어하기 위해,한번 메인루프가 전부 실행되는데 시간이 얼마나 걸리는지
	// 이 period_frequency변수쪽에 기록해둬서 최종적인 횟수에 대하여 보정을 거침
	//


	int frame_rate;//FPS
	int frame_count;//프로그램 시작후 경과된 프레임의 개수

	float one_sec_count; //1초가 지났는지의 여부를 저장하는 변수
	float run_time;//프로그램이 실행되기 시작한 후 부터 기록을 시작하는 프로그램의 총 가동 시간

	Timer();
	~Timer();

	void Update();

	int GetFPS() { return frame_rate; }
	float GetDeltaTime() { return time_elapsed; }
	//이 함수가 실질적은 시간 처리를 담당하는 구문으로
	// 매크로문을 통해 DELTA라는 이름으로 이 함수에 빠르게 접근하도록 만듬
	//
	//앞으로 오브젝트등을 움직이는등 시간에 따라서 작동하도록 할 내용들은
	// 1초동안 작동하고자 의도한 값 * DELTA라고 쓰는식으로
	// 작동하는 속도를 관리하게 될것
	//
	float GetRunTime() { return run_time; }
	

};