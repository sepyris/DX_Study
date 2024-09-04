#include "framework.h"

MiniMap::MiniMap(wstring file_loc, Vector2 start_uv, Vector2 end_uv, Vector2 p, Vector2 s, float a, Vector2 size, D3D11_PRIMITIVE_TOPOLOGY t)
	:Transform(p, s, a)
{
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

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			star[i][j] = new Star(L"Texture/AnimateScene/Animation/star.png");
			star[i][j]->scale.x = 0.2f;
			star[i][j]->scale.y = 0.1f;
			//star[i][j]->GetCollider()->scale.x = 0.1f;
			//star[i][j]->GetCollider()->scale.y = 0.1f;
		}
	}
	for (int i = 0; i < 20; i++) {
		stage_star_line[i] = new StarLine(L"Texture/Image/stagestarline.png");
		stage_star_line[i]->GetCollider()->scale.y = 0.06f;
	}
}

MiniMap::~MiniMap()
{
	delete image;
	srv->Release();
}

void MiniMap::SetStar(S_STAGE stage_star[])
{
	for (int i = 0; i < 10; i++) {
		minimap_stage[i] = stage_star[i];
	}
	
	for (int i = 0; i < 10; i++) {
		stage_star_line[i]->SetStarOne(minimap_stage[i].star1);
		stage_star_line[i]->SetStarTwo(minimap_stage[i].star2);
		stage_star_line[i]->ChangeImage(L"Texture/Image/stagestarline.png");
	}
}

void MiniMap::SetCompStar(S_STAGE stage_star)
{
	int star1_x = stage_star.star1.x;
	int star1_y = stage_star.star1.y;
	int star2_x = stage_star.star2.x;
	int star2_y = stage_star.star2.y;

	for (int i = 0; i < 10; i++) {
		if (stage_star_line[i]->CheckLineComp(Vector2(star1_x, star1_y), Vector2(star2_x, star2_y))) {
			stage_star_line[i]->ChangeImage(L"Texture/Image/starline.png");
		}
	}
}

void MiniMap::Update()
{
	
	WorldUpdate();
	float init_x_pos = -140;
	float init_y_pos = -155;
	float x_pos = 0;
	float y_pos = 0;
	for (int i = 0; i < 10; i++) {
		x_pos = init_x_pos + (i * 31);
		for (int j = 0; j < 12; j++) {
			y_pos = init_y_pos + (j * 31);
			star[i][j]->pos = pos + Vector2(x_pos, y_pos);
			star[i][j]->Update();
			star[i][j]->SetComp();
		}
	}

	for (int i = 0; i < 10; i++) {
		//스테이지 라인 생성
		int star1_x = stage_star_line[i]->GetStarOne().x;
		int star1_y = stage_star_line[i]->GetStarOne().y;
		Vector2 star1_pos = star[star1_x][star1_y]->pos;

		int star2_x = stage_star_line[i]->GetStarTwo().x;
		int star2_y = stage_star_line[i]->GetStarTwo().y;
		Vector2 star2_pos = star[star2_x][star2_y]->pos;

		stage_star_line[i]->GetCollider()->pos = (star1_pos + star2_pos) / 2;
		stage_star_line[i]->GetCollider()->rot.z = (star1_pos - star2_pos).Normalized().Angle();
		stage_star_line[i]->SetSize((star1_pos - star2_pos).GetLength());
		stage_star_line[i]->Update();
		stage_star_line[i]->GetCollider()->WorldUpdate();
	}
}

void MiniMap::Render()
{
	WB->SetVS(0);
	DVC->PSSetShaderResources(0, 1, &srv);
	image->Render();

	for (int i = 0; i < 10; i++) {
		stage_star_line[i]->Render();
		stage_star_line[i]->GetCollider()->Render();
	}
	for (int i = 0; i < 10; i++) {
		//해당 별만 렌더링
		int star1_x = stage_star_line[i]->GetStarOne().x;
		int star1_y = stage_star_line[i]->GetStarOne().y;
		int star2_x = stage_star_line[i]->GetStarTwo().x;
		int star2_y = stage_star_line[i]->GetStarTwo().y;
		Star* tmp = star[star1_x][star1_y];
		if (tmp != NULL) {
			tmp->Render();
		}
		Star* tmp2 = star[star2_x][star2_y];
		if (tmp2 != NULL) {
			tmp2->Render();
		}
	}
}
