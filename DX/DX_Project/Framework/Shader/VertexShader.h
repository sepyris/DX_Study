#pragma once

class VertexShader
	// �� �״�� ���� ���̴��� ����� Ŭ����
	// -> DX���� �����ϴ� ���� ���̴��� ���õ� Ŭ��������
	// �ս��� �����ϰ� �����ϱ� ���� Ŭ����
{
private:
	ID3D11VertexShader* VS;
	// ���� DX������ ���� ���̴��� ����ϴ� Ŭ����
	ID3D11InputLayout* input_layout;
	// �� ���� ���̴��� �� �����Ͱ� ��� ��������� �����ϴ� Ŭ����

	static unordered_map<wstring, VertexShader*> shader_data;
	//���α׷� ������ ������� VertexShader �ν��Ͻ����� ������ �� �ڷᱸ��

public:
	VertexShader(wstring file_loc,UINT type = 0, DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS);
	//VertexShader(LPCWSTR file_loc, DWORD flags)
	//	:VertexShader(file_loc, 0, flags) {};
	// �Ű� ������ ���ڿ��� ���̴� ������ �ʿ��� �÷��׸� �޴´�
	//�Ʒ��� �����ڴ� ���� �����ڸ� �̿��ϴ� Ŭ�������� ȣȯ�ǵ���
	//�ӽ÷� ���� ������ ���µ�
	//�� ������ �ణ �߸� �Ǿ ������ �����ڿ� �Ű������� ��ġ�� ��Ȳ�� ����� ��
	//�ű⿡ ������ ���� 2���� �Ű������� ����Ʈ���� �־ ������ �����߰�,
	//�� ſ�� �Ű������� wstring�� type�� �Է� ������
	//�Ű� ������ ��ġ�� �Ʒ��� �����ڰ� ��� ȣ��Ǿ�
	//�츮�� �ǵ��� ���̴� ������ ���� �������� ��ǥ���� ������ �ϳ�

	~VertexShader();

	static VertexShader* GetInstance(wstring file_loc, UINT type = 0);
	//�Է¹��� ���� �ּҸ� Ű������ ��Ƽ� �ν��Ͻ��� ��ȯ �ϴ� �Լ�
	static void Delete();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }

	void Set();
};