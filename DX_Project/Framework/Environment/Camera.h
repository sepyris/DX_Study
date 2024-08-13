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

public:
	Camera();
	~Camera();

	void Update();
	void PostRender();

	void SetPos(Vector2 pos);
	void SetTarget(Transform* target) {
		this->target = target;
	};


private:
	void FreeMode();
	void FollowMode();

	void SetView();
};