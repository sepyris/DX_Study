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

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};