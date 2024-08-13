#pragma once
class PixelShader
{
private:
	ID3D11PixelShader* PS;

	static unordered_map<wstring, PixelShader*> shader_data;

public:
	PixelShader(wstring file_loc, DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);
	// LPCWSTR = WCHAR = 유니코드 지원하는 문자 자료형
	~PixelShader();

	static PixelShader* GetInstance(wstring file_loc);
	//입력받은 파일 주소를 키값으로 삼아서 인스턴스를 반환 하는 함수
	static void Delete();

	void Release();
	ID3D11PixelShader* GetPixelShader() { return PS; }

	void Set();
};