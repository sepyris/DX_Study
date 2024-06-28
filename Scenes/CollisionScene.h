#pragma once
class CollisionScene : public Scene {

private:
	MatrixBuffer* view;
	MatrixBuffer* projection;

	RectCollider* player;
	RectCollider* obstackle;
	RectCollider* enemy;

public:
	CollisionScene();
	~CollisionScene();
	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};