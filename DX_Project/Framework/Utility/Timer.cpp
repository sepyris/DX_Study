#include "framework.h"

Timer::Timer()
	:frame_rate(0),
	frame_count(0),
	time_elapsed(0),
	one_sec_count(0),
	run_time(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&period_frequency);
	//�⺻������ winmain�Լ��� ������ �����ӵ��� �ݺ��ǰ� ����
	// //�� �ݺ��Ǵ� Ƚ���� �ʴ� �������� Ȯ��,
	// �Ű������� �Է¹��� �����Ϳ� ����
	// ���� ��ǻ���� ����� ���η����� �ʴ� ��� ������ �ִ��� �˻��ϴ� �Լ�
	QueryPerformanceCounter((LARGE_INTEGER*)&last_time);
	//���� ī���Ͱ� ���� ������ �ִ°��� �����ϴ� �Լ�
	// ����ī����:
	// � ������ ��������(��ǻ�Ͱ� ���� �ð������� ������ ����)
	// CPU�� ������ Ƚ���� ����� ��, �� CPU�� ���� �۾��� �� Ƚ��
	//->�ý��ۻ����� ��ϵ� ���� �ð��� �޾ƿ��� �Լ�
	time_scale = 1.0f / (float)period_frequency;
	//long long int�� period_frequency�� 1�ʿ��� �����°�����
	//�Ѱ��� ī���Ͱ� ��������� 0.���������� ���⼭ ����� ����
	//�̸� ���ؼ� �� ��� ī��Ʈ�� ��� ������
	//�����δ� �ð��� �󸶳� ������������ ���� �ð����μ� ó���ϰ� ���ִ�
	//����ǥ ����
}

Timer::~Timer()
{
}

void Timer::Update()
{
	//����ð� ����
	QueryPerformanceCounter((LARGE_INTEGER*)&cur_time);
	
	//���������� ��ϵ� ����ī���͸� ���� ������ ����ī���Ϳ��� ����
	//�׷��� ���� ī������ ����ġ�� timescale�� ���� ���� ����� �ð��� üũ
	time_elapsed = (float)(cur_time - last_time) * time_scale;
	if (time_elapsed > 0.016f) {
		time_elapsed = 0.016f;
	}
	
	//������� ��� ������ ���� �ð��� ���̻� �ʿ������ ���� �����
	last_time = cur_time;

	frame_count++;
	//1�ʴ� �� ����� �۾��� ����Ǿ����� üũ

	one_sec_count += time_elapsed;

	//�� 1�ʰ� ��� �Ǿ��� Ȯ��
	if (one_sec_count > 1.0f) {
		frame_rate = frame_count;
		one_sec_count -= 1.0f;
		frame_count = 0;
		//1�ʰ� ��� �Ǿ��ٸ� �� ������ �ʴ� ������ ����Ʈ�� ����,
		//���꿡 ���� ������ �ʱ�ȭ ������ ����
	}

	run_time += time_elapsed;
	//�̹� ������Ʈ�� �ɸ� �� �ð��� run_time�� �������

}

