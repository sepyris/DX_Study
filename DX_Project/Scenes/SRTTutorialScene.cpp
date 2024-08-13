#include "framework.h"
#include "SRTTutorialScene.h"

SRTTutorialScene::SRTTutorialScene()
{
	world = new MatrixBuffer();
	// 이 Scene이 가지고 있는 기본적인 원점을 가리키는 World 행렬
	// 이번 프로젝트에선 딱히 쓸 일 없었고 앞으로도 없을 예정이나,
	// 혹여라도 원점으로 되돌리는 일이 필요할 때면 쓰일지도 모름

	// World 변환을 할 때 사용함

	view = new MatrixBuffer();
	// View 변환을 할 때 사용되는 행렬
	// 기본적으로 한참 나중에 "카메라(=시점)"를 다루게 될 때부터 사용하며,
	// 그 전까지는 직접 다루지 않고 기본값만 사용

	projection = new MatrixBuffer();
	// Projection 변환을 할 때 사용되는 행렬
	// 이에 대한 자세한 설명은 바로 밑에서 만든 행렬을 통해 설명

	// 이하의 행렬은 DX에서 제공하는 함수를 통해
	// "지금 우리가 출력할 화면이 
	// 전체 공간의 어디에서부터 어디에서까지를 다룬다고 선언하는,
	// 다시말해 화면의 좌표체계를 정의하는 행렬을 만드는 함수"
	Matrix orthographic = XMMatrixOrthographicOffCenterLH
	(
		0.0f, (float)WIN_WIDTH, // X좌표 : 0 ~ (창의 가로 크기)
		(float)WIN_HEIGHT, 0.0f, // Y좌표 : (창의 세로 크기) ~ 0
		-1.0f, 1.0f // Z좌표 : -1.0f ~ 1.0f(초기값)
		
		// 다른 것과는 달리 Y좌표는 입력하는 순서가 역전되어 있는데,
		// 여기에 적혀있는 값은 정확히는
		// 위에서부터 왼쪽/오른쪽/아래/위/(원점에서 우리가 보는 방향 기준)뒤/앞
		// 각각의 최대치를 설정한 것으로
		// 이 공간 내에 있는 오브젝트의 좌표를 확인해
		// 이 값들 중 어느 쪽에 더 가까운지를 통해 실제 출력되는 위치를 결정

		// 추가로, 왜 API처럼 왼쪽 위를 0으로 뒀냐면
		// 앞으로 우리가 사용하게 되는 몇몇 기능,
		// 특히 API 쪽에서 우리가 마우스 좌표를 가져왔을 때의 기능은
		// API에서 썼던 방식을 그대로 가져올 것이기 때문에
		// 호환성을 위해 일치시킨 것

	);
	// 이렇게 선언하는 것으로, 실제로 우리가 보는 화면의 좌표계가
	// API 때와 마찬가지로 왼쪽 위를 0,0으로 해서 창의 크기만큼의 절대좌표가 되도록
	// 만들 수 있다

	projection->Set(orthographic);
	// 그렇게 만들어진, 간단히 말하면 축척비율을 저장한 행렬이라 할 수 있는
	// 이 orthographic 행렬을 P 변환에 이용하게 될 버퍼에다가 저장

	worldBuffer = new MatrixBuffer();
	// 오브젝트들이 가지고 있는 World 행렬을 적용할 때
	// 지금 시점의 오브젝트들은
	// 자기가 가진 World 행렬을 직접 셰이더에 보내지 않으니
	// Scene 쪽에서 그 오브젝트들의 행렬을 받아 셰이더에 등록할 용도의 버퍼를
	// 새로 하나 만들어둔 것

	obj = new MyObject(Float2(WIN_WIDTH / 2 - 200
		, WIN_HEIGHT / 2 - 200));
	satelite = new MyObject(Float2(100, 20), Float2(1,1), 0,
						Float2(50,50));
	
	c = new SRTCircle(100, 6, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
}

SRTTutorialScene::~SRTTutorialScene()
{
	delete world;
	delete view;
	delete projection;
	delete worldBuffer;
	delete obj;
	delete satelite;
}

void SRTTutorialScene::Update()
{
	if (Control::Get()->Press(VK_RIGHT))
	// Control에서 만들어진 3개 함수 중 Press 여부를 검사하는 함수를 호출
	// 이 때 매개변수로 쓰는 값은 "가상 키 코드"에서 키보드의 각 키와 대응되는 값
	{
		obj->pos.x += DELTA * (float)WIN_WIDTH/3.0f;
	}
	if (Control::Get()->Press(VK_LEFT))
	{
		obj->pos.x -= DELTA * (float)WIN_WIDTH / 3.0f;
	}
	if (Control::Get()->Press(VK_UP))
	{
		obj->pos.y -= DELTA * (float)WIN_HEIGHT / 2.0f;
	}
	if (Control::Get()->Press(VK_DOWN))
	{
		obj->pos.y += DELTA * (float)WIN_HEIGHT / 2.0f;
	}
	if (obj->pos.x > WIN_WIDTH) {
		obj->pos.x = 0;
	}
	if (obj->pos.x < 0) {
		obj->pos.x = WIN_WIDTH;
	}
	if (obj->pos.y > WIN_HEIGHT) {
		obj->pos.y = 0;
	}
	if (obj->pos.y < 0) {
		obj->pos.y = WIN_HEIGHT;
	}
		

	/*
	obj->pos.x += 0.04f;
	
	// WVP 변환을 적용시킨 환경 하에서
	// 오브젝트의 위치를 바꾸고자 한다면
	// 위와 같이 pos의 값을 바꾸면 됨
	*/


	//obj->rot.z += 0.0001f;
	// 회전을 바꾸고 싶다면
	// 오브젝트가 가진 Transform의 멤버 중
	// rot의 z값만 바꾸는 것으로 회전을 해결 가능

	//타이머를 구현하기전에 메인루프가 진행되는 속도로 인해
	// 저렇게 작은값이 아니면 지나치게 빠르게 작동했었음
	// 이제는 Timer를 쓰니 원하는 속도를 직접 지정가능해짐
	obj->rot.z += 2 * M_PI * DELTA;



	obj->SetColor(Float4(0.0f, 1.0f, 0.0f, 1.0f));
	// 픽셀셰이더를 이제 다른 걸 쓰기 때문에,
	// 도형 자체에 이렇게 색을 설정하는 것으로
	// 우리가 원하는 색을 해당 도형에서 출력할 수 있도록 만들 수 있다

	Vector2 Up(0, -1);
	Vector2 Down(0, 1);
	Vector2 Left(-1, 0);
	Vector2 Right(1, 0);
	//이 4개의 벡터는 원점을 기준으로 정확히 상하좌우를 가리키는 단위 벡터
	//현 시점에서 전체공간의 원점,
	// 즉 좌표(0,0)에 xyz축 자체를 회전축으로 삼는점을 기준으로 해서
	// 전체공간에서의 위아래왼쪽오른쪽을 정의한 것
	// 
	// 월드 전체를 포괄하는 트랜스폼이 현재 없기 때문에
	// 직접 여기서 만들어주는것
	//
	

	if (Control::Get()->Press('W')) 
	{
		satelite->pos = Up * 120.0f;
		satelite->rot.z = Up.Angle() + M_PI_2;
	}
	if (Control::Get()->Press('S'))
	{
		satelite->pos = Down * 120.0f;
		satelite->rot.z = Down.Angle() + M_PI_2;
	}
	if (Control::Get()->Press('A'))
	{
		satelite->pos = Left * 120.0f;
		satelite->rot.z = Left.Angle() + M_PI_2;
	}
	if (Control::Get()->Press('D'))
	{
		satelite->pos = Right * 120.0f;
		satelite->rot.z = Right.Angle() + M_PI_2;
	}
	//기존의 obj의 데이터를 참조해 상하좌우를 체크했던것에서
	//전체 좌표계 기준의 상하좌우를 이용하는것으로 변경

	//satelite의 위치나 회전방향등을 결정할때,
	//이 satelite라는 오브젝트가 철저하게 obj의 월드 위에서
	//위치나 회전등을 반영하는것을 잊으면 안됨
	//->satelite의 방향등을 그냥 원점에 맞춰서 상하좌우로 위치랑 방향을 맟춰도
	//그걸 obj의 월드에 따라서 변주를 거치게 되므로
	//실제 전체 공간상에서 obj가 어느 방향을 가리키고있다 한들
	//satelite의 입장에선 그냥 자기가 기준으로 삼는 공간에서의 
	//그냥 바라보고자 하는쪽을 향하면 됨

	//1.현재 가리키는 방향 자체를 저장한후 이를 기반으로 실시간으로 위치를 지정하는 방식
	//2.자식 오브젝트의 위치는 어차피 부모오브젝트를 0,0으로 친 상태에서 계산한다는점을 이용해 해당 좌표공간상에서 상하좌우 똑바로 이용해주는방식
	//1과 2를 비교하면
	// 자식 오브젝트의 위치를 실시간으로 계산하기가 편하다면 1번이 좀더 구현하기 쉽고,그 외 다른 장점이 더 많음
	// 하지만 그런 계산이 불가능하다면 전자를 쓸수 없기 때문에
	// 2번 방식도 사용할줄 알아야함
	//


	obj->Update();
	// 오브젝트를 업데이트하기 전,
	// 해당 오브젝트가 가진 데이터를 변경시켜주는 것으로
	// 오브젝트의 위치나 회전 등을 관리할 수 있음
	// 위에서 변경된 값들을 Update 내부의 WorldTransform,
	// 혹은 후일 이를 개량할 WorldUpdate 함수에서 
	// SRT 변환 행렬에 반영

	satelite->Update(obj->GetWorld());
	// 이렇게 한 오브젝트의 업데이트에 다른 오브젝트의 월드를 넣는 것은
	// "이 오브젝트는 저 월드를 사용하는 오브젝트의 위치를 따라갑니다"
	// -> 이 오브젝트의 위치를 계산할 때 기준점을 0,0이 아니라
	// 해당 오브젝트의 위치로 삼겠다

	satelite->SetColor(Float4(0.4f, 0.4f, 0.4f, 1.0f));
}

void SRTTutorialScene::Render()
{
	world->SetVS(0);
	view->SetVS(1);
	projection->SetVS(2);
	// 이 행렬들을 셰이더에 보내어
	// WVP 변환을 하는 데 사용하도록 세팅

	// 여기서 SetVS에 들어가는 값은
	// 이 "상수 버퍼"가 셰이더의 어느 "슬롯"에 들어가는지를 표기하는 값
	// 자세한 설명은 (대충 폴더명\정점 셰이더\)VertexShader.hlsl

	worldBuffer->Set(*obj->GetWorld());
	worldBuffer->SetVS(0);
	// 위 2줄의 코드가 없을 때는
	// API에서 원점 역할을 했던 왼쪽 위에 삼각형이 위치해있고
	// 삼각형의 위치를 조절해봐도 위치가 변치 않는다는 것이 확인됨

	// 반면 이 코드를 추가하니
	// 생성자 측에서 위치를 바꿔줬던 것이 제대로 적용됨을 확인가능

	// -> 오브젝트의 위치를 표현하는 월드 행렬이
	// 오브젝트의 현재 위치를 가리키는 월드 행렬이 아니라
	// Scene 쪽에서 무대로 제공하고 있는 기본 월드로 세팅됐기 때문
	// 정확한 설명을 위해선 WVP 변환.h에서 설명

	obj->Render();
	satelite->Render();


	c->Render(); // Shape를 그대로 출력하는 것이라
	// Transform 오브젝트로 만들지 않은 내용
	// 따라서 이건 추가로 월드 세팅을 하지 않는 이상
	// 직전에 세팅한 월드 행렬을 그대로 이용하게 돼서
	// 별달리 세팅하지 않고도 정상적으로 출력되는 것

	// 앞으로는 Shape 자체를 직접 출력하는 일은 어지간하면 없기에
	// 이 부분은 크게 고치지 않고 넘어감
}

void SRTTutorialScene::PostRender()
{
}

/*
과제 : 지금 우리는 새로 갱신한 Vector2, Transform의 힘을 빌려서
특정 키를 입력하면 그 키에 대응하는 방향으로
한 오브젝트를 돌아다니는 다른 오브젝트의 위치를 바꾸고 있음

그러나, 우리가 의도한 코드는 해당 방향의 키를 누르면
오브젝트가 보고 있는 그 방향으로 이동하고 끝나야 하는데,
실제로는 누를 떄마다 그 방향에서 약간씩 달라지는 식으로 
이상하게 이동중(즉, 해당 방향으로 고정이 되지 않고 있음)

그 원인을 찾아 해결하는 것이 이번 과제
즉, 위를 누르면 위로 위성이 이동하여 고정되도록 하는 것,
그리고 그 위라는 것이 "우리가 보기에 위다"라고 인식되는 방향으로 만들 것

1) 회전하지 않는 상태에서 좌우는 멀쩡한데, 상하는 반대로 뒤집혀있음
이를 해결할 것
1+) 이를 해결하는 동시에 현재 이동하면서 이 오브젝트는 회전하지 않고 있는데
이 오브젝트도 누른 방향을 가리키도록 만들 것

2) 회전하는 도중에는 같은 키를 눌러도 (상대좌표가)한 자리에 고정되지 않고
계속해서 그 값이 변하는데
이를 안정화하여 키를 계속 누른다고 상대위치가 이동하지 않도록 만들어볼 것
(실습 도중에 의도치 않게 함정을 깔아버린 부분이 있으니 주의)
2+)1+를 여기에도 적용 성공시켜볼 것

++) 그 뒤엔 이번에 추가된(특히 Vector2와 관련된) 기능들을 이용해
뭔가 더 만들어보기


--)위에서 말한 함정을 깔았다는 것이 무엇인지,
그리고 그 외에 힌드를 줄 수 있는 것이 있다면 이에 대한 힌트들을
토요일 자정~일요일 오후 6시 사이에 예제와 함꼐 올릴 예정


*/