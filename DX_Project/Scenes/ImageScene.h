#pragma once
class ImageScene : public Scene {
private:
	BackGroundUV* bg[2];

	ImageRect* image;
	ImageRect* flame;


	float interval = 0;
	int record_time = 0;
public:
	ImageScene();
	~ImageScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};