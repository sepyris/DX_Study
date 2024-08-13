cbuffer Color : register(b0)
{
	float4 color;
}

struct PixelInput
{
	float4 position : SV_Position;
};


float4 PS(PixelInput input) : SV_TARGET
{
	return color;
	//이번엔 꼭지점에서 색상을 아예 다루지 않으니
	//색상버퍼를 통해 전달된 색상을 그대로 이용
}
