#include "framework.h"

Environment::Environment()
{
	CreateProjection();
	//WVP변환중 View Projection변환을 담당할
	//변환 행렬들을 이 시점에서 초기화

	CreateSamplerState();
	CreateBlendState();
	CreateRasterizerState();
	//이 셋은 기본적으로 외부 텍스쳐 파일의 인식 및 출력을 위해
	//설정해야 하는 state들을 여기서 초기화 함

	main_camera = new Camera();
}

Environment::~Environment()
{
	//delete view;
	delete projection;
}
void Environment::CreateProjection()
{

	projection = new MatrixBuffer();


	size_x = Vector2(0.0f, (float)WIN_WIDTH);
	size_y = Vector2((float)WIN_HEIGHT, 0.0f);

	

	orthographic = XMMatrixOrthographicOffCenterLH
	(
		size_x.x, size_x.y, // X좌표 : 0 ~ (창의 가로 크기)
		size_y.x,size_y.y, // Y좌표 : (창의 세로 크기) ~ 0
		-1.0f, 1.0f // Z좌표 : -1.0f ~ 1.0f(초기값)
	);


	projection->Set(orthographic);

	//view->SetVS(1);
	projection->SetVS(2);
}

void Environment::CreateSamplerState()
//입력받은 이미지를 어떻게 처리할것인지 결정하는 state
//state:상태라는 뜻으로 그냥 설정을 저장하는 역할

{
	D3D11_SAMPLER_DESC desc = {};
	//설정을 저장하는 역할의 클래스
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	//이 이미지를 어떤식으로 보정,정확히는 보간 할것인지 지정
	//보간:인접한 데이터들 사이에 있는,데이터가 아직 정해지지 않은 점에
	//적합한함수를 이용해서 들어갈 데이터를 결정하는 작업

	//원래 이미지가 가지고 있던 데이터로는 표현하지 못하는 부분
	//(확대했을때 기존의 픽셀들 사이에 들어갈 새로운 픽셀들에 들어가게 되는색,혹은 반대로 축소 했을때 인접한 픽셀들중 어느 픽셀이 사라질지등)
	//미리 설정해둔 조건에 맞게 근처 픽셀들의 데이터를 이용하여 연산 함
	//출력할 값을 저장해 보정해주는것이 보간

	//주로 2d에서는 위에서 쓴 MIN_MAG_MIP_POINT라는 값을 쓰고
	//3D에서는 MIN_POINT_MAG_MAP_LINEAR라는 선형 보간을 이용한다.

	desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//입력받은 이미지 파일을 실제 좌표에 위치 시킬때
	//UV값이 0과 1의 범위를 벗어날때가 있음
	//그럴때,저 범위를 벗어나는 부분엔 어떤식으로 색을 출력하도록 하는가에 대해
	//그 방침을 정하는 부분

	//여기서 U,V,W의 값은 각각 실제 Transform 좌표의 x,y,z에 해당
	//즉 U는 가로에서의 그림 처리 방식
	//V는 세로에서의 그림 처리방식을 결정하는 메뉴

	//여기에 들어올수 있는 열거형 데이터는 다음과 같음:
	//MIRROR:1의 단위를 넘을때마다 직전 영역에 있던 내용을 반전시켜서 출력
	// (0 ~ -1까지의 구간은 0을 기점으로 반전 시켜서 출력,
	//  1 ~ 2 까지의 구간은 1을 기점으로 반전 시켜서 출력,
	//  2 ~ 3 까지의 구간은 2를 기점으로,.....)
	// 
	//WRAP:0~1까지의 내용을 그대로 복사해서 출력
	//BORDER:0~1까지의 범위 바깥은 프로그램의 기본 배경색으로만 채우고,
	//       해당범위 안만 원본 이미지를 이용해 출력
	//CLAMP:0~1까지의 범위 제일 끝부분을 경정하는 픽셀 부분으로 그 바깥부분을 전부 채운것
	//      같은 x좌표(정확히는 U) or Y좌표(V)에 있는 모든 픽셀을 전부 저 하나의 픽셀로 전부 채우는 방식
	//MIRROR_ONCE:-1~1은 MIRROR 그 외에은 CLAMP로 채우는 방식

	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	//둘 이상의 이미지가 같은 위치에 존재할때
	//어떤 규칙을 이용해서 어느 이미지를 출력하도록 할것인지
	//그 규칙을 정하는 부분
	//규칙을 적용하지 않으려면 위와 같이 이용


	DEVICE->CreateSamplerState(&desc, &samplerstate);

	DVC->PSSetSamplers(0, 1, &samplerstate);


}

void Environment::CreateBlendState()
//투명처리를 관리하기 위해 만드는 부분
/*
지금까지 RGB값만 이용했지만
실제로는 Alpha값이라는 하나의 값이 더 있음

이 색을 사용하는 부분의 투명도가 어떻게 되는지를 지정하는 값
0이면 자기자신을 전혀 비추지 않고 그 뒤쪽에있는 그래픽을 전부 투시하도록 하는 값
255면 뒤쪽의 그 어떤것도 비추지 않고 자기자신을 비추도록 함

DX는 이 값을이용해서 그래픽의 투명도를 결정함

흔히 영상등에서 투명을 처리하기 위해 사용하는
그린스크린(=크로마키)등 특정한 색으로 칠해진 부분을 투명한 색으로 취급하도록 하는 방식의
투명 처리방법이 있음, 그러나 DX에서는 이방법을 안쓰는가?

이유는 간단:DX는 그걸 직접 지원하지 않음
구현하고자 한다면 가능하기는 함(픽셀 셰이더 쪽에서 입력된 색이 그 크로마키에 해당되는 색상이라면 아예 알파값을 0으로 설정하여 그 색이 반영되지 않도록 하는 방식)
그러나 이건 DX가 직접 지원하는 방식은아니기 때문에
알아서 알파값으로 처리되는 이방식과는 달리 구현 하는 난이도가 상당히 높다

그래서 이 알파값이 0일때 투명으로 처리하겠다는쪽으로 진행함
*/

//그래서 알파값을 다루기 위해 아래와 같이 설정을 해주는것
//아래의 내용들은 항상 같은 값을 사용
//그리고 배경을 제거하고자 한다면
//직접 이미지의 배경이 가지고 있는 알파값을 0으로 바꾸면 됨

{
	D3D11_BLEND_DESC desc = {};
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&desc, &blendstate);

	float blendFactor[] = { 0, 0, 0, 0 };
	DVC->OMSetBlendState(blendstate, blendFactor, 0xffffffff);
}

void Environment::CreateRasterizerState()
//그래픽 파이프라인에서 설명햇던 Rasterizer셰이더단계를 여기서 처리
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&desc, &rasterizerstate);

	DVC->RSSetState(rasterizerstate);
}

void Environment::Update()
{
	if (KEY_PRESS(VK_LCONTROL) && KEY_PRESS(VK_OEM_PLUS) &&
		size_x.x < size_x.y) {

		size_x.x += (float)WIN_CENTER_X / 1 * DELTA;
		size_x.y -= (float)WIN_CENTER_X / 1 * DELTA;
		size_y.x -= (float)WIN_CENTER_Y / 1 * DELTA;
		size_y.y += (float)WIN_CENTER_Y / 1 * DELTA;
		
		orthographic = XMMatrixOrthographicOffCenterLH
		(
			size_x.x, size_x.y, // X좌표 : 0 ~ (창의 가로 크기)
			size_y.x, size_y.y, // Y좌표 : (창의 세로 크기) ~ 0
			-1.0f, 1.0f // Z좌표 : -1.0f ~ 1.0f(초기값)
		);
	}
	if (KEY_PRESS(VK_LCONTROL) && KEY_PRESS(VK_OEM_MINUS) &&
		size_x.x > -WIN_CENTER_X) {

		size_x.x -= (float)WIN_CENTER_X / 1 * DELTA;
		size_x.y += (float)WIN_CENTER_X / 1 * DELTA;
		size_y.x += (float)WIN_CENTER_Y / 1 * DELTA;
		size_y.y -= (float)WIN_CENTER_Y / 1 * DELTA;

		orthographic = XMMatrixOrthographicOffCenterLH
		(
			size_x.x, size_x.y, // X좌표 : 0 ~ (창의 가로 크기)
			size_y.x, size_y.y, // Y좌표 : (창의 세로 크기) ~ 0
			-1.0f, 1.0f // Z좌표 : -1.0f ~ 1.0f(초기값)
		);
	}

	projection->Set(orthographic);
	projection->SetVS(2);
}

void Environment::SetVerticalScreen()
{
	is_horizon_mode = false;
	projection = new MatrixBuffer();

	size_x = Vector2(0.0f, (float)WIN_HEIGHT);
	size_y = Vector2((float)WIN_WIDTH, 0.0f);


	orthographic = XMMatrixOrthographicOffCenterLH
	(
		size_x.x, size_x.y, // X좌표 : 0 ~ (창의 가로 크기)
		size_y.x, size_y.y, // Y좌표 : (창의 세로 크기) ~ 0
		-1.0f, 1.0f // Z좌표 : -1.0f ~ 1.0f(초기값)
	);


	projection->Set(orthographic);

	//view->SetVS(1);
	projection->SetVS(2);
}

void Environment::SetHorizonScreen()
{
	is_horizon_mode = true;
	projection = new MatrixBuffer();
	size_x = Vector2(0.0f, (float)WIN_WIDTH);
	size_y = Vector2((float)WIN_HEIGHT, 0.0f);

	orthographic = XMMatrixOrthographicOffCenterLH
	(
		size_x.x, size_x.y, // X좌표 : 0 ~ (창의 가로 크기)
		size_y.x, size_y.y, // Y좌표 : (창의 세로 크기) ~ 0
		-1.0f, 1.0f // Z좌표 : -1.0f ~ 1.0f(초기값)
	);


	projection->Set(orthographic);

	//view->SetVS(1);
	projection->SetVS(2);
}
