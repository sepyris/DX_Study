cbuffer world : register(b0)
{
	matrix world;
}
cbuffer view : register(b1)
{
	matrix view;
}
cbuffer projection : register(b2)
{
	matrix projection;
}

struct VertexInput
{
	float4 pos : POSITION;
	float4 uv : UV;
	/*
	UV:텍스쳐(질감,그래픽 이론에서는 이미지 같은 것을 주로 이야기함)를 이용하기 위해
	텍스쳐의 어느 부분을 가져올것인지를 결정하는 2번째 좌표값 uvm
	pos라는 값이 3D공간상에서의 위치를 나타내기 위해 사용하는 지표 였다면
	UVM는 이 오브젝트 전체를 표시할때 이 꼭지점이 전체 그림중 어느 부분의 출력을 담당하고 있는것인지를 기록하는 또다른 좌표
	
	텍스쳐 파일에서의 x,y,z좌표을 이 u,v,m에 저장하는 것
	*/
};

struct PixelInput
{
	float4 position : SV_Position;
	float4 uv : UV;
};


PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.pos, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	
	output.uv = input.uv;

	return output;
	
}
//말 그대로 좌표만 다루니,
//기존 셰이더에서 좌표를 제외한 나머지를 전부 제거