#pragma once
#define IMAGE_Y_POS 1400
#define GROUND_IMAGE_SIZE Vector2(172, 150)
#define WALL_IMAGE_SIZE Vector2(174, 200)
#define HILL_IMAGE_SIZE Vector2(299, 300)

#define GROUND_IMAGE_LOC L"Texture/Image/footholdloop.png"
#define WALL_IMAGE_LOC L"Texture/Image/wallloop.png"
#define HILL_UP_IMAGE_LOC L"Texture/Image/footholduphillloop.png"
#define HILL_DOWN_IMAGE_LOC L"Texture/Image/footholddownhillloop.png"
#define BACKGROUND_IMAGE_LOC L"Texture/Image/backgroundimage.png"


class Running :public Scene {
private:
	BackGroundUV* bg;
	AnimatePlayer* player;

	LoopImageRect* ground[100];
	LoopImageRect* wall[100];
	LoopImageRect* hill[100];

	ImageRect* exit_button;
	RectCollider* mouse_object;



public:
	Running();
	~Running();

	void GroundUpdate();
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};