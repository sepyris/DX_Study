#pragma once
//���������� ����� ���� ��ֹ� ���� �ۼ�
#define OBSTACKLE_COUNT 50
#define ENEMY_COUNT 50
#define ITEM_MAX_COUNT 50
class CollisionScene : public Scene {
private:
	RectCollider* player; // �÷��̾�

	RectCollider* obstackle[OBSTACKLE_COUNT]; //��
	CircleCollider* enemy[ENEMY_COUNT]; // ��
	CircleCollider* item[ITEM_MAX_COUNT];// ������

	RectCollider* end_stage; // ��������
	RectCollider* dummy_effect;//ȸ�� ������ ���Ѵ���
	

	float interval = 1; // ���͹� �ð� 

	int stage = 1; //���� �������� ��ȣ
	int earn_coin = 0;//���� ����
	int stage_coin = 0;//���������� ���� �ϴ� ����
	bool is_collision = false; //�� ������Ʈ�� �浹 Ȯ��
	bool move_right[ENEMY_COUNT];//�� ������Ʈ ������ ����
	bool move_hor[ENEMY_COUNT]; // �¿�� ������ ����
	bool move_down[ENEMY_COUNT];//�� ������Ʈ ������ ����
	bool move_ver[ENEMY_COUNT];//���Ϸ� ������ ����
	int count = 0; //������ ���� �ݺ����� ���� ī��Ʈ


	//�������� ����
	void CreateStage(int stage);

	//�������� ����
	void DeleteStage();

	//�������� ������Ʈ
	void StageUpdate();

	//�������� ���� üũ
	void EndCheck();

	//�������� �ʱ�ȭ
	void ResetStage();


public:
	CollisionScene();
	~CollisionScene();
	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

};