#include "framework.h"


RectCollider::RectCollider(Vector2 size)
	: size(size)
{
	type = TYPE::RECT;

	CreateLine();
}

RectCollider::~RectCollider()
{
}

void RectCollider::CreateLine()
//이 충돌 판정의 범위를 화면에 표기하기 위해
//어떤 정점을 사용하는지 정의 하는 부분
{
	Vector2 half = Size() * 0.5f;

	vertices.emplace_back(-half.x, +half.y);
	vertices.emplace_back(+half.x, +half.y);
	vertices.emplace_back(+half.x, -half.y);
	vertices.emplace_back(-half.x, -half.y);
	vertices.emplace_back(-half.x, +half.y);
	//시계 반대방향으로 정점이 만들어져있지만
	//삼각형이 아니라 선을 긋는것이라 시계방향을 지킬필요가 없음

	VB = new VertexBuffer(vertices.data(), sizeof(VertexPos), vertices.size());
}

RectCollider::ObbDesc RectCollider::GetObbDesc()
{
	return ObbDesc();
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
	return false;
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

	//if(overwrap != NULL)
	return isAABB(collider, overwrap);
	//else
	//isOBB(collider);
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
/*O Bounding Box의 줄임말

*/
{

	return false;
}

bool RectCollider::isAABB(CircleCollider* rect)
{
	return false;
}

bool RectCollider::isOBB(CircleCollider* rect)
{
	return false;
}

float RectCollider::separateAxis(Vector2 seperate, Vector2 e1, Vector2 e2)
{
	return 0.0f;
}
