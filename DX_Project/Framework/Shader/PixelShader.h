#pragma once
class PixelShader
{
private:
	ID3D11PixelShader* PS;

	static unordered_map<wstring, PixelShader*> shader_data;

public:
	PixelShader(wstring file_loc, DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);
	// LPCWSTR = WCHAR = �����ڵ� �����ϴ� ���� �ڷ���
	~PixelShader();

	static PixelShader* GetInstance(wstring file_loc);
	//�Է¹��� ���� �ּҸ� Ű������ ��Ƽ� �ν��Ͻ��� ��ȯ �ϴ� �Լ�
	static void Delete();

	void Release();
	ID3D11PixelShader* GetPixelShader() { return PS; }

	void Set();
};