#pragma once
class StarBridge :public Scene {
private:
	BackGroundUV* bg;
	Star* star[10][12];
	StarLine* star_line[20];

	AnimatePlayer* player;
public:
	StarBridge();
	~StarBridge();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};