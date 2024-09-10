#include "framework.h"



Program::Program()
{
	Create();
	CreateScene(6, 1);
	// �ٷ� �� �κ��� ���� ���α׷��� � Scene�� ����� �������� ����
	// DX�� �ٷ�� �ʹ� ���������� Scene�� ���ƺ��� �ϳ��� ����� ���̹Ƿ�
	// �� Scene�� ���⼭ �����ϰ�, ���߿� �ʿ��ϸ� ���� Scene�� ���� ä
	// ���ο� Scene�� ���⿡ ����ؼ� ����ϴ� ������ ���α׷��� ������ ����

	//Scene�� ���� �߰� ������ ���� ��� Scene�� ����ų ������ ���
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
	
	//�̷��� �Scene�� ����Ű���� �Ұ�����
	//�� ��Ŀ������ ���� �����Ű�°�����
	//���α׷��� � Scene�� ����Ű���� �Ұ������� �����Ҽ� ����
	
	//���� ���ӿ��� Scene�ܺο��� ������ �ٲٴ°� �ƴ϶�
	//Scene���ο��� �̷����� ������ �ϸ� �ٸ� Scene���� ��ȯ�ǵ��� �ϴ�
	//�� ��� ��ȯ�� Scene���� ����ϴ� ��찡 ����

	//�׷��⿡ �������̸� Scene���ο��� �ٸ� Scene���� ��ȯ�ش޶�� ��û�� ������ �ֵ���
	//Program���� Scene�� ��ȯ �ش޶�� �Լ��� ����°��� ����
	
	
	scene->Update();
	CAM->Update();
}

void Program::Render()
{
	Device::Get()->Clear();
	
	// ������ ���α׷����� Render �Լ��� ȣ��Ǿ��� �� �̷����� ������
	// ���� ������ Scene�� �� ���� �ϳ��� �ٷ�� ������
	// �׸��� Scene ���ο��� �� ȭ�� �ʱ�ȭ�� �ϱ� ������ ���⼭�� ����
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//���� 2�� �Լ��� �̿��ؼ� DX11/Windowsȯ���� �� �������� ���鵵�� ����
	//������ �Ϸ�Ǹ� â�� ����

	string fps = "FPS:" + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());
	ImGui::Text("Total Run Time:%f", Timer::Get()->GetRunTime());

	Vector2 screen = Vector2(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
	ImGui::SliderFloat2("screen_size", (float*)&screen, 0, WIN_WIDTH);
	ImGui::SliderFloat2("cam.pos", (float*)&CAM->pos, 0, WIN_WIDTH);
	

	scene->Render();
	scene->PostRender();

	ImGui::Render();//������ = ����ϴ� �Լ�
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//�׷��� ��µ� UI�� ����ؾ��� �����͵��� ��ü���� ǥ�� �����ϵ��� ������ִ� �Լ�

	Device::Get()->Present();

}

void Program::Create()
{
	Device::Get(); // �̱����� ���⼭ ����
	Control::Get();
	Timer::Get();
	Environment::Get();

	ImGui::CreateContext();//��ü�� ������ �Լ�
	ImGui::StyleColorsDark();//â�� ������ ������ ������� �����ϴ� �Լ�
	//�̿ܿ��� Light,Classic�̶�� ��Ÿ�ϵ� ����

	ImGui_ImplDX11_Init(DEVICE, DVC);
	//DX11ȯ�濡�� ����ϴ� ImGui ��� ���� �� �ʱ�ȭ

	ImGui_ImplWin32_Init(hWnd);
	//������ �ü������ ����ϰ� �ִٰ� ���� �� �ʱ�ȭ

	//�̷��� 4���� �ۼ��Ͽ� ImGui�� ����ϰڴٰ� ���� �� �ʱ�ȭ

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
