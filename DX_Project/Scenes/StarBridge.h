#pragma once
class StarBridge :public Scene {
private:
	struct S_STAGE {
		Vector2 star1;
		Vector2 star2;
	};

	BackGroundUV* bg;
	AnimatePlayer* player;

	Star* star[10][12];
	StarLine* star_line[20];
	S_STAGE select_star;
	
	//starcount
	S_STAGE stage_star[10];
	StarLine* stage_star_line[20];
	int active_star_count = 0;
	//RectCollider* exit_button;
	
public:
	StarBridge();
	~StarBridge();

	void CreateStage();

	void ResetStage();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};