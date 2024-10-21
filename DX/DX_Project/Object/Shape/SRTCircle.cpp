#include "framework.h"

SRTCircle::SRTCircle(Float2 size, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type)
	: Shape(), type(type), size(size)
{
	float angle = 2 * (float)M_PI;
	// 원에서 현재 내가 찍어야 할 점의 위치를 삼각함수를 통해 구하기 위해,
	// 그 삼각함수에 넣을 좌표값을 계산해 저장하기 위한 변수를 만든 것
	// 초기값은 원 한 바퀴를 의미하는 360도를
	// 라디안으로 변환한 값인 2 * pi 값

	// M_PI라는 수학적 상수를 이용하므로
	// framework.h에서 _USE_MATH_DEFINES를 동반한 <math.h>의 포함이 필요
	// 우리는 이미 이걸 했죠?

	switch (type)
	// 지금은 원의 내용물을 꽉 채워서 출력했지만
	// 상황에 따라선 원의 안쪽을 전부 그릴 필요 없이
	// 그 테두리선만 그릴 필요가 있음
	// 그래서 입력받은 D3D11_PRIMITIVE_TOPOLOGY(=type)가 어떤 것이냐에 따라서
	// 그림을 그리는 데 사용할 정점의 데이터를 다르게 만들도록 한 것
	{
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		for (int i = 0; i < vertex_count; i++)
		{
			vertices.emplace_back(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
			// 삼각형의 첫번째 점으로 사용할, 원의 중점을 입력
			vertices.emplace_back(
				-cos(angle) * this->size.x,
				sin(angle) * this->size.y,
				(float)(angle / (2 * M_PI)), float((2 * M_PI - angle) / (2 * M_PI)), 1.0f
			);
			// 삼각함수를 통해 확보한 육각형의 점 중 하나를 추가

			angle -= 2 * (float)M_PI / (float)vertex_count;
			// 각도 보정

			vertices.emplace_back(
				-cos(angle) * this->size.x,
				sin(angle) * this->size.y,
				(float)(angle / (2 * M_PI)), (float)((2 * M_PI - angle) / (2 * M_PI)), 1.0f
			);
			// 삼각함수를 통해 확보한 육각형의 다음 점을 추가
		}
		break;
		// 이를 총 6개의 삼각형이 육각형을 그리게 하도록 하고 종료

	case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
		for (int i = 0; i <= vertex_count; i++)
		{
			vertices.emplace_back(
				-cos(angle) * this->size.x,
				sin(angle) * this->size.y,
				(float)(angle / (2 * M_PI)), (float)((2 * M_PI - angle) / (2 * M_PI)), 1.0f
			);
			angle -= 2 * (float)M_PI / (float)vertex_count;
		}
		// 이 쪽은 시작점만 추가로 적어줘야 한다는 점 빼면 꼭지점들만 순차적으로 추가하면 됨
		break;
	}

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	VS = new VertexShader(L"Shader/VertexShader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShader.hlsl", flags);

	VB = new VertexBuffer(vertices.data(), (UINT)sizeof(Vertex), (UINT)vertices.size());
	CB = new ColourBuffer();
}

SRTCircle::SRTCircle(float radius, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type)
	: SRTCircle(Float2(radius, radius), vertex_count, type)
	// 위임 생성자는 자기 자신의 다른 생성자로도 이용할 수 있다
{
}

SRTCircle::~SRTCircle()
{
	delete VS;
	delete PS;
	delete VB;
	delete CB;
}

void SRTCircle::Render()
{
	if (CB->data.colour.x != 1.0f || CB->data.colour.y != 1.0f || CB->data.colour.z != 1.0f)
		CB->SetPS(0);
	// 컬러버퍼에 저장된 색상값이 흰색이 아니라면
	// 이 컬러버퍼를 셰이더에 입력할 것

	VB->Set(type);
	VS->Set();
	PS->Set();
	DVC->Draw((UINT)vertices.size(), 0);
}