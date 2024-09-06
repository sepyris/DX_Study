#pragma once
class Running :public Scene {
private:
	BackGroundUV* bg;
	AnimatePlayer* player;

	LoopImageRect* main_ground;

	ImageRect* exit_button;
	RectCollider* mouse_object;



public:
	Running();
	~Running();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};