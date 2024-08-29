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
