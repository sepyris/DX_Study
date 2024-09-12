#include "framework.h"

LoopImageRect::LoopImageRect(wstring file_loc, Vector2 image_size, Vector2 size, Vector2 p, float a, Vector2 start_uv, Vector2 end_uv, Vector2 s, D3D11_PRIMITIVE_TOPOLOGY t)
	:Transform(p, s, a)
{
	this->size = size;
	if (image_size.x < this->size.x) {
		int mag = this->size.x / image_size.x;
		end_uv.x = mag;
	}
	if (image_size.y < this->size.y) {
		int mag = this->size.y / image_size.y;
		end_uv.y = mag;
	}

	image = new RectUV(this->size, start_uv, end_uv);
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
	
	if (file_loc == L"Texture/Image/footholdloop.png") {
		collider = new RectCollider(Vector2(this->size.x, 10));
	}
	else if (file_loc == L"Texture/Image/wallloop.png") {
		collider = new RectCollider(this->size);
	}
	else if (file_loc == L"Texture/Image/footholduphillloop.png") {
		collider = new RectCollider(Vector2(this->size.x+55, 10));
		collider->rot.z = -0.58f;
	}
	else if (file_loc == L"Texture/Image/footholddownhillloop.png") {
		collider = new RectCollider(Vector2(this->size.x+55, 10));
		collider->rot.z = 0.58f;
	}
	else {
		//�浹 ������ ������ �̹����� ũ�Ⱑ �ʿ���⿡ 0���� ����
		collider = new RectCollider(Vector2(0, 0));
	}
	
}

LoopImageRect::~LoopImageRect()
{
	delete image;
	srv->Release();
	delete collider;
}

void LoopImageRect::Update()
{
	WorldUpdate();
	collider->WorldUpdate();
}

void LoopImageRect::Render()
{
	WB->SetVS(0);
	DVC->PSSetShaderResources(0, 1, &srv);
	image->Render();
	collider->Render();
}
