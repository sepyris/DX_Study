#pragma once
// ���� �츮�� ����� ������Ʈó��
// ���� �ڵ� �ʿ��� ��� �۾��� ������� �ʰ�,
// ���α׷��� �������� ó���� ����ϴ� Ŭ������ �ϳ� ����
// �ű⼭ ���α׷��� �ʿ��� �۾������ �����ϴ� ���� �Ѱ��ϵ��� ����� �������
// ���α׷��� �����ϴ� ��찡 ����

// �׷��� �� ���α׷��� �������� �帧�� ����ϴ� �� Ŭ������ �̸���
// Program�̶� ���� ��
// ��, �� Ŭ������ ���α׷��� �������� ó���� �Ѱ��ϴ� Ŭ����

class Program
{
private:
	Scene* scene;
	// ���α׷����� �ϳ��� ����� ����ϴ� Ŭ����
	// �� Ŭ������ ���� �츮�� ���� ȭ�鿡�� ��µǴ� ������� ���� ����

	/*
	���� ������ ���� ������ Scene�� �̿��� ��������� ������
	�� Scene�� ������ �󸶳� �þ�� �𸣴�
	vector�� �̿��ؼ� ������ �󸶰� �ƴ� ���� ���� �ֵ��� ����Ʈ�� ������
	*/


	

public:
	Program();
	~Program();

	void Update(); // ���α׷��� ����Ǹ鼭 ������Ʈ�Ǿ�� �� ������� ����
	void Render(); //		   ''		  ȭ�鿡 ��µ� ������� 
	// �� �Լ����� ���þ� ����ϵ��� ��

	void Create();
	// �� Ŭ������ ���� �� �ʱ�ȭ�ؾ� �ϴ� ������� �����ڿ��� �и��ؼ� ����
	void Delete();
	// �� Ŭ������ ����� ����Ǿ��� �� ó���ؾ� �ϴ� �������
	// �Ҹ��ڿ��� �и��ؼ� �����, �ܺο��� ȣ���� ������ ���·� ����

	void CreateScene(UINT map_code,UINT area);
	//Scene�������� ���α׷��� ���� �ٷ�� scene�� �ٸ������� �ٲٰ��� �� �� 
	//ȣ���ϵ��� �ϴ� �Լ�

};