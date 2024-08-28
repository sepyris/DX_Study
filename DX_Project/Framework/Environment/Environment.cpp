#include "framework.h"

Environment::Environment()
{
	CreateProjection();
	//WVP��ȯ�� View Projection��ȯ�� �����
	//��ȯ ��ĵ��� �� �������� �ʱ�ȭ

	CreateSamplerState();
	CreateBlendState();
	CreateRasterizerState();
	//�� ���� �⺻������ �ܺ� �ؽ��� ������ �ν� �� ����� ����
	//�����ؾ� �ϴ� state���� ���⼭ �ʱ�ȭ ��

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
		size_x.x, size_x.y, // X��ǥ : 0 ~ (â�� ���� ũ��)
		size_y.x,size_y.y, // Y��ǥ : (â�� ���� ũ��) ~ 0
		-1.0f, 1.0f // Z��ǥ : -1.0f ~ 1.0f(�ʱⰪ)
	);


	projection->Set(orthographic);

	//view->SetVS(1);
	projection->SetVS(2);
}

void Environment::CreateSamplerState()
//�Է¹��� �̹����� ��� ó���Ұ����� �����ϴ� state
//state:���¶�� ������ �׳� ������ �����ϴ� ����

{
	D3D11_SAMPLER_DESC desc = {};
	//������ �����ϴ� ������ Ŭ����
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	//�� �̹����� ������� ����,��Ȯ���� ���� �Ұ����� ����
	//����:������ �����͵� ���̿� �ִ�,�����Ͱ� ���� �������� ���� ����
	//�������Լ��� �̿��ؼ� �� �����͸� �����ϴ� �۾�

	//���� �̹����� ������ �ִ� �����ͷδ� ǥ������ ���ϴ� �κ�
	//(Ȯ�������� ������ �ȼ��� ���̿� �� ���ο� �ȼ��鿡 ���� �Ǵ»�,Ȥ�� �ݴ�� ��� ������ ������ �ȼ����� ��� �ȼ��� ���������)
	//�̸� �����ص� ���ǿ� �°� ��ó �ȼ����� �����͸� �̿��Ͽ� ���� ��
	//����� ���� ������ �������ִ°��� ����

	//�ַ� 2d������ ������ �� MIN_MAG_MIP_POINT��� ���� ����
	//3D������ MIN_POINT_MAG_MAP_LINEAR��� ���� ������ �̿��Ѵ�.

	desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//�Է¹��� �̹��� ������ ���� ��ǥ�� ��ġ ��ų��
	//UV���� 0�� 1�� ������ ������� ����
	//�׷���,�� ������ ����� �κп� ������� ���� ����ϵ��� �ϴ°��� ����
	//�� ��ħ�� ���ϴ� �κ�

	//���⼭ U,V,W�� ���� ���� ���� Transform ��ǥ�� x,y,z�� �ش�
	//�� U�� ���ο����� �׸� ó�� ���
	//V�� ���ο����� �׸� ó������� �����ϴ� �޴�

	//���⿡ ���ü� �ִ� ������ �����ʹ� ������ ����:
	//MIRROR:1�� ������ ���������� ���� ������ �ִ� ������ �������Ѽ� ���
	// (0 ~ -1������ ������ 0�� �������� ���� ���Ѽ� ���,
	//  1 ~ 2 ������ ������ 1�� �������� ���� ���Ѽ� ���,
	//  2 ~ 3 ������ ������ 2�� ��������,.....)
	// 
	//WRAP:0~1������ ������ �״�� �����ؼ� ���
	//BORDER:0~1������ ���� �ٱ��� ���α׷��� �⺻ �������θ� ä���,
	//       �ش���� �ȸ� ���� �̹����� �̿��� ���
	//CLAMP:0~1������ ���� ���� ���κ��� �����ϴ� �ȼ� �κ����� �� �ٱ��κ��� ���� ä���
	//      ���� x��ǥ(��Ȯ���� U) or Y��ǥ(V)�� �ִ� ��� �ȼ��� ���� �� �ϳ��� �ȼ��� ���� ä��� ���
	//MIRROR_ONCE:-1~1�� MIRROR �� �ܿ��� CLAMP�� ä��� ���

	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	//�� �̻��� �̹����� ���� ��ġ�� �����Ҷ�
	//� ��Ģ�� �̿��ؼ� ��� �̹����� ����ϵ��� �Ұ�����
	//�� ��Ģ�� ���ϴ� �κ�
	//��Ģ�� �������� �������� ���� ���� �̿�


	DEVICE->CreateSamplerState(&desc, &samplerstate);

	DVC->PSSetSamplers(0, 1, &samplerstate);


}

void Environment::CreateBlendState()
//����ó���� �����ϱ� ���� ����� �κ�
/*
���ݱ��� RGB���� �̿�������
�����δ� Alpha���̶�� �ϳ��� ���� �� ����

�� ���� ����ϴ� �κ��� ������ ��� �Ǵ����� �����ϴ� ��
0�̸� �ڱ��ڽ��� ���� ������ �ʰ� �� ���ʿ��ִ� �׷����� ���� �����ϵ��� �ϴ� ��
255�� ������ �� ��͵� ������ �ʰ� �ڱ��ڽ��� ���ߵ��� ��

DX�� �� �����̿��ؼ� �׷����� ������ ������

���� ������ ������ ó���ϱ� ���� ����ϴ�
�׸���ũ��(=ũ�θ�Ű)�� Ư���� ������ ĥ���� �κ��� ������ ������ ����ϵ��� �ϴ� �����
���� ó������� ����, �׷��� DX������ �̹���� �Ⱦ��°�?

������ ����:DX�� �װ� ���� �������� ����
�����ϰ��� �Ѵٸ� �����ϱ�� ��(�ȼ� ���̴� �ʿ��� �Էµ� ���� �� ũ�θ�Ű�� �ش�Ǵ� �����̶�� �ƿ� ���İ��� 0���� �����Ͽ� �� ���� �ݿ����� �ʵ��� �ϴ� ���)
�׷��� �̰� DX�� ���� �����ϴ� ������ƴϱ� ������
�˾Ƽ� ���İ����� ó���Ǵ� �̹�İ��� �޸� ���� �ϴ� ���̵��� ����� ����

�׷��� �� ���İ��� 0�϶� �������� ó���ϰڴٴ������� ������
*/

//�׷��� ���İ��� �ٷ�� ���� �Ʒ��� ���� ������ ���ִ°�
//�Ʒ��� ������� �׻� ���� ���� ���
//�׸��� ����� �����ϰ��� �Ѵٸ�
//���� �̹����� ����� ������ �ִ� ���İ��� 0���� �ٲٸ� ��

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
//�׷��� ���������ο��� �����޴� Rasterizer���̴��ܰ踦 ���⼭ ó��
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
			size_x.x, size_x.y, // X��ǥ : 0 ~ (â�� ���� ũ��)
			size_y.x, size_y.y, // Y��ǥ : (â�� ���� ũ��) ~ 0
			-1.0f, 1.0f // Z��ǥ : -1.0f ~ 1.0f(�ʱⰪ)
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
			size_x.x, size_x.y, // X��ǥ : 0 ~ (â�� ���� ũ��)
			size_y.x, size_y.y, // Y��ǥ : (â�� ���� ũ��) ~ 0
			-1.0f, 1.0f // Z��ǥ : -1.0f ~ 1.0f(�ʱⰪ)
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
		size_x.x, size_x.y, // X��ǥ : 0 ~ (â�� ���� ũ��)
		size_y.x, size_y.y, // Y��ǥ : (â�� ���� ũ��) ~ 0
		-1.0f, 1.0f // Z��ǥ : -1.0f ~ 1.0f(�ʱⰪ)
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
		size_x.x, size_x.y, // X��ǥ : 0 ~ (â�� ���� ũ��)
		size_y.x, size_y.y, // Y��ǥ : (â�� ���� ũ��) ~ 0
		-1.0f, 1.0f // Z��ǥ : -1.0f ~ 1.0f(�ʱⰪ)
	);


	projection->Set(orthographic);

	//view->SetVS(1);
	projection->SetVS(2);
}
