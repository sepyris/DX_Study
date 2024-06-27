#include "framework.h"
#include "ObjectTrialScene.h"

ObjectTrialScene::ObjectTrialScene()
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	// ���̴� ������ �ʿ��� �÷��׸� �̸� ����

	VS = new VertexShader(L"Shader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/VertexShader.hlsl", flags);
	// ���� ���̴��� �ȼ� ���̴��� ���̴� �ּҰ� �ִ� ���Ͽ� ����
	// �߰���,
	// ������ζ�� �� ���̴����� ���̴��� �̿��ؼ� ����� ������ ����ϴ�
	// Ŭ���� �� ��ü�� ������ �־�� �� �����̳�
	// �̹� �ð������� �״�� �� �ʿ��� �̿���

	// ������� ������ ������ ��������

	//t = new Triangle(0.5f, 0.5f);

}

ObjectTrialScene::~ObjectTrialScene()
{
	delete t;
	delete VS;
	delete PS;
}

void ObjectTrialScene::Update()
{
}

void ObjectTrialScene::Render()
{

	UINT stride = sizeof(Vertex);
	UINT offset = 0;


	DVC->VSSetShader(VS->GetVertexShader(), nullptr, 0);
	DVC->PSSetShader(PS->GetPixelShader(), nullptr, 0);
	// ����̽��� ���� ���̴��� �ȼ� ���̴��� ����
	// �̷��� DeviceContext�� ������ ���� ������
	// �̸� �ҷ����� �ڵ� �״�� ���� �� �ʹ� �� ��ȿ����
	// �׷��� ��ũ�θ� �����Ͽ� �ϸ� �ִ��� ª�� ���� ��

	DVC->IASetInputLayout(VS->GetInputLayout());
	// �� Scene�� ����ϰ� �ִ� VS�� ���ο� �ִ� input_layout�� ������
	// device_context�� ����, ������ � �ڷᰡ ���̴��� �Ѿ����
	// ��ġ�� �˸�

	//DVC->IASetVertexBuffers
	//(0, 1, t->GetBuffer(), &stride, &offset);
	// �ﰢ���� ����ϴ� �ν��Ͻ��� t�� ������ �ִ� ������
	// ����Ǿ� �ִ� ���۸� ����̽��� ����
	DVC->IASetPrimitiveTopology(t->GetType());
	// �ﰢ���� �����ϰ� �ִ� ������ �׸� ����� ����̽��� ����

	DVC->Draw(t->GetVertexSize(), 0);
	// �غ� �� �������� ����̽��� ���ݱ��� �Է��ߴ� �����͵��� ���� �׷���

}
