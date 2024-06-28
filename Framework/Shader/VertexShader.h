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

public:
	VertexShader(wstring file_loc,UINT type = 0, DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);
	VertexShader(LPCWSTR file_loc, DWORD flags)
		:VertexShader(file_loc, 0, flags) {};
	// �Ű� ������ ���ڿ��� ���̴� ������ �ʿ��� �÷��׸� �޴´�
	~VertexShader();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }

	void Set();
};