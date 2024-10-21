#include "framework.h"

BackGroundUV::BackGroundUV(wstring file_loc, Vector2 start_uv,Vector2 end_uv, Vector2 p, Vector2 s, float a, Vector2 size, D3D11_PRIMITIVE_TOPOLOGY t)
	:Transform(p, s, a)
{
	image = new RectUV(size,start_uv,end_uv);
	
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
}

BackGroundUV::~BackGroundUV()
{
	delete image;
	srv->Release();
}

void BackGroundUV::Update()
{
	WorldUpdate();
}

void BackGroundUV::Render()
{
	WB->SetVS(0);
	DVC->PSSetShaderResources(0, 1, &srv);
	image->Render();
}
