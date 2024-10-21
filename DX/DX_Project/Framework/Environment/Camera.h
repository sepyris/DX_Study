#pragma once
class Camera :public Transform {
private:
	MatrixBuffer* view;

	float speed;//ī�޶��� �̵��ӵ��� ���ϴ� ����

	Transform* target;//ī�޶� ���� ���

	Vector2 offset; //ī�޶��� ��ü ȭ�鳻������ ��ġ �� ����ϴ� ��
	//���� ��鿡�� ����� 2���� ����

	Vector2 left_top;//ī�޶� ����Ű�� �ִ� ������ ������ ����
	Vector2 right_bottom;//ī�޶� ����Ű�� �ִ� ������ ������ �Ʒ� ����
	//ī�޶� ����Ű�� ������ ��ü ȭ����� ���� �ٸ� ������ �ɼ� �ֱ⿡
	//�̸� ����ϱ� ���� ����ϴ� ��

	float running_pos;

public:
	Camera();
	~Camera();

	void Update();
	void PostRender();

	void SetPos(Vector2 pos);
	void SetTarget(Transform* target) {
		this->target = target;
	};
	void SetRunnuingLastPos(float pos) { running_pos = pos;}


private:
	void FreeMode();
	void FollowMode();

	void SetView();
};