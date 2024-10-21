#pragma once
class StarLine : public ImageRect {
private:
	float origin_size;

	Vector2 star1;
	Vector2 star2;

public:
	enum class LINE_STATUS {
		NONE = 0,
		SETTING,
		COMP,
		MAX = 3
	}status;

	StarLine(wstring file_loc);
	~StarLine();
	void SetSize(float size);

	void SetStarOne(Vector2 star1) { this->star1 = star1; }
	void SetStarTwo(Vector2 star2) { this->star2 = star2; }

	Vector2 GetStarOne() { return star1; }
	Vector2 GetStarTwo() { return star2; }

	bool CheckLineComp(Vector2 star1, Vector2 star2);

	LINE_STATUS GetLineStatus() { return status; }
	void SetLine() { status = LINE_STATUS::SETTING; }
	void ResetLine() { status = LINE_STATUS::NONE; }
};
