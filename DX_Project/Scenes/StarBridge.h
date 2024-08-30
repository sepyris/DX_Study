#pragma once
class StarBridge :public Scene {
private:
	struct S_STAGE {
		Vector2 star1;
		Vector2 star2;
	};

	BackGroundUV* bg;
	Star* star[10][12];
	StarLine* star_line[20];

	AnimatePlayer* player;

	//stagecount_starcount
	S_STAGE stage[10][10];
	
public:
	StarBridge();
	~StarBridge();

	void CreateStage();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;


};