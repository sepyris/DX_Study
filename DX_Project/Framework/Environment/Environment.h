#pragma once

//������ Program���� �ٷ�� �־���
//DX�׷����� �ٷ�� ���� �����ص־� �ߴ� ȯ����
//�����ؼ� ����� Ŭ����


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
		RUNNING,//�޸��� ��� �������� ������ ����
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
