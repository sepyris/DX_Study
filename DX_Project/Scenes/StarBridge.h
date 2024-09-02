#pragma once
class StarBridge :public Scene {
private:
	struct S_STAGE {
		Vector2 star1;
		Vector2 star2;
		void SetStageStar(int star1_x, int star1_y, int star2_x, int star2_y) {
			star1 = Vector2(star1_x, star1_y);
			star2 = Vector2(star2_x, star2_y);
		}
	};

	BackGroundUV* bg;
	AnimatePlayer* player;

	Star* star[10][12];
	StarLine* star_line[20];
	S_STAGE select_star;
	
	//starcount
	S_STAGE stage_star[10];
	S_STAGE stage_star_fix[10][10];
	StarLine* stage_star_line[20];
	int active_star_count = 0;


	ImageRect* exit_button;
	RectCollider* mouse_object;
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