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
	UV:�ؽ���(����,�׷��� �̷п����� �̹��� ���� ���� �ַ� �̾߱���)�� �̿��ϱ� ����
	�ؽ����� ��� �κ��� �����ð������� �����ϴ� 2��° ��ǥ�� uvm
	pos��� ���� 3D�����󿡼��� ��ġ�� ��Ÿ���� ���� ����ϴ� ��ǥ ���ٸ�
	UVM�� �� ������Ʈ ��ü�� ǥ���Ҷ� �� �������� ��ü �׸��� ��� �κ��� ����� ����ϰ� �ִ°������� ����ϴ� �Ǵٸ� ��ǥ
	
	�ؽ��� ���Ͽ����� x,y,z��ǥ�� �� u,v,m�� �����ϴ� ��
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
//�� �״�� ��ǥ�� �ٷ��,
//���� ���̴����� ��ǥ�� ������ �������� ���� ����