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
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};