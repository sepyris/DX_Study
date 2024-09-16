#pragma once
class StarBridgeWaitting :public Scene {
private:
	BackGroundUV* bg;
	RectCollider* ground[20];
	RectCollider* center_portal;
	RectCollider* left_portal;
	ImageRect* info;

	AnimatePlayer* player;
public:
	StarBridgeWaitting(UINT area);
	~StarBridgeWaitting();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};