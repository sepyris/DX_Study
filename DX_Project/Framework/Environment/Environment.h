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
