#include "framework.h"
// 미리 컴파일된 헤더에 해당 헤더를 미리 등록해뒀다면
// 이후 코드 파일을 자동 생성했을 때 알아서 미리 컴파일된 헤더가 포함됨

VertexShader::VertexShader(wstring file_loc, UINT type, DWORD flags)
{
    ID3DBlob* vertexBlob;
    // 셰이더를 생성하기 위해 필요한 임시 객체

    D3DCompileFromFile(file_loc.c_str(), nullptr, nullptr, "VS",
        "vs_5_0", flags, 0, &vertexBlob, nullptr);
    // 매개변수를 통해 실제로 우리가 사용할 셰이더 파일을 이용,
    // DirectX 장치 쪽에서 해당 파일을 기반으로 하는 셰이더를 설치하는 함수
    
    // 셰이더 파일은 HLSL이라는 C++과는 다른 언어를 이용하는 파일이기 때문에
    // VS에서 이를 곧바로 컴파일할 수 없고, 
    // DX 측에서 파일을 이용해 컴파일하는 기능을 가지고 있어서
    // 이를 이용해 해당 파일을 실제 셰이더로 설치하는 과정을 거쳐야 함

    // 다른 부분을 특별히 기억할 것이 없고,
    // 이 함수의 매개 변수 중 "VS"와 "vs_5_0" 둘만 체크하면 됨

    // "VS" : Vertex Shader, 즉 정점 셰이더를 컴파일한다고 알리는 역할
    // "vs_5_0" : 셰이더 모델 5.0을 따르는 정점 셰이더
    // 이는 셰이더 파일의 속성에서 설정한 내용과 동일함
    // - 우리가 셰이더를 실제로 컴파일할 때 이 형식으로 셰이더를 만들 것이라서
    // 속성에서도 그와 같은 값으로 맞춰주는 것

    // 이 작업을 통해 임시 셰이더가 vertexBlob에 저장됨

    
    Device::Get()->GetDevice()->CreateVertexShader(vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), nullptr, &VS);
    // 로드한 파일을 이용해서,
    // 지금 이 프로젝트에서 만들어져 있는 DX 구동용 장치를 이용해
    // 실제 정점 셰이더를 동적 할당하여 VS에 저장

    // 정점 셰이더에서 사용될 데이터가 어떻게 구성되어 있는지
    // 셰이더 파일 측에서는 전혀 모르는 상황
    // (언어 자체가 C++과 HLSL로 다르기 때문에, 
    // 문법이나 자료형 등이 100% 호환되지 않음)
    // 그래서 단순히 데이터만 보내면 
    // 그 데이터의 몇번째 비트부터 몇번째 비트까지가
    // 셰이더에서 사용할 이 데이터인지 저 데이터인지를 분간할 수 없음
    // 그래서 이 layouts를 이용해 보내진 데이터의 어디부터 어디까지가
    // 어떤 데이터인지를 명시하는 역할 
    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", // 셰이더에 데이터가 입력될 때, 지금 다루는 부분의 데이터는
        // 이 이름을 가진 시멘틱에 들어갈 것이다
        // 시멘틱이라는 개념에 대한 설명은 파일 쪽에서 재설명
        0, // 시멘틱 인덱스 - 당장은 쓸 일이 없으니 
        // 추후 사용할 일이 생겼을 때 설명
        // 그 전까지는 0으로 고정
        DXGI_FORMAT_R32G32B32_FLOAT, 
        // "이 시멘틱엔 이 형식의 자료가 들어갈 예정"이라고 알려주는 부분,
        // 이게 실제 데이터와 일치하지 않으면 정상적으로 작동하지 않음
        // 이것 때문에 에러가 나는 경우가 굉장히 많으므로 신경써서 일치시켜줘야 함

        // 위 포맷의 뜻은
        // R, G, B 총 3가지의 자료를 사용한다는 의미
        // + 이 3가지 자료는 각각 32비트 / 32비트 / 32비트만큼의 데이터를 사용함
        // 그리고 이 데이터들은 실수(float)다

        // 지원하는 데이터의 형식엔 한도가 있으며,
        // 그 내용은 정의를 찾아가서 열거형의 내용을 보며 확인해볼 것
        0, // 어느 "슬롯"에 넣을지를 결정하는 부분
        // 이 슬롯에 대한 개념은 추후 직접 다루게 됐을 때 설명, 지금 당장은 사용하지 않는 개념
        0, // 전체 데이터(바이트) 중 어디에서부터 이 데이터가 시작되는지 그 인덱스를 명사
        // 인덱스를 명시하는 것이니 0부터 시작
        D3D11_INPUT_PER_VERTEX_DATA, 0} 
        // 2D를 공부하는 동안엔 다룰 일 없는 변수들이므로 패스

        // 정점 셰이더의 시멘틱 "POSITION"에는 이런 구조의 데이터가 들어간다고
        // 시스템에 알리는 부분

        // 그리고 지금의 셰이더는 단순 위치값만 저장하는 게 아니라
        // 색상까지 저장하므로
        // 추가로 색상을 저장하고 있다고 알릴 필요가 있음

        ,{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 
        12, // 이번에 명시하고 있는 데이터가 몇번째 바이트에서부터 시작하는지
        // 그 인덱스를 표기하는 부분
        // 상세내용은 위쪽의 각주 참조
        D3D11_INPUT_PER_VERTEX_DATA, 0}
        // 시멘틱 "COLOR"에 들어갈 데이터의 포맷
        // 12의 경우, 위쪽에서 선언되었던 첫번쨰 데이터의 포맷이
        // R32G32B32 = 총 12바이트이므로
        // 이 12바이트가 끝나고 난 뒤 13번째 바이트(=인덱스 12)부터 이 포맷의 데이터를 가리킨다
        // 라고 알려주는 내용
        // 만약 layouts에 이 2개 말고 
        // 다른 데이터를 더 저장하는 정점을 이용하게 된다면
        // 그 정점을 이용하는데 필요한 layouts를 구성하게 될 경우
        // 해당 layouts의 3번째 원소를 추가할 때는
        // 12 + COLOR의 총 용량인 16 = 28을 인덱스로 입력해야 할 것


        // 이렇게 정의된 데이터들이
        // 정점 셰이더에 입력된다는 것을 시스템에 알리는 것이 layouts의 역할
    };

    D3D11_INPUT_ELEMENT_DESC layouts_pos[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
        0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };



    UINT layoutSize;
    // 그렇게 규격을 지정한 layouts의 총 용량을 계산
    // 바로 밑의 CreateInputLayout 함수에서 
    // layouts의 총 용량을 직접 계산하지 못하기 때문에,
    // 우리가 미리 계산해서 알려줄 필요가 있기 때문

    //기존에는 어떤 레이아웃을 쓸것인지 이미 정해져있으니
    //그걸 그대로 갔다썻으면 됬지만.
    //이제는 사용할 정점에 따라서 다른 레이아웃을 쓸 예정이므로
    //일단 선언만 함

    switch (type) {//입력받은 타입,즉 어떤 정점을 이용할것인지에 따라 다른 레이아웃을 쓰도록 만듬
    case 0: {//색상과 좌표를 저장하는 정점을 이용할때
        layoutSize = ARRAYSIZE(layouts);
        Device::Get()->GetDevice()->CreateInputLayout(layouts, layoutSize,
            vertexBlob->GetBufferPointer(),
            vertexBlob->GetBufferSize(), &input_layout);
        break;
    }
          
    case 1: {//좌표 하나만 저장하는 정점을 이용할때
        layoutSize = ARRAYSIZE(layouts_pos);
        Device::Get()->GetDevice()->CreateInputLayout(layouts_pos, layoutSize,
            vertexBlob->GetBufferPointer(),
            vertexBlob->GetBufferSize(), &input_layout);
        break;
    }
          
    }

    
    // 그렇게 필요한 내용들이 전부 구성이 완료됐다면
    // 이 데이터들을 이용해 
    // 앞으로 이 셰이더에 들어갈 데이터는 이런 형식이라고
    // 안내판 역할을 해줄 input_layout을 동적 할당

    vertexBlob->Release();
    // 이제 이 임시 셰이더 버퍼는 필요없어졌으니 할당 해제
}



VertexShader::~VertexShader()
{
    Release();
}

void VertexShader::Release()
{
    VS->Release();
    input_layout->Release();
}

void VertexShader::Set()
{
    DVC->VSSetShader(VS, nullptr, 0);
    DVC->IASetInputLayout(input_layout);
}
