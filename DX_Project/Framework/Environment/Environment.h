#pragma once

//기존에 Program에서 다루고 있었던
//DX그래픽을 다루기 위해 설정해둬야 했던 환경을
//전담해서 만드는 클래스


class Environment : public Singleton<Environment> {

private:
	friend class Singleton;

	Camera* main_camera;
	
	MatrixBuffer* projection;
	Matrix orthographic;
	Vector2 size_x, size_y;

	ID3D11SamplerState* samplerstate;
	ID3D11BlendState* blendstate;
	ID3D11RasterizerState* rasterizerstate;

	void CreateProjection();

	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

	Environment();
	~Environment();

public:
	void Update();

	void SetVerticalScreen();
	void SetHorizonScreen();

	Camera* GetMainCamera() { return main_camera; }

	float GetScreenSizeX() { return size_x.y - size_x.x; }
	float GetScreenSizeY() { return size_y.x - size_y.y; }
};
