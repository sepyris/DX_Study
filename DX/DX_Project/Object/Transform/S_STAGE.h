#pragma once
struct S_STAGE {
	Vector2 star1;
	Vector2 star2;
	void SetStar(int star1_x, int star1_y, int star2_x, int star2_y) {
		star1 = Vector2((float)star1_x, (float)star1_y);
		star2 = Vector2((float)star2_x, (float)star2_y);
	}
};