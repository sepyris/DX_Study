#pragma once
#define KEY_MAX 256
// �Ϲ����� Ű������ Ű�� ���ƺ��� 108��
// -> 255���� ���̸� �װ� �������� ���� 128�� �������� ���� 2���μ�
// Ű�� ǥ���� �� ����

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
	// Ư�� Ű�� ���� ���¸� �ǹ�
	// ���������� "������ ����"/"���� �� ����"/"���� �� ����"/"���� ��������"
	// �߰��� MAX�� �� �������� �ִ� �� ���� �����Ͱ� ����ִ����� 
	// üũ�ϱ� ���� ����

	// ������ 3���� ���� Ű������ �� Ű��
	BYTE cur_state[KEY_MAX]; // ���� �����ִ����� ������ �迭
	BYTE old_state[KEY_MAX]; // ���� Ÿ�ֿ̹� �����־������� ������ �迭
	BYTE map_state[KEY_MAX]; // �� 2���� ������ �����ؼ�
	// ���������� �� Ű�� ���� ������ ���������� ���� �� �����ϴ� �迭

	// �� �迭���� ������ Ű�� �ԷµǾ������� ���θ� �Ǵ��� ��
	// ����� ��Ʈ �÷��׵�
	// ��, �� 108�� �̻��� Ű�� �ν��� ���� = Ű������ ��� ���� ���⼭ ó��

	Control();
	~Control();

public:
	void Update();

	bool Down(UINT key) { return map_state[key] == DOWN; }
	bool Up(UINT key) { return map_state[key] == UP; }
	bool Press(UINT key) { return map_state[key] == PRESS; }
};
// ���α׷����� Ű����, ���콺 ���� �Է���ġ �����͸� �����ϴ� �Ŵ���