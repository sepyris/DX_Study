#pragma once
// 이 프로젝트에서 사용할 정점들을 정의 하는 헤더
//앞으로 특정한 정점을 필요로 할때 만듬
struct Vertex
// 앞으로 우리가 도형을 만들 때 쓸 정점의 정보는 이 구조체를 통해 관리함
{
	Float3 position; // 정점의 위치
	// 우리가 실제로 다루는 건 2D지만
	// 기본적으로는 3D 쪽의 기능을 이용해서 2D를 다루는 것이기 때문에
	// 사용하는 함수 등의 규격에 맞게 x,y,z 3개 차원의 데이터를 
	// 전부 구성은 해둬야 함 -> 사용은 안 하더라도 z값은 일단 가지게 만듦

	Float4 colour; // 정점이 가지고 있는 색
	// RGB값을 이용해서 색을 결정하나,
	// 여기에 추가로 Alpha값이라는 데이터를 같이 저장함

	Vertex()
		// C++에선 구조체는 사실상 public만 존재하는 클래스라 봐도 무방
		// 이렇게 생성자를 만드는 것도 문제 X
		// 아무 입력 없이 디폴트 선언했읋 때의 초기화값
	{
		position = Float3(0, 0, 0);
		colour = Float4(0, 0, 0, 1);
		// RGB값 외에 4번째 값인 알파값은 사용할 기회가 왔을 때 실행
	}
	Vertex(float x, float y, float r, float g, float b)
	{
		position = Float3(x, y, 0);
		// 2D에선 z축의 위치를 사용하지 않음
		colour = Float4(r, g, b, 1);
		// DX에서는 RGB값을 이용할 때
		// 0.0f ~ 1.0f까지의 값을 통해 백분율로서 색상을 표시함
	}
};


struct VertexPos {// 좌표를 제외한 어떤 데이터도 없는 꼭지점
	Float3 position;

	VertexPos(float x = 0, float y = 0)
	{
		position = Float3(x, y, 0);
	}
};

//struct VertexUV