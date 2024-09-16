#pragma once
// 기본적으로는 지난 프로젝트에서 만들었던 것과 비슷
// 하지만 이번엔 적용되는 이론 자체가 있는 만큼
// 기존 클래스와는 구성이 달라질 것

class Shape
{
protected:
	vector<Vertex> vertices = {};
	vector<VertexUV> vertices_uv = {};

	VertexShader* VS;
	PixelShader* PS;

	// pos_x, pos_y는 더 이상 사용하지 않음
	// : transform이라는 클래스에서 다룰 예정

	VertexBuffer* VB;
	ColourBuffer* CB;
	// 각각 정점/색상을 저장하는 데 사용할 버퍼들
	// 이제는 ID3D11Buffer 대신 각각의 용도에 특화된 전용 클래스를 이용
public:
	Shape();

	VertexBuffer** const GetBuffer() { return &VB; }
	int GetVertexSize() { return (int)vertices.size(); }
	int GetVertexUVSize() { return (int)vertices_uv.size(); }

	void SetColor(Float4 colour)
	// 이 도형이 가져야 할 색을 지정해주는 지정자
	// -> 색 버퍼에 새로운 색을 저장하는 함수
	{
		CB->data.colour = colour;
	}

	virtual void Render() = 0;
	// 기존에 Scene에서 그림을 출력하는 코드를 전부 실행했던 걸
	// 앞으로는 각 오브젝트가 가지고 있는 그래픽을 담당하는 클래스들이
	// 관련 처리를 전부 도맡아 하게 될 예정

	// 이를 위해, 그 출력을 담당할 함수를
	// 이 클래스를 상속받는 모든 클래스가 가지도록 강제
};