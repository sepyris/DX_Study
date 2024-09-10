#include "framework.h"



Program::Program()
{
	Create();
	CreateScene(6, 1);
	// 바로 이 부분을 통해 프로그램이 어떤 Scene을 사용할 것인지를 설정
	// DX를 다루는 초반 구간에서는 Scene을 많아봐야 하나만 사용할 것이므로
	// 그 Scene을 여기서 설정하고, 나중에 필요하면 기존 Scene은 놔둔 채
	// 새로운 Scene을 여기에 등록해서 사용하는 식으로 프로그램을 구성할 예정

	//Scene을 전부 추가 했으면 그중 어느 Scene를 가리킬 것인지 기록
}

Program::~Program()
{
	delete scene;
}

void Program::Update()
{
	Control::Get()->Update();
	Timer::Get()->Update();
	Environment::Get()->Update();
	
	//이렇게 어떤Scene을 가리키도록 할것인지
	//그 매커니즘을 만들어서 적용시키는것으로
	//프로그램이 어떤 Scene을 가리키도록 할것인지를 결정할수 있음
	
	//실제 게임에선 Scene외부에서 강제로 바꾸는게 아니라
	//Scene내부에서 이런저런 동작을 하면 다른 Scene으로 전환되도록 하는
	//즉 장면 전환을 Scene에서 담당하는 경우가 상당수

	//그렇기에 가급적이면 Scene내부에서 다른 Scene으로 전환해달라는 요청을 보낼수 있도록
	//Program에서 Scene을 전환 해달라는 함수를 만드는것이 나음
	
	
	scene->Update();
	CAM->Update();
}

void Program::Render()
{
	Device::Get()->Clear();
	
	// 원래는 프로그램에서 Render 함수가 호출되었을 때 이뤄져야 하지만
	// 지금 당장은 Scene을 한 번에 하나만 다루기 때문에
	// 그리고 Scene 내부에서 또 화면 초기화를 하기 때문에 여기서는 생략
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//위의 2개 함수를 이용해서 DX11/Windows환경의 새 프레임을 만들도록 세팅
	//세팅이 완료되면 창을 생성

	string fps = "FPS:" + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());
	ImGui::Text("Total Run Time:%f", Timer::Get()->GetRunTime());

	Vector2 screen = Vector2(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
	ImGui::SliderFloat2("screen_size", (float*)&screen, 0, WIN_WIDTH);
	ImGui::SliderFloat2("cam.pos", (float*)&CAM->pos, 0, WIN_WIDTH);
	

	scene->Render();
	scene->PostRender();

	ImGui::Render();//렌더링 = 출력하는 함수
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//그렇게 출력된 UI에 출력해야할 데이터들을 객체에서 표기 가능하도록 등록해주는 함수

	Device::Get()->Present();

}

void Program::Create()
{
	Device::Get(); // 싱글톤을 여기서 생성
	Control::Get();
	Timer::Get();
	Environment::Get();

	ImGui::CreateContext();//객체를 만들어내는 함수
	ImGui::StyleColorsDark();//창의 색상을 검은색 기반으로 설정하는 함수
	//이외에도 Light,Classic이라는 스타일도 있음

	ImGui_ImplDX11_Init(DEVICE, DVC);
	//DX11환경에서 사용하는 ImGui 라고 설정 및 초기화

	ImGui_ImplWin32_Init(hWnd);
	//윈도우 운영체제에서 사용하고 있다고 설정 및 초기화

	//이렇게 4줄을 작성하여 ImGui를 사용하겠다고 선언 및 초기화

}

void Program::Delete()
{
	Device::Delete();
}

void Program::CreateScene(UINT map_code, UINT area)
{
	delete scene;
	Environment::Get()->SetHorizonScreen();
	if (map_code == 1) {
		scene = new MapleIsland(area);
	}
	else if (map_code == 2) {
		scene = new MapleIslandField(area);
	}
	else if (map_code == 3) {
		scene = new StarBridgeWaitting(area);
	}
	else if (map_code == 4) {
		scene = new RunningWaitting(area);
	}
	else if (map_code == 5) {
		Environment::Get()->SetVerticalScreen();
		scene = new StarBridge();
	}
	else if (map_code == 6) {
		Environment::Get()->SetRunningScreen();
		scene = new Running();
	}
	if (scene == NULL) {
		scene = new MapleIsland(3);
	}
}
