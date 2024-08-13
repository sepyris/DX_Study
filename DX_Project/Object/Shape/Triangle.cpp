#include "framework.h"
#include "Triangle.h"

Triangle::Triangle(Float2 size, D3D11_PRIMITIVE_TOPOLOGY type)
	: size(size), type(type)
{
	// 출력할 삼각형의 정점을 벡터에 추가
	vertices.emplace_back(0, size.y * (-2.0 / 3.0), 1.0f, 1.0f, 1.0f);
	vertices.emplace_back(size.x * (0.5f), size.y * (1.0 / 3.0), 1.0f, 1.0f, 1.0f);
	vertices.emplace_back(size.x * (-0.5f), size.y * (1.0 / 3.0), 1.0f, 1.0f, 1.0f);

	// 기존 것과 다른 게 없어보이지만,
	// 결정적인 차이점으로 여기서는 size의 기본값이 100, 100이라는 것이 있음
	// -> 지금 이 꼭지점들은 상대좌표가 아니라 절대좌표계를 기준으로,
	// 특히 API 때처럼 화면의 왼쪽 위 끝을 (0,0)으로 잡고 있다는 전제로서
	// 정점의 좌표를 구성하고 있다는 의미

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	VS = new VertexShader(L"Shader/VertexShader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShader.hlsl", flags);

	VB = new VertexBuffer(vertices.data(), sizeof(Vertex),
							vertices.size());
	CB = new ColourBuffer();
	
}

Triangle::~Triangle()
{
	delete VS;
	delete PS;
	delete VB;
	delete CB;
}

void Triangle::Render()
{
	if (CB->data.colour.x != 1.0f
		|| CB->data.colour.y != 1.0f
		|| CB->data.colour.z != 1.0f)
		// 이 삼각형이 보유하고 있는 색상버퍼의 RGB값 중 하나라도 1.0이 아니라면
		// 즉, 완벽한 흰색이 아니라면
		CB->SetPS(0); // 이 도형이 가지고 있는 흰색이 아닌 색상버퍼의 값을
		// 픽셀 셰이더에 넘긴다
		
	// VS, PS를 시스템에 등록하는 부분
	VS->Set();
	PS->Set();

	// 셰이더에 버퍼에 들어있는 데이터를 넘기고
	// 어떤 도형을 그릴 것인지 장치에 알리는 부분
	VB->Set(type);

	// 그대로 남은 건 정점 개수만큼 그려달라 요청하는 이 코드 하나
	DVC->Draw(vertices.size(), 0);
}
