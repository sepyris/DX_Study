#include "framework.h"

StarLine::StarLine(wstring file_loc):
	ImageRect(file_loc)
{
	origin_size = GetCollider()->scale.x;
}

void StarLine::SetSize(float size)
{
	GetCollider()->scale.x = origin_size / 100 * size;
}

bool StarLine::CheckLineComp(Vector2 star1, Vector2 star2)
{
	if (this->star1.x == star1.x && this->star1.y == star1.y) {
		if (this->star2.x == star2.x && this->star2.y == star2.y) {
			status = LINE_STATUS::COMP;
			return true;
		}
	}
	if (this->star2.x == star1.x && this->star2.y == star1.y) {
		if (this->star1.x == star2.x && this->star1.y == star2.y) {
			status = LINE_STATUS::COMP;
			return true;
		}
	}
	return false;
}
