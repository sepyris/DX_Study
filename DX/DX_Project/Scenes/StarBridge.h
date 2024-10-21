#pragma once
class StarBridge :public Scene {
private:
	BackGroundUV* bg;
	MiniMap* mini_map;
	AnimatePlayer* player;

	Star* star[10][12];
	StarLine* star_line[20];
	S_STAGE select_star;
	
	//starcount
	S_STAGE stage_star[20];
	S_STAGE stage_star_fix[20][20];
	StarLine* stage_star_line[20];
	int active_star_count = 0;
	int now_stage = 99;
	int star_line_count = 0;


	ImageRect* exit_button;
	RectCollider* mouse_object;
public:
	StarBridge();
	~StarBridge();

	void InitStage();
	void CreateStage();

	void ResetStage();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};