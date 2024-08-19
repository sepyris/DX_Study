#pragma once
class MapleIsland :public Scene {
private:
	BackGroundUV* bg;
	RectCollider* ground[20];
	RectCollider* left_col[20];
	RectCollider* right_col[20];
	RectCollider* hill_ground[20];
	RectCollider* ladder[20];
	RectCollider* right_portal;

	AnimatePlayer* player;
	
	
public:
	MapleIsland(float area);
	~MapleIsland();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};