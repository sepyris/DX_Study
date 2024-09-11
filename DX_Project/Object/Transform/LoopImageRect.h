#pragma once
class LoopImageRect : public Transform
{
private:
	RectUV* image;
	ID3D11ShaderResourceView* srv;
	RectCollider* collider;
	Vector2 size;

public:
	LoopImageRect(wstring file_loc,
		Vector2 image_size,
		Vector2 size = Float2(WIN_WIDTH, WIN_HEIGHT),
		Vector2 p = Float2(0, 0),
		float a = 0.0f,
		Vector2 start_uv = Vector2(0, 0),
		Vector2 end_uv = Vector2(1, 1),
		Vector2 s = Float2(1, 1),
		D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~LoopImageRect();

	void Update();
	void Render();

	Vector2 GetSize() { return size; }

	RectCollider* GetCollider() { return collider; }

};