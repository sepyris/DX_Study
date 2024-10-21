#pragma once
// ���� ���� Shape�� ��ӹ޾� �̿��ϴ� ���ο� ����� �ﰢ�� Ŭ����
// ��Ȯ���� SRT ��ȯ�� �����ų ������ Ŭ����


class RectUV : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;

public:
	RectUV(Vector2 size = Float2(100.0f, 100.0f),
		Vector2 start_uv = Vector2(0,0),
		Vector2 end_uv = Vector2(1, 1),
		D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~RectUV();


	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }

	// Shape��(��) ���� ��ӵ�
	virtual void Render() override;

};