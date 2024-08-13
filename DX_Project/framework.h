#pragma once

// framework.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <windowsx.h>

// 주로 사용할 상수들을 지정하는 매크로문
#define WIN_START_X 200
#define WIN_START_Y 200
// 창이 처음에 만들어질 위치를 지정
// 만약 본 코드를 받아서 사용하는데 화면이 안 나온다면
// 이 값을 100/100으로 바꿔둘 것

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
// 칭의 크기로 삼을 값을 지정

#define WIN_CENTER_X (WIN_WIDTH * 0.5f)
#define WIN_CENTER_Y (WIN_HEIGHT * 0.5f)
// 화면 중앙의 좌표를 매크로로서 손쉽게 이용할 수 있도록
// 매크로 상수 선언

#define DEVICE Device::Get()->GetDevice()
#define DVC Device::Get()->GetDeviceContext()
#define DELTA Timer::Get()->GetDeltaTime()
#define KEY_PRESS(x) Control::Get()->Press(x)
#define KEY_UP(x) Control::Get()->Up(x)
#define KEY_DOWN(x) Control::Get()->Down(x)
#define CAM Environment::Get()->GetMainCamera()
#define SCREEN_SIZE_X Environment::Get()->GetScreenSizeX()
#define SCREEN_SIZE_Y Environment::Get()->GetScreenSizeY()

#define LERP(s,e,t)(s+(e-s)*t)
//선형보간을 계산하는 식을 매크로 함수화


// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#define _USE_MATH_DEFINES // math.h에 정의된 몇몇 상수를 이용하기 위해
// 반드시 math.h를 포함하기 전에 선언해둬야 하는 키워드
#include <math.h>
#include <string>
#include <random>
#include <unordered_map>

// DirectX 11을 이용하기 위한 라이브러리
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//ImGui외부 라이브러리
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"
//이3개 파일은 ImGui라는 외부 라이브러리를 이용하기 위해 필요한 구문

//DirectXTex 외부 라이브러리
#pragma comment(lib, "dxguid.lib")
#include "../DirectxTex/DirectXTex.h"
//DirectXTex라는 라이브러리를 사용하기 위해 필요한 구문
//DirectXTex란(DirectX texture processing library)
//DX에서 이미지를 다루기 쉽게 만들어주는 라이브러리
//자세한것은 Program쪽에서 다룸
//



using namespace std;
using namespace DirectX;
// DX 쪽의 클래스들은 상당수 DirectX라는 네임스페이스 안에 있음
// 따라서 이것들을 항상 사용할 예정이니 아예 해당 네임스페이스를 상시 시용

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
// XMFLOATX 시리즈 : DX에서 지원하는, 실수를 X개 저장하는 구조체
// 이 형식을 이용하는 DX 쪽의 함수가 많기 때문에,
// 이를 편하게 이용하기 위해 typedef를 이용하여 축약

typedef XMMATRIX Matrix;
// XMMATRIX : DX에서 지원하는, 행렬을 저장하는 용도의 유니온(구조체)

// 이 아래의 내용들은 우리가 직접 만들어낸 프레임워크의 헤더들
// 프레임워크를 새로이 구성할 때마다 추가될 예정
// 이 아래에 추가되는 헤더들은 반드시 올바른 순서대로 추가되어야 함

// Framework Header
/// Utility Header
#include"Framework/Utility/Singleton.h"
#include"Framework/Utility/Control.h"
#include"Framework/Utility/Timer.h"

// Buffer Header
#include"Framework/Buffer/VertexBuffer.h"
#include"Framework/Buffer/IndexBuffer.h"
#include"Framework/Buffer/ConstBuffer.h"
#include"Framework/Buffer/GlobalBuffer.h"

// Math Header
#include"Framework/Math/Vector2.h"
#include"Object/Shape/Vertex.h"
#include"Framework/Math/Transform.h"

// System Header
#include"Framework/System/Device.h"

/// Shader Header
#include"Framework/Shader/VertexShader.h"
#include"Framework/Shader/PixelShader.h"


// Object Header 
#include"Object/Shape/Shape.h"
#include"Object/Shape/Triangle.h"
#include"Object/Shape/SRTCircle.h"
#include"Object/Shape/RectUV.h"

//Collider Header
#include "Framework/Collision/Collider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/CircleCollider.h"

//Render Header
#include"Framework/render/Texture.h"
#include"Framework/render/Frame.h"
#include"Framework/render/Clip.h"


// Transform Header
#include"Object/Transform/TransformList.h"

//Environment Header
#include"FrameWork/Environment/Camera.h"
#include"FrameWork/Environment/Environment.h"


// Scenes Header
#include"Scenes/Scene.h"
#include "Scenes/SceneList.h"

// Program Header
#include"Program/Program.h"

extern HWND hWnd;
extern Vector2 mouse_pos;
extern Program* program;
#endif //PCH_H
