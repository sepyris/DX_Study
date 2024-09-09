#include "framework.h"

LoopImageRect::LoopImageRect(wstring file_loc, Vector2 image_size, Vector2 size, Vector2 p, float a, Vector2 start_uv, Vector2 end_uv, Vector2 s, D3D11_PRIMITIVE_TOPOLOGY t)
	:Transform(p, s, a)
{
	if (image_size.x < size.x) {
		int mag = size.x / image_size.x;
		end_uv.x = mag;
	}
	if (image_size.y < size.y) {
		int mag = size.y / image_size.y;
		end_uv.y = mag;
	}

	image = new RectUV(size, start_uv, end_uv);
	ScratchImage img;
	//���� �̹��� ������ �ε��ؿͼ� �����ϴ� ������ ����ϴ� Ŭ����

	LoadFromWICFile(wstring(file_loc).c_str(),
		WIC_FLAGS_NONE, nullptr, img);
	//�����ϴ� ������ �ҷ��ͼ� img�� �����ϴ� �Լ�
	//����� ���� ������ img�� ���� �����

	CreateShaderResourceView(DEVICE, img.GetImages(), img.GetImageCount(), img.GetMetadata(), &srv);
	//������� srv�� DEVICE�� img�� �̿��� ���̴� ���ҽ� �� ��°��� ����
	// �̰����� ���̴��� ���������͸� ����
	//�� srv�κ��� ���� PixelShaderUV.hlsl���� �ٷ�� samp�� map� �����͸� ����
	collider = new RectCollider(size);
}

LoopImageRect::~LoopImageRect()
{
	delete image;
	srv->Release();
	delete collider;
}

void LoopImageRect::Update()
{
	collider->WorldUpdate();
	WorldUpdate();
}

void LoopImageRect::Render()
{
	WB->SetVS(0);
	DVC->PSSetShaderResources(0, 1, &srv);
	collider->Render();
	image->Render();
}