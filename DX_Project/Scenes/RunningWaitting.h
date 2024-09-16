#pragma once
class RunningWaitting :public Scene {
private:
	BackGroundUV* bg;
	RectCollider* ground[20];
	RectCollider* left_col[20];
	RectCollider* right_col[20];
	RectCollider* hill_ground[20];
	RectCollider* ladder[20];
	RectCollider* left_portal;
	RectCollider* right_portal;
	ImageRect* info;

	AnimatePlayer* player;
public:
	RunningWaitting(UINT area);
	~RunningWaitting();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};