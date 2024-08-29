#pragma once
class StarLine : public ImageRect {
private:
	enum class LINE_STATUS {
		NONE = 0,
		SETTING,
		COMP,
		MAX = 3
	}status;
	float origin_size;

public:
	StarLine(wstring file_loc);
	~StarLine();
	void SetSize(float size);

	LINE_STATUS GetLineStatus() { return status; }
	void SetLine() { status = LINE_STATUS::SETTING; }

};