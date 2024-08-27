#include "framework.h"

Star::Star(wstring file)
{
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	//��� CHAR_STATUS::IDLE
	Vector2 init_pos = { 11,2 };
	Vector2 this_frame_size = { 32,32 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//��� ���� ��
	
	//�������� CHAR_STATUS::SET
	init_pos = { 8,37 };
	this_frame_size = { 33,32 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//���� ���� ��
	
	//�Ϸ� CHAR_STATUS::COMP
	init_pos = { 10,74 };
	this_frame_size = { 32,32 };
	frames.push_back(new Frame(file, init_pos.x, init_pos.y, this_frame_size.x, this_frame_size.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));
	frames.clear();
	//�Ϸ� ���� ��

	VS = new VertexShader(L"Shader/VertexShader/VertexShaderUV.hlsl", 2);
	PS = new PixelShader(L"Shader/PixelShader/PixelShaderUv.hlsl");

	CB = new ColourBuffer();

	collider = new RectCollider(Vector2(50, 50));


	clip_cursor = 0;
	action_status = CHAR_STATUS::IDLE;
	this->scale.x = 2;
}

Star::~Star()
{
	for (Clip* c : clips) {
		if (c != NULL) {
			delete c;
		}
	}
	delete CB;
	delete collider;
}

void Star::Update()
{

	WorldUpdate();
	collider->WorldUpdate();
	
}

void Star::Render()
{
	VS->Set();
	PS->Set();
	WB->SetVS(0);
	CB->SetPS(0);
	clips[(UINT)action_status]->Render();

	collider->Render();
}

void Star::PostRender()
{
	
}
void Star::SetClip(CHAR_STATUS stat)
{
	if (stat == action_status) {
		return;
	}

	switch (stat)
	{
	case Star::CHAR_STATUS::IDLE://���ߴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case Star::CHAR_STATUS::SET://�ȴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	case Star::CHAR_STATUS::COMP://�ȴ� ���°� �� ���
		clips[(UINT)action_status]->Stop();
		action_status = stat;
		clips[(UINT)action_status]->Play();
		break;
	default:
		break;
	}
}
