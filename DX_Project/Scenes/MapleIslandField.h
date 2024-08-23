#pragma once
class MapleIslandField :public Scene {
private:
	BackGroundUV* bg;
	RectCollider* ground[20];
	RectCollider* left_col[20];
	RectCollider* right_col[20];
	RectCollider* hill_ground[20];
	RectCollider* ladder[20];

	RectCollider* monster_zone[5];
	UINT monster_zone_count[5];
	UINT monster_zen_count[5];
	UINT monster_count = 5;

	RectCollider* left_portal;
	RectCollider* center_portal;
	RectCollider* right_portal;

	AnimatePlayer* player;
	Mushroom* mushroom[10];
	Snail* snail[10];

public:
	MapleIslandField(UINT area);
	~MapleIslandField();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};