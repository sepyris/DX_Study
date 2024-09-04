#pragma once
// Transform을 상속받고, 멤버로서 삼각형을 출력하도록 하는
// 실질적인 오브젝트를 담당하는 클래스
class ImageRect : public Transform
{
private:
	RectUV* image;

	ID3D11ShaderResourceView* srv;

	RectCollider* collider = NULL;

public:
	ImageRect(wstring file_loc,
		Vector2 p = Float2(0, 0),
		Vector2 s = Float2(1, 1),
		float a = 0.0f,
		Vector2 size = Float2(100, 100),
		D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~ImageRect();

	void ChangeImage(wstring file_loc);
	void Update();
	void Render();

	RectCollider* GetCollider() { return collider; }

};