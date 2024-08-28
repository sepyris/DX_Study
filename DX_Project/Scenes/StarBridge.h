#pragma once
class StarBridge :public Scene {
private:
	BackGroundUV* bg;
	Star* star[10][12];
	ImageRect* star_line;

	AnimatePlayer* player;
public:
	StarBridge();
	~StarBridge();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};