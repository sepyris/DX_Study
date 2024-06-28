#pragma once
class PixelShader
{
private:
	ID3D11PixelShader* PS;

public:
	PixelShader(LPCWSTR file_loc, DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);
	// LPCWSTR = WCHAR = 유니코드 지원하는 문자 자료형
	~PixelShader();

	void Release();
	ID3D11PixelShader* GetPixelShader() { return PS; }

	void Set();
};