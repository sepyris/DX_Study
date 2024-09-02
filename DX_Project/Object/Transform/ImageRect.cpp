#include "framework.h"

ImageRect::ImageRect(wstring file_loc,Vector2 p, Vector2 s, float a, Vector2 size, D3D11_PRIMITIVE_TOPOLOGY t)
	:Transform(p,s,a)
{
	image = new RectUV(size);
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

ImageRect::~ImageRect()
{
	delete image;
	if (srv != nullptr) {
		srv->Release();
	}
	delete collider;
}

void ImageRect::Update()
{
	collider->WorldUpdate();
	WorldUpdate();
}

void ImageRect::Render()
{
	WB->SetVS(0);
	DVC->PSSetShaderResources(0, 1, &srv);
	//����̽� ���ؽ�Ʈ ���������Ͱ� �� �ִ� ���̴� ���ҽ� �並 �Է�
	//�̸� ���ؼ� PixelUV.hlsl�� samp,map�� �����͸� ������ �ְ� ����
	collider->Render();
	image->Render();

}
