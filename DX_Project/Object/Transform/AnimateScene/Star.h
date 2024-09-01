#pragma once

class Star : public Transform {
private:
	enum class CHAR_STATUS {
		IDLE = 0,
		SET,
		COMP,
		MAX = 3
	}action_status;
	CHAR_STATUS tmp_status;
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	vector<Clip*> clips;

	RectCollider* collider;
	UINT clip_cursor;
public:
	Star(wstring file);
	~Star();

	RectCollider* GetCollider() { return collider; }
	void Update();
	void Render();
	void PostRender();

	bool IsActive();
	void SetActive();
	void SetComp();
	void SetNone();
	bool IsComplate();
	void ResetStatus();

	void SetColor(Float4 color) {
		CB->data.colour = color;
	}

	void SetClip(CHAR_STATUS stat);

};