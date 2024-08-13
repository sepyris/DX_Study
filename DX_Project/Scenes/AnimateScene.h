#pragma once
class AnimateScene :public Scene {
private:
	AnimatePlayer* player;
	RectCollider* obstackle;
	RectCollider* ground[4];

public:
	AnimateScene();
	~AnimateScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};