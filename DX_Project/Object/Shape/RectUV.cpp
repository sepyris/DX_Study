#include "framework.h"

RectUV::RectUV(Vector2 size, Vector2 start_uv, Vector2 end_uv, D3D11_PRIMITIVE_TOPOLOGY type)
	:Shape(),type(type)
{
	Float2 half_size = Float2(size.x / 2.0f, size.y / 2.0f);
	//이 도형이 입력받은 크기를 절반으로 쪼갠뒤
	//이를 꼭지점의 위치를 정의하기 위한 값으로 사용

	Float2& hf = half_size;
	//레퍼런스 기능을 이용해서 이 half_size라는 변수에 hf라는 별명을 붙임
	
	vertices_uv.emplace_back(-hf.x, -hf.y, start_uv.x, start_uv.y);
	vertices_uv.emplace_back(+hf.x, -hf.y, end_uv.x, start_uv.y);
	vertices_uv.emplace_back(-hf.x, +hf.y, start_uv.x, end_uv.y);
	vertices_uv.emplace_back(-hf.x, +hf.y, start_uv.x, end_uv.y);
	vertices_uv.emplace_back(+hf.x, -hf.y, end_uv.x, start_uv.y);
	vertices_uv.emplace_back(+hf.x, +hf.y, end_uv.x, end_uv.y);
	//위와 같이 꼭지점을 입력함
	//start_uv,end_uv :현재 세팅된 텍스쳐 데이터에서 어느부분부터 어느부분까지를 사용하겠다는뜻
	//그 범위는 0~1까지
	//2D기준 0,0이 텍스처의 왼쪽위 끝
	//1,1이 오른쪽아래끝
	//즉 디폴트값은 텍스쳐(이미지)전체를 이용하겠다는 뜻이 됨
	// 
	//다만 0과 1의 값을 벗어난다고 해서 에러가 발생하지는 않는다
	//왜 그렇게 되는지는 CreateSamplerState함수에서 설명

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	VS = new VertexShader(L"Shader/VertexShader/VertexShaderUV.hlsl",2,flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShaderUv.hlsl");

	VB = new VertexBuffer(vertices_uv.data(), sizeof(VertexUV),
		vertices_uv.size());
	CB = new ColourBuffer();

}

RectUV::~RectUV()
{
	delete VS;
	delete PS;
	delete VB;
	delete CB;
}

void RectUV::Render()
{
	CB->SetPS(0);
	VB->Set(type);
	VS->Set();
	PS->Set();
	DVC->Draw(vertices_uv.size(), 0);

	//꼭지점을 이루는 값 잧체에 이미지의 어디를 출력하라는것인지가 결정되어 있으니
	//그걸 그냥 이용하면 ok

}
