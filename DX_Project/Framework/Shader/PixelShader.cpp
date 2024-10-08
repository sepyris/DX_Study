#include "framework.h"

unordered_map<wstring, PixelShader*> PixelShader::shader_data;

PixelShader::PixelShader(wstring file_loc, DWORD flags)
{
    PS = NULL;
    // VertexShader 측과 하는 것은 똑같음 : 
    // 파일명을 받아서 그걸 이용해 셰이더를 컴파일하고
    // 그걸 토대로 만들어진 셰이더 인스턴스를 PS에 저장

    // 다만 픽셀 셰이더는 정점 셰이더에 비해서 
    // 셰이더를 만드는 데 필요한 데이터가 더 적어
    // 일부 내용만 실행하게 됨

    ID3DBlob* pixelBlob;
    D3DCompileFromFile(file_loc.c_str(), nullptr, nullptr, "PS",
        "ps_5_0", flags, 0, &pixelBlob, nullptr);

    Device::Get()->GetDevice()->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, &PS);
    pixelBlob->Release();
}

PixelShader::~PixelShader()
{
	Release();
}

PixelShader* PixelShader::GetInstance(wstring file_loc)
{
    if (shader_data.count(file_loc) > 0) {
        return shader_data[file_loc];
    }
    PixelShader* instance = new PixelShader(file_loc);

    shader_data[file_loc] = instance;

    return instance;
}

void PixelShader::Delete()
{
}

void PixelShader::Release()
{
	PS->Release();
}

void PixelShader::Set()
{
    DVC->PSSetShader(PS, nullptr, 0);
}
