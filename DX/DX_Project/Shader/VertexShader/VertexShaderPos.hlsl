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
};

struct PixelInput
{
	float4 position : SV_Position;
};


PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.pos, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	

	return output;
	
}
//�� �״�� ��ǥ�� �ٷ��,
//���� ���̴����� ��ǥ�� ������ �������� ���� ����