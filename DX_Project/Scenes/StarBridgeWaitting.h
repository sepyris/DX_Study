#pragma once
class StarBridgeWaitting :public Scene {
private:
	BackGroundUV* bg;
	RectCollider* ground[20];
	RectCollider* center_portal;

	AnimatePlayer* player;
public:
	StarBridgeWaitting(float area);
	~StarBridgeWaitting();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};