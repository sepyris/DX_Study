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
	bool is_horizon_mode = true;

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
	enum class CAM_STATUS {
		HORIZON = 0,
		VERTICAL,
		RUNNING,//달리기 모드 우측으로 제한이 없음
	}cam_mode;

	void Update();

	void SetVerticalScreen();
	void SetRunningScreen();
	void SetHorizonScreen();

	Camera* GetMainCamera() { return main_camera; }

	float GetScreenSizeX() { return size_x.y - size_x.x; }
	float GetScreenSizeY() { return size_y.x - size_y.y; }

	CAM_STATUS GetScreenMode() { return cam_mode; }
};
