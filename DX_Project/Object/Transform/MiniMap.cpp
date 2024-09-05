#include "framework.h"

MiniMap::MiniMap(wstring file_loc, Vector2 start_uv, Vector2 end_uv, Vector2 p, Vector2 s, float a, Vector2 size, D3D11_PRIMITIVE_TOPOLOGY t)
	:Transform(p, s, a)
{
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


	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			star[i][j] = new Star(L"Texture/AnimateScene/Animation/star.png");
			//�̴ϸʿ� �°� �� ������ ����
			star[i][j]->scale.x = 0.2f;
			star[i][j]->scale.y = 0.1f;
		}
	}
	for (int i = 0; i < 20; i++) {
		stage_star_line[i] = new StarLine(L"Texture/Image/stagestarline.png");
		//�̴ϸʿ� �°� ���� ������ ����
		stage_star_line[i]->GetCollider()->scale.y = 0.06f;
	}
}

MiniMap::~MiniMap()
{
	delete image;
	srv->Release();
}

void MiniMap::SetStar(S_STAGE stage_star[],int line_count)
{
	stage_line_count = line_count;

	//���������� �ִ� ���� ��ġ�� ����
	for (int i = 0; i < stage_line_count; i++) {
		minimap_stage[i] = stage_star[i];
	}
	
	//�̴ϸ��� �׸��� ���� ���ο� �� ����
	for (int i = 0; i < stage_line_count; i++) {
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
	//�Ϸ�� ������ �̹��� ����
	for (int i = 0; i < stage_line_count; i++) {
		if (stage_star_line[i]->CheckLineComp(Vector2(star1_x, star1_y), Vector2(star2_x, star2_y))) {
			stage_star_line[i]->ChangeImage(L"Texture/Image/starline.png");
		}
	}
}

void MiniMap::Update()
{
	WorldUpdate();
	//�̴ϸ� ����� �°� �� ��ġ ����
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

	//�̴ϸʿ��� ������ ���̱⿡ ���� ����
	for (int i = 0; i < stage_line_count; i++) {
		//�������� ���� ����
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

	//���� ������
	for (int i = 0; i < stage_line_count; i++) {
		stage_star_line[i]->Render();
		stage_star_line[i]->GetCollider()->Render();
	}
	for (int i = 0; i < stage_line_count; i++) {
		//�ش� ���� ������
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
