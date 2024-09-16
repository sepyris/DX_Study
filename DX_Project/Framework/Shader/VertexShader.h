#pragma once

class VertexShader
	// 말 그대로 정점 셰이더를 담당할 클래스
	// -> DX에서 제공하는 정점 셰이더와 관련된 클래스들을
	// 손쉽게 생성하고 세팅하기 위한 클래스
{
private:
	ID3D11VertexShader* VS;
	// 실제 DX에서의 정점 셰이더를 담당하는 클래스
	ID3D11InputLayout* input_layout;
	// 그 정점 셰이더에 들어갈 데이터가 어떻게 생겼는지를 정의하는 클래스

	static unordered_map<wstring, VertexShader*> shader_data;
	//프로그램 내에서 만들어질 VertexShader 인스턴스들을 저장할 맵 자료구조

public:
	VertexShader(wstring file_loc,UINT type = 0, DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS);
	//VertexShader(LPCWSTR file_loc, DWORD flags)
	//	:VertexShader(file_loc, 0, flags) {};
	// 매개 변수로 문자열과 셰이더 설정에 필요한 플래그를 받는다
	//아래쪽 생성자는 기존 생성자를 이용하던 클래스들이 호환되도록
	//임시로 만든 생성자 였는데
	//그 구성이 약간 잘못 되어서 위쪽의 생성자와 매개변수가 겹치는 상황이 생기게 됨
	//거기에 위쪽은 뒤쪽 2개의 매개변수에 디폴트값이 있어서 생략이 가능했고,
	//그 탓에 매개변수로 wstring과 type을 입력 했을때
	//매개 변수가 겹치는 아래쪽 생성자가 대신 호출되어
	//우리가 의도한 셰이더 세팅이 되지 않은것이 대표적인 원인중 하나

	~VertexShader();

	static VertexShader* GetInstance(wstring file_loc, UINT type = 0);
	//입력받은 파일 주소를 키값으로 삼아서 인스턴스를 반환 하는 함수
	static void Delete();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }

	void Set();
};