#pragma once
/*
애니메이션 : 정지되어 있는 수많은 그림들을 매우 빠른 속도로 연속적으로 보여줘서
마치 움직이는것처럼 착각하게 만드는 원리로 만들어지는 영상을 말함

->애니메이션은 기본적으로 그 각각의 움직임을 담당하는 하나하나의 그림들의 집합
*/


// Frame :: 애니메이션의 컷(=애니메이션의 프레임 하나) 하나하나를 담당하는 클래스
//애니메이션에서의 본래의 뜻은 영상을 구성하는 사진이 초당 사용된개수
//혹은 그 구성하는 사진하나하나
class Frame
{
private:
	vector<VertexUV> vertices; // 정점을 저장하는 벡터
	vector<UINT> indices; // 사용할 정점의 인덱스를 저장할 벡터

	VertexBuffer* VB;
	IndexBuffer* IB;
	// 위 2개의 벡터들을 담당하는 버퍼들

	Texture* texture;
	// 모든 프레임은 각각 그 프레임이 담당하는 이미지를 출력해야 함
	// 그 이미지를 이 변수를 통해 관리

	Vector2 frame_size;
	// 프레임이 실제로 출력할 사이즈

public:
	Frame(wstring file, Vector2 startUV = Vector2(0, 0), Vector2 endUV = Vector2(1, 1));
	Frame(wstring file, float x, float y, float w, float h);

	~Frame();

	void Render();
	//애니메이션 자체는 이 프레임을 출력하는것을 교체하면서 수행되는 것이므로,
	//그 출력을 담당할 프레임의 Render함수는 반드시 필요

	// 이 프레임이 사용하는 스프라이트의 원본 파일이 담당하는 크기
	//기본적으로 프레임 외부에서 텍스쳐 자체에 접근할 방법이 없기 때문에
	//만들어두는 함수
	Vector2 Size() { return texture->GetSize(); }
	// 이 프레임이 실제로 출력할 사이즈를 담당하는 함수
	Vector2 GetFrameSize() { return frame_size; }
	// 이 프레임이 사용하는 스프라이트의 원본 파일과 실제로 출력할 사이즈를 확정짓기 위한 비율을 이용,
	// 이 프레임이 담당하는 스프라이트 자체의 본래 크기를 계산해 반환하는 함수
	Vector2 GetFrameOrigSize() { return frame_size * texture->GetSize(); }

};