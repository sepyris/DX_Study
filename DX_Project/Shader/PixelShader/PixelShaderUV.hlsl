cbuffer Color : register(b0)
{
	float4 color;
}

struct PixelInput
{
	float4 position : SV_Position;
	float4 uv : UV;
	/*
	지금 셰이더 파일에서 데이터들을 다루는것이 실수 4개를 이용하도록 만들어져 있음
	셰이더는 기본적으로 4의 배수의 데이터밖에 처리하지 못함
	만약 들어온 데이터가4의 배수가 아니라면 연산 자체를 하지 못해 그래픽 출력을 못함
	그때문에 4바이트 크기인 float라 하더라도 4개단위를 맟춰줘야 정상적으로 동작할것이라 기대 가능
	
	*/
};

SamplerState samp : register(s0);
//samp:텍스쳐데이터에서 특정한 한 점을 뽑아와 그 점의 정보를 임시로 저장하는 버퍼
Texture2D map : register(t0);
//map:samp에 저장된 각 픽셀의 값들을
//프로그램(그래픽)에서 출력할 위치에 맞게 저장하는 버퍼

//이 둘을 합쳐서 최종적으로 그려낼 그래픽 데이터를 결정하는 버퍼로 이용,
//이미지등의 텍스쳐 파일에서 정보를추출해 모니터에 출력할 그래픽으로 바꾸는 용도

//여기에 들어올 텍스쳐 데이터는 C++쪽 코드에서 전달됨

//DirectTex는 여기에 들어오게될 데이터를 다루기 위해 사용하는 라이브러리

float4 PS(PixelInput input) : SV_TARGET
{
    return map.Sample(samp, (float2)input.uv) * color;
	//텍스쳐 파일에서 samp를 통해 들어온 데이터를 uv값에 해당하는 map의 좌표에 저장
	//추가로 만약 생상버퍼에 색이 들어와 있다면 이를 곱해서
	//그렇게 가져온 이미지 데이터에 필터 비슷한 느낌으로 색을 보정할수 있음
}
