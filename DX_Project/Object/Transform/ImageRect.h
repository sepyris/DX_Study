#pragma once
// Transform�� ��ӹް�, ����μ� �ﰢ���� ����ϵ��� �ϴ�
// �������� ������Ʈ�� ����ϴ� Ŭ����
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