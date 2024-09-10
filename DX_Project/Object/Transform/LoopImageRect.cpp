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
	//실제 이미지 파일을 로딩해와서 저장하는 역할을 담당하는 클래스

	LoadFromWICFile(wstring(file_loc).c_str(),
		WIC_FLAGS_NONE, nullptr, img);
	//실존하는 파일을 불러와서 img에 저장하는 함수
	//제대로 실행 됬으면 img의 값이 변경됨

	CreateShaderResourceView(DEVICE, img.GetImages(), img.GetImageCount(), img.GetMetadata(), &srv);
	//멤버변수 srv에 DEVICE와 img를 이용해 셰이더 리소스 뷰 라는것을 생성
	// 이걸통해 셰이더에 사진데이터를 보냄
	//이 srv부분을 통해 PixelShaderUV.hlsl에서 다루는 samp와 map등에 데이터를 보냄
	if (file_loc == L"Texture/Image/footholdloop.png") {
		collider = new RectCollider(Vector2(size.x, 3));
	}
	else if (file_loc == L"Texture/Image/wallloop.png") {
		collider = new RectCollider(size);
	}
	else if (file_loc == L"Texture/Image/footholduphillloop.png") {
		collider = new RectCollider(Vector2(size.x+70, 3));
		collider->rot.z = -0.58f;
	}
	else if (file_loc == L"Texture/Image/footholddownhillloop.png") {
		collider = new RectCollider(Vector2(size.x+70, 3));
		collider->rot.z = 0.58f;
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
