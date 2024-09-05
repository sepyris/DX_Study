#pragma once
class MiniMap : public Transform
{
private:
	RectUV* image;
	ID3D11ShaderResourceView* srv;

	Star* star[10][12];
	S_STAGE minimap_stage[20];
	StarLine* stage_star_line[20];
	int stage_line_count = 0;
public:
	MiniMap(wstring file_loc, 
		Vector2 start_uv = Vector2(0, 0),
		Vector2 end_uv = Vector2(1, 1),
		Vector2 p = Float2(0, 0),
		Vector2 s = Float2(1, 1),
		float a = 0.0f,
		Vector2 size = Float2(WIN_WIDTH/3.5, WIN_HEIGHT/1.7),
		D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~MiniMap();

	void SetStar(S_STAGE stage_star[],int stage);
	void SetCompStar(S_STAGE stage_star);

	void Update();
	void Render();
};