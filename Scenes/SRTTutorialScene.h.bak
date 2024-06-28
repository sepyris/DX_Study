#pragma once
class SRTTutorialScene : public Scene
{
private:
	MatrixBuffer* world;
	MatrixBuffer* view;
	MatrixBuffer* projection;
	// 위 3개는 WVP 변환을 위해 필요한 내용

	MatrixBuffer* worldBuffer;

	MyObject* obj;
	MyObject* satelite;

	SRTCircle* c;

public:
	SRTTutorialScene();
	~SRTTutorialScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};