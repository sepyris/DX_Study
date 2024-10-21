#pragma once
class BackGroundUV : public Transform
{
private:
	RectUV* image;

	ID3D11ShaderResourceView* srv;

public:
	BackGroundUV(wstring file_loc,
		Vector2 start_uv = Vector2(0, 0),
		Vector2 end_uv = Vector2(1, 1),
		Vector2 p = Float2(0, 0),
		Vector2 s = Float2(1, 1),
		float a = 0.0f,
		Vector2 size = Float2(WIN_WIDTH, WIN_HEIGHT),
		D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~BackGroundUV();

	void Update();
	void Render();

};