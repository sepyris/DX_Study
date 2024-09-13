#include "framework.h"

Timer::Timer()
	:frame_rate(0),
	frame_count(0),
	time_elapsed(0),
	one_sec_count(0),
	run_time(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&period_frequency);
	//기본적으로 winmain함수는 굉장히 빠른속도로 반복되고 있음
	// //그 반복되는 횟수가 초당 얼마인지를 확인,
	// 매개변수를 입력받은 포인터에 저장
	// 현재 컴퓨터의 사양이 메인루프를 초당 몇번 돌릴수 있는지 검사하는 함수
	QueryPerformanceCounter((LARGE_INTEGER*)&last_time);
	//성능 카운터가 현재 가지고 있는값을 저장하는 함수
	// 성능카운터:
	// 어떤 시점을 기준으로(컴퓨터가 켜진 시간부터일 것으로 추정)
	// CPU가 동작한 횟수를 기록한 것, 즉 CPU가 뭔가 작업을 한 횟수
	//->시스템상으로 기록된 현재 시각을 받아오는 함수
	time_scale = 1.0f / (float)period_frequency;
	//long long int인 period_frequency를 1초에서 나누는것으로
	//한개의 카운터가 대력적으로 0.몇초인지를 여기서 계산해 저장
	//이를 통해서 총 몇개의 카운트가 경과 했을때
	//실제로는 시간이 얼마나 지난것인지를 실제 시간으로서 처리하게 해주는
	//이정표 역할
}

Timer::~Timer()
{
}

void Timer::Update()
{
	//현재시각 저장
	QueryPerformanceCounter((LARGE_INTEGER*)&cur_time);
	
	//마지막으로 기록된 성능카운터를 현재 시점의 성능카운터에서 빼고
	//그렇게 구한 카운터의 변동치에 timescale를 곱해 실제 경과된 시간을 체크
	time_elapsed = (float)(cur_time - last_time) * time_scale;
	if (time_elapsed > 0.016f) {
		time_elapsed = 0.016f;
	}
	
	//여기까지 계산 했으면 과거 시각은 더이상 필요없으니 덮어 씌우기
	last_time = cur_time;

	frame_count++;
	//1초당 총 몇번의 작업이 진행되었는지 체크

	one_sec_count += time_elapsed;

	//총 1초가 경과 되었나 확인
	if (one_sec_count > 1.0f) {
		frame_rate = frame_count;
		one_sec_count -= 1.0f;
		frame_count = 0;
		//1초가 경과 되었다면 현 시점의 초당 프레임 레이트를 갱신,
		//연산에 사용된 값들을 초기화 내지는 정정
	}

	run_time += time_elapsed;
	//이번 업데이트에 걸린 총 시간을 run_time에 누적기록

}

