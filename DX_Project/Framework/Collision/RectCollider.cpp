#include "framework.h"


RectCollider::RectCollider(Vector2 size)
	: size(size)
{
	type = TYPE::RECT;

	CreateLine();
}

RectCollider::~RectCollider()
{
	delete VB;
}

void RectCollider::CreateLine()
//이 충돌 판정의 범위를 화면에 표기하기 위해
//어떤 정점을 사용하는지 정의 하는 부분
{
	Vector2 half = Size() * 0.5f;

	vertices.emplace_back(-half.x, +half.y);
	vertices.emplace_back(-half.x, -half.y);
	vertices.emplace_back(+half.x, -half.y);
	vertices.emplace_back(+half.x, +half.y);
	vertices.emplace_back(-half.x, +half.y);
	//시계 반대방향으로 정점이 만들어져있지만
	//삼각형이 아니라 선을 긋는것이라 시계방향을 지킬필요가 없음

	VB = new VertexBuffer(vertices.data(), sizeof(VertexPos), vertices.size());
}

RectCollider::ObbDesc RectCollider::GetObbDesc()
//회전된 상태에서의 충돌판정의 범위를 정의하기 위해 필요한 데이터를 모아둔 구조체
{
	obb_desc.pos = GlobalPos();//충돌 판정의 전체 공간상에서의 좌표
	obb_desc.half_size = Size() * 0.5f;//충돌판정의 크기 좌우 및 상하의 절반
	obb_desc.Axis[0] = Right();
	obb_desc.Axis[1] = Up();
	//이 충돌 방향이 현재 바라보는 방향을 기준으로 각각 오른쪽 위를 가리키는 단위 벡터

	return obb_desc;
}

bool RectCollider::isPointCollision(Vector2 point)
//입력받은 점이 사각형 내부에 있는지 = 충돌하는지 검사하는 함수
{
	Vector2 half = Size() * 0.5f;
	float left = GlobalPos().x - half.x;
	float right = GlobalPos().x + half.x;
	float top = GlobalPos().y - half.y;
	float bottom = GlobalPos().y + half.y;
	//이 사각형의 크기를 확인한뒤
	//상하좌우 각각의 좌표를 실제 공간상에서의 좌표로서 확인한후
	//거기에 위에서 구한 크기를 이용해 각 꼭지점의 좌표,
	//즉 이 사각형의 범위를 계산

	//그렇게 계산된 범위안에 입력된 좌표가 들어있는지 검사

	if (point.x > left && point.x < right) {
		if (point.y > top && point.y < bottom) {
			return true;//들어와 있다면 충돌한것
		}
	}

	return false;//그렇지 않으면 충돌하지 않은것
}

bool RectCollider::isCircleCollision(CircleCollider* collider)
{
	return isOBB(collider);
}

bool RectCollider::isRectCollision(RectCollider* collider, Vector2* overwrap)
{
	//사각형 범위와 사각형 범위가 충돌했다고 한다면
	//이는 정확히 어떤 상태가 되는가?
	//->그 정확히 어떤 상태가 되는것인지를 다루는게 충돌 이론
	//즉 어떤 방식으로 충돌을 처리할것이냐에 따라
	//이 충돌 했다 를 정의 하는방식이 서로 전혀 달라지게 됨

	//예를들어 사각형이 서로 충돌 했다,즉 겹치는 부분이 있다는 이야기는
	//서로의 사각형의 영역중 일부가 상대방의 영역을 침범하고 있다는 이야기니
	//그렇다면 서로의 사각형을 구성하는 꼭지점중 적어도 하나는 상대방의 영역에 들어가있는 상황이라고 정의 하는것이 가능함

	//그러므로 일단 상대방의 꼭지점을 확인,그 꼭지점이 내 안에 들어와 있는지를 검사하는 알고리즘을 만들어두어
	//이를 이용해 검사하는 방법이 있음

	//다만 이방법을 쓰기 위해선 먼저 점과의 충돌을 다룰 필요가 있음
	
	//이 방식의 핵심 아이디어는 이것:
	//어지간하면 서로 충돌 했을 경우에 두 사각형중 적어도 하나의 꼭지점은 상대방의 내부에 들어가 있을것이니
	//나의 꼭지점4개중 하나가 상대방에게 들어가 있거나
	//상대방의 꼭지점4개중 하나가 내게 들어와 있거나
	//이 둘중 하나에 해당 된다면 충돌한것이다.


	/*
	이라는 알고리즘을 다음과 같이 구성했지만,
	실제로는 꼭지점이 항상 상대방에게 위치하지 않았더라도 충돌하는 상황은 발생함
	
	->따라서 이 알고리즘은 충돌판정에 제대로 쓸수 없음
	그렇다면 어떻게 해야 하는가?
	
	->사용가능하다고 검증된 알고리즘을 쓰면됨
	그것이 AABB알고리즘과 OBB알고리즘

	둘중 어느 알고리즘을 쓸것인지는 상황에 따라 다르며
	그 다른 상황을 매개변수에 입력 하냐 마냐를 통해 제어가 가능하니
	여기서는 조건문으로 어느 알고리즘을 사용할것인지 결정

	//일단 나 자신의 범위 꼭지점을 구한뒤
	Vector2 half = Size() * 0.5f;
	float left = GlobalPos().x - half.x;
	float right = GlobalPos().x + half.x;
	float top = GlobalPos().y - half.y;
	float bottom = GlobalPos().y + half.y;

	Vector2 opp_half = collider->Size() * 0.5f;
	float opp_left = collider->GlobalPos().x - opp_half.x;
	float opp_right = collider->GlobalPos().x + opp_half.x;
	float opp_top = collider->GlobalPos().y - opp_half.y;
	float opp_bottom = collider->GlobalPos().y + opp_half.y;
	//상대방의 범위도 같은 방식으로 구함

	if (collider->isPointCollision(Vector2(left,top))||
		collider->isPointCollision(Vector2(left, bottom)) ||
		collider->isPointCollision(Vector2(right, top)) ||
		collider->isPointCollision(Vector2(right, bottom)) ||

		isPointCollision(Vector2(opp_left, opp_top)) ||
		isPointCollision(Vector2(opp_left, opp_bottom)) ||
		isPointCollision(Vector2(opp_right, opp_top)) ||
		isPointCollision(Vector2(opp_right, opp_bottom))
		) 
	{
		//그렇게 구한 나와 상대방의 각각의 꼭지점중 하나라도 상대방의 영역을 침범하고 있다면 
		return true;//충돌한것으로 취급
	}


	return false;//아무꼭지점도 침범하지 않고 있다면 충돌하지 않았음
	*/

	if(overwrap != NULL)
		return isAABB(collider, overwrap);
	else
		return isOBB(collider);
}

bool RectCollider::isAABB(RectCollider* rect, Vector2* overwrap)
/*Axis - Aligned Bounding Box의 줄임말
축이 나란한 경계상자-> 충돌판정을 이루는 모든 상자의 변들이
기본축과 평행하도록 만들어졌을경우 사용하는 알고리즘

기본적으로는 매우 빠르다는 점이 제일 큰 장점이나
회전하지 않는 경우에만 정상적으로 동작한다는것이 제일 큰 단점

*/
{
	float max_left = max(LeftVX(), rect->LeftVX());
	float min_right = min(RightVX(), rect->RightVX());
	float max_top = max(TopVX(), rect->TopVX());
	float min_bottom = min(BottomVX(), rect->BottomVX());
	//2개의 사각형의 충돌판정을 이용해,
	//둘중 더 큰 왼쪽/위 좌표와
	//둘중 더 작은 오른쪽/아래 좌표를 계산

	//이렇게 하여 두 사각형이 겹쳐있는 범위를 정의할수 있게 됨
	//다만 지금 당장은 그 범위 자체를 구할 필요는 없으니
	//해당 범위의 가로세로 각각의 크기만 구하면 됨
	Vector2 obstackle = Vector2(min_right - max_left, min_bottom - max_top);
	//이렇게 만들어진 사각형의 변의 길이를 검사하여
	//둘중 하나라도 0 이하라면 이 사각형은 실존하지 않는다고 판단할수 있음
	//반대로 둘다 양수라면 그만큼 실제로 충돌하는 영역이 있다는 뜻

	if (obstackle.x>0.f&& obstackle.y > 0.f) {
		//그 영역이 구해졌다면 = 충돌 했다면
		if (overwrap != NULL) {
			*overwrap = obstackle;
		}
		// overwrap 이 함수 밖 즉 이함수를 호출한곳에서
		//충돌 범위가 정확히 어떻게 되나 그 데이터를 받아가기 위한포인터
		// 만약 이게 입력 되어 있다면 위에서 구한 충돌 범위를 여기다 입력하는식으로 호출한 위치에 반환
		return true;
		
	}
	return false;

	/*
	이 방식은 충돌여부를 검사하는 방식이 무조건 회전하지 않고
	각각의 변이 x축,y축과 평행하다는 걸 전제로 만들어진 검사 방법

	이때문에
	1.만약 둘중 하나라도 회전이 이뤄졌다면
	그걸 고려하지 않은 지금의 코드로는
	그래픽과 실제 충돌판정이 일치하지 않게 되는것

	2.일치하게 하려고 해도, 이 알고리즘 자체가
	서로 동일한 축을 이용해서 검사하는것을 기본 전제로 만든 알고리즘이라
	서로 회전한 정도가 다르면 이 알고리즘을 그대로 쓸수 없음

	->지금 구현한 AABB로는 2D에서의 회전하지 않은 사각형끼리의 검사만 가능
	


	*/
}

bool RectCollider::isOBB(RectCollider* rect)
/*Oriented Bounding Box의 줄임말
지향성 경계 상자 - 회전 방향을 따라가는 충돌 판정 처리법

두 물체를 어떤 축에 "투영(사영)"시켰을때
투영된 두 물체가 서로 겹치지 않는 다면
두 물체 사이를 가로질러 완벽히 분리 시키는 무언가의 분리축이 하나라도 있는것이다
라는 논리로 그런 분리축이 존재하는지를 여러축을 통해 검사해서
하나라도 존재한다면 서로 충돌하지 않고 분리된것
존재하지 않는다면 충돌한 것이라고 판단하는 충돌 검사 알고리즘
*/
{
	
	ObbDesc this_obb = GetObbDesc();
	ObbDesc rect_obb = rect->GetObbDesc();

	Vector2 nea1 = this_obb.Axis[0];
	Vector2 nea2 = this_obb.Axis[1];
	Vector2 ea1 = nea1 * this_obb.half_size.x;
	Vector2 ea2 = nea2 * this_obb.half_size.y;

	Vector2 neb1 = rect_obb.Axis[0];
	Vector2 neb2 = rect_obb.Axis[1];
	Vector2 eb1 = neb1 * rect_obb.half_size.x;
	Vector2 eb2 = neb2 * rect_obb.half_size.y;
	Vector2 distance = this_obb.pos - rect_obb.pos;

	//테스트축:nea1(A.RIGHT())
	float lengthA = ea1.GetLength();
	float lengthB = separateAxis(nea1, eb1, eb2);
	float length = abs(Vector2::Dot(distance, nea1));
	if (length > lengthA + lengthB) {
		return false;
	}

	//테스트축:nea2(A.UP())
	lengthA = ea2.GetLength();
	lengthB = separateAxis(nea2, eb1, eb2);
	length = abs(Vector2::Dot(distance, nea2));
	if (length > lengthA + lengthB) {
		return false;
	}
	//테스트축:neb1(B.Right())
	lengthA = eb1.GetLength();
	lengthB = separateAxis(neb1, ea1, ea2);
	length = abs(Vector2::Dot(distance, neb1));
	if (length > lengthA + lengthB) {
		return false;
	}
	//테스트축:neb2(B.Up())
	lengthA = eb2.GetLength();
	lengthB = separateAxis(neb2, ea1, ea2);
	length = abs(Vector2::Dot(distance, neb2));
	if (length > lengthA + lengthB) {
		return false;
	}
	return true;
}

bool RectCollider::isAABB(CircleCollider* circle)
{
	//이미 만든 코드가 있으니 그대로 이용하는 방법
	return circle->isRectCollision(this);
	//다만 이 클래스에서 담당해야 하는 기능을 다른 클래스에다가 맡겨버리는 꼴이 되기에
	//S.O.L.I.D법칙중 단일책임원칙을 위배하게 됨
	//이때문에 CircleCollider에 문제가 생기면 이 기능도 문제가 생기기 때문에 쓰기 힘듬
	//
	// 따라서 코드를 가져와 이쪽에 맞게 고치는게 나음
	//

} 

bool RectCollider::isOBB(CircleCollider* circle)
{
	//CircleCollider에서 만든 코드를 그대로 복사 해왔을때
	//원래 대로라면 이 사각형의 월드등에 맞게 고쳐야 할 필요가 있음
	//그런데 애초에 이 코드 자체가 지금 이 함수를 호출하는 Transform의 정보를 이용하므로
	//굳이 고칠 이유가없다



	Matrix S = XMMatrixScaling(circle->scale.x, circle->scale.y, 1.0f);
	Matrix R = XMMatrixRotationZ(circle->rot.z);
	Matrix T = XMMatrixTranslation(circle->pos.x - pos.x, circle->pos.y - pos.y, 0.0f);

	Matrix circle_world = S * R * T;

	circle_world *= XMMatrixRotationZ(-circle->rot.z);

	XMFLOAT4X4 temp_matrix;
	XMStoreFloat4x4(&temp_matrix, circle_world);
	//만들어진 월드에서 데이터를 추출하기 쉽게 FLOAT4x4행렬에 복사

	Vector2 circle_obb_center = Vector2(temp_matrix._41, temp_matrix._42);

	//나머지 내용은 그렇게 위치가 변경된 원의 좌표를 이용해서
	//이제는 회전하지 않고 있는 사각형과 충돌하는지 아닌지를 검사

	//사용하는 코드는 AABB에서와 거의 동일
	//다만 바뀌어야 하는 부분이 2가지
	Vector2 half = Size() * 0.5f;
	Vector2 closest;

	//1.원의 위치가 사각형의 월드를 기준으로 바뀌어 버렸으니
	//그 바꾼 위치를 이용하도록 변경해야함

	//지금 처리하는 영역은 사각형의 중심을 기준점으로 삼는 상황
	// 따라서 사각형의 pos값이라던가를 이용하지 않고
	//그냥 원점을 기준으로 계산하기만 하면 됨
	if (circle_obb_center.x < -half.x) {
		closest.x = -half.x;
	}
	else if (circle_obb_center.x > half.x) {
		closest.x = half.x;
	}
	else {
		closest.x = circle_obb_center.x;
	}

	if (circle_obb_center.y < -half.y) {
		closest.y = -half.y;
	}
	else if (circle_obb_center.y > half.y) {
		closest.y = half.y;
	}
	else {
		closest.y = circle_obb_center.y;
	}


	//2.이쪽에선 원의 원래 위치를 이용하는 알고리즘인 isPointCollision을
	//사용할수 없음
	//원이 사각형의 회전에 맞게 위치를 이동했으므로
	//원래 위치를 기준으로 계산하는 저 함수를 그대로 쓸수 없기 때문
	//따라서,여기선 직접 계산을 해줘야 한다
	if ((circle_obb_center - closest).GetLength() < circle->GetRadius()) {
		return true;
	}
	return false;
}

float RectCollider::separateAxis(Vector2 seperate, Vector2 e1, Vector2 e2)
//현재 테스트하고 있는 축의 방향을 이용,
//해당 축을 사용하지 않는 상대측 판정범위에서
// 기준점으로 사영 했을때 만들어지는 길이를 측정하는 함수
//
{
	float r1 = abs(Vector2::Dot(seperate, e1));
	float r2 = abs(Vector2::Dot(seperate, e2));
	//seperate라는 현재축을 만드는 방향을 가리키는 단위 벡터를 기준으로 하여
	//e1과e2가 각각 해당 방향 기준으로 얼마만큼의 좌표를 가지고 있는지
	//내적을 통해 계산하는 과정

	return r1 + r2;
	//e1,e2는 각각 상대측의 2개 벡터를 이용해서 만들어낸 값이니
	//상대방측에서 사영한 총 길이가 이 값이 되는것
}
/*
과제:

1)원->사각형 충돌 여부 판정은 만들어놨음
문제는 사각형->원과의 충돌여부 함수는 만들어지지 않은 상황
이걸 만들어볼것

힌트:말 그대로 날먹하는 방법과 조금 수고는 들어가지만 프로그램의 안정성은 살짝 더 나은 방법 2가지 방법이 있음
어느 방법을 쓰건 일단 문제삼지 않음


2)세상에서 제일 어려운 게임
같은 게임 만들기?

조건:다음과 같은 환경으로 만들것
1.장애물에 부딪힐 경우 1초동안 플레이어의 색이 변했다가 시작지점으로 돌아올것 + b에서 설명할 아이템이 전부 원래 자리로 돌아갈것
2.아이템이 화면(=레벨) 전체에 적어도 3개는 있어서 이 3개를 모두 먹었어야만 클리어 할수 있도록 할것
(3개를 다 먹어야 결승점에 도착했을때 게임이 종료 되도록 해도 되고
3개를 다 먹은 시점에 게임이 종료 되도록 해도 되고
3개를 다 먹는것으로 결승점 도착을 막는 장애물이 사라지도록 해도 되고 방식은 자유)

힌트 - 아이템을 먹었는지 아닌지의 여부를 판단할 방법은 많을것이나
먹은 아이템은 그냥 화면 밖으로 치워두는식을 이용하면 큰 문제는 없을것
다른 방법을 써도 되나 그러면 난이도가 높아질수 있음

플레이어는 반드시 키보드로만 움직일수있게 할것

*/