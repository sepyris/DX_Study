#pragma once
// Clip : ������ ���� ������ ��ü���� �ִϸ��̼��� ����ϴ� Ŭ����
// ���� �ǹ�(ª�� �߶� ����)ó��, 
// �ִϸ��̼� �ϳ��ϳ��� ª���� �� ª�� �ִϸ��̼��� ���� �����ϴ� �뵵

//Texture >> Frame >> CLIP ������ �����ؾ��� �ʿ䰡 ����(��Ӱ���X)
class Clip
{
public:
	enum class CLIP_TYPE
	{
		END, LOOP, PINGPONG
	};
	// �� Ŭ���� �����ϰ� �ִ� �̹�������
	// � ������� ����� ������ ��Ÿ���� ������
	// = �� �ִϸ��̼��� � �ִϸ��̼������� ��Ÿ���� ��
	// 
	// END :  �� �� ����� ������ �״�� ��
	// (������ �������� ���� ����Ʈ ���� ��ǥ��)
	// 
	// LOOP : �� �� ����� ������ ó�� ���������� ���ƿͼ� ����� �ݺ�
	// 
	// PINGPONG : �� �� ����� ������ ������ �����Ӻ��� �������� ����ϰ�,
	//			  ó�� �����ӱ��� ����� ������ �ٽ� ó������ ������ϴ� ���� �ݺ�

private:
	vector<Frame*> frames; // �� Ŭ������ ����� �����ӵ��� ����� ����
	CLIP_TYPE repeat_type;
	bool is_play; // �ִϸ��̼��� ���� ��������� �ƴ����� ����صδ� ����

	UINT cur_frame_num; // ��ü ������ �� ���° �������� ���� ��� ������ �����ϴ� ����
	float time; // fps�� ����ϱ� ���� �ð������ �����صδ� ����
	float fps; // �ʴ� �� ���� �������� ����� ������ �����ϴ� ����

	bool is_reverse; // PINGPONG Ÿ�Կ��� �����ϴ� �������Ȳ ���θ� �����ϴ� ���

public:
	Clip(
		vector<Frame*> frames,
		CLIP_TYPE t = CLIP_TYPE::LOOP,
		float fps = 1.0f / 8.0f//�ִϸ��̼� �� �������� ����Ǵµ� �ɸ��� �ð�
		// �ٸ��� ���ϸ� �ִ̾ϸ��̼ǿ� ���ϴ� ����ӵ��� �Է��ϴ°�
	);
	~Clip();

	bool isPlay() { return is_play; }
	Vector2 GetFrameSize() { return frames[cur_frame_num]->GetFrameSize(); }
	Vector2 GetFrameOrigSize() { return frames[cur_frame_num]->GetFrameOrigSize(); }


	void Update();
	void Render();
	void Play(UINT type = 0);
	void Pause();
	void Stop();

};