#include "framework.h"

CircleCollider::CircleCollider(float rad)
	:radius(rad)
{
	type = TYPE::CIRCLE;
	CreateLine();
}

CircleCollider::~CircleCollider()
{
	delete VB;
}
bool CircleCollider::isPointCollision(Vector2 point)
{
	//원이라는것의 정의 자체가
	//중심에서 반지름 만큼 떨어져 있는 점의 집합
	//그렇다면 그 반지금보다 점이 더 가까이 있다면
	//원 안에 있다는 이야기가 됨
	return (GlobalPos()-point).GetLength() < radius;
	//내 중심과 입력받은 점과의 거리를 구해서
	//그 거리가 반지름보다 큰지 작은지 여부를 bool로 반환
	//반지름보다 작다면 원안에 들어온것
	//크기가 같거나 크다면 충돌하지 않은것
}
bool CircleCollider::isCircleCollision(CircleCollider* collider)
{
	//두 원의 중점 사이의 거리가 
	//두 원의 반지름을 합한것보다 작다면
	//= 두 원끼리 반지름을 서로를 향해 펼쳤을때 겹치는 부분이 있다면 충돌한것
	Vector2 dir = GlobalPos() - collider->GlobalPos();

	return dir.GetLength() < radius + collider->GetRadius();
}

bool CircleCollider::isRectCollision(RectCollider* collider, Vector2* overwrap)
{
	if (overwrap != NULL)
		return isAABB(collider);
	else
		return isOBB(collider);

	return false;
}

void CircleCollider::CreateLine()
{
	float angle = (float)(2 * M_PI);	
	for (int i = 0; i <= 50; i++)
	{
		vertices.emplace_back(-cos(angle) * radius, sin(angle) * radius);
		vertices.emplace_back(cos(angle) * radius, -sin(angle) * radius);
		angle -= (float)(2 * M_PI) / 50.0f;
	}
	VB = new VertexBuffer(vertices.data(), (UINT)sizeof(VertexPos), (UINT)(vertices.size()));
}

bool CircleCollider::isAABB(RectCollider* collider)
//사각형끼리의 AABB와는 완전히 같은 개념은 아니나
//사각형의 가로축과 세로축을 이용하는것 자체는 사실이니
//AABB라고 못부를건 없긴 함
{


	Vector2 half = collider->Size() * 0.5f;
	/*
	Vector2 closest; // 원과 사각형 사이에 제일 가까운 거리
	
	if (pos.x < collider->pos.x - half.x) {
		//원의 중심점이 상자의 왼쪽끝보다 더 왼쪽에 있다면
		closest.x = collider->pos.x - half.x;
		//원에서 사각형과 제일 가까운 지점의 x좌표는 사각형의 왼쪽끝(이라 가정)
		//만약 이것보다 더 멀다면 애초에 충돌할 리가 없음
	}
	else if (pos.x > collider->pos.x + half.x) {
		//그 반대로 오른쪽 끝보다 더 오른쪽 이라면
		closest.x = collider->pos.x + half.x;
		//위의 내용을 좌우 반전
	}
	else {
		//둘다 아닌, 즉 원의 중심점이 사각형측의 x좌표 범위 내에 있는 경우
		closest.x = pos.x;
	}

	//같은 내용을 y좌표에 대해서도 반복
	if (pos.y < collider->pos.y - half.y) {
		closest.y = collider->pos.y - half.y;
	}
	else if (pos.y > collider->pos.y + half.y) {
		closest.y = collider->pos.y + half.y;
	}
	else {
		closest.y = pos.y;
	}

	//그렇게 구한 사각형의 내부에서 원과 제일 가까운 점이 원 내부에 존재하는지를
	//검사하는 방식으로 사각형과 원이 충돌하는지 체크하면 됨


	if (isPointCollision(closest)) {
		return true;
	}

	return false;

	*/

	// 여기부터가 AABB
	//위쪽에비해 코드가 김
	//
	if (pos.x > collider->pos.x - half.x &&
		pos.x < collider->pos.x + half.x &&
		pos.y > collider->pos.y - half.y - GetRadius() &&
		pos.y < collider->pos.y + half.y + GetRadius()) {
		return true;
	}
	if (pos.x > collider->pos.x - half.x - GetRadius() &&
		pos.x < collider->pos.x + half.x + GetRadius() &&
		pos.y > collider->pos.y - half.y &&
		pos.y < collider->pos.y + half.y) {
		return true;
	}
	float left = collider->GlobalPos().x - half.x;
	float right = collider->GlobalPos().x + half.x;
	float top = collider->GlobalPos().y - half.y;
	float bottom = collider->GlobalPos().y + half.y;

	if (isPointCollision(Vector2(left,top)) ||
		isPointCollision(Vector2(left, bottom)) || 
		isPointCollision(Vector2(right, top)) || 
		isPointCollision(Vector2(right, bottom))) {
		return true;
	}

	return false;
}

bool CircleCollider::isOBB(RectCollider* collider)
//이쪽 사각형에서의 OBB와는 다른데,
//그래도 기본적으로 큰축은 비ㅡㅅ해던 AABB와는 다르게
//이쪽은 이론 자체가 완전히 다름
//여기서 OBB라고 쓰는건 그냥 단순하게 사각형축에서 처럼
//화전에 대응하는 알고리즘이라는 이유 단 하나뿐

//이쪽의 아이디어는 사각형 충돌의 OBB이론에 비해 훨씬 간단함
//사각형이 회전해 있으면 축에 직각으로 대응하지 않아서 계산이 복잡한것이니
//아예 그 대각선으로 계산할 일이 없도록 전체공간이 아닌
//사각형의 중점 정확힌 사각형의 월드 행렬을 기준으로 
//모든 것을 변환 시켜서 계산하면 되는것아닌가 라는 발상
{
	//일단은 새로운 월드를 만들기 위해 필요한 작업을 수행
	Matrix T = XMMatrixTranslation(pos.x - collider->pos.x,
		pos.y - collider->pos.y,0);
	//다른 행렬들은 Circle의 Transform이 가지고 있는 행렬을 이용해도 되나
	//T행렬만큼은 위치를 재계산한 행렬을 이용해야 함

	Matrix circle_world = S * R * T;
	circle_world *= XMMatrixRotationZ(-collider->rot.z);
	//그렇게 월드 계산을 시행,
	//그 과정에서 사각형이 기울어져있는정도만큼을 추가로 회전 시켜서
	//사각형을 변경된 월드의 x,y축에 평행하도록 만들기

	XMFLOAT4X4 temp_matrix;
	XMStoreFloat4x4(&temp_matrix, circle_world);
	//만들어진 월드에서 데이터를 추출하기 쉽게 FLOAT4x4행렬에 복사

	Vector2 circle_obb_center = Vector2(temp_matrix._41, temp_matrix._42);

	//나머지 내용은 그렇게 위치가 변경된 원의 좌표를 이용해서
	//이제는 회전하지 않고 있는 사각형과 충돌하는지 아닌지를 검사

	//사용하는 코드는 AABB에서와 거의 동일
	//다만 바뀌어야 하는 부분이 2가지
	Vector2 half = collider->Size() * 0.5f;
	Vector2 closest;

	//1.원의 위치가 사각형의 월드를 기준으로 바뀌어 버렸으니
	//그 바꾼 위치를 이용하도록 변경해야함

	//지금 처리하는 영역은 사각형의 중심을 기준점으로 삼는 상황
	// 따라서 사각형의 pos값이라던가를 이용하지 않고
	//그냥 원점을 기준으로 계산하기만 하면 됨
	if (circle_obb_center.x <  - half.x) {
		closest.x =  - half.x;
	}
	else if (circle_obb_center.x >  + half.x) {
		closest.x =  + half.x;
	}
	else {
		closest.x = circle_obb_center.x;
	}

	if (circle_obb_center.y <  - half.y) {
		closest.y =  - half.y;
	}
	else if (circle_obb_center.y >  + half.y) {
		closest.y =  + half.y;
	}
	else {
		closest.y = circle_obb_center.y;
	}


	//2.이쪽에선 원의 원래 위치를 이용하는 알고리즘인 isPointCollision을
	//사용할수 없음
	//원이 사각형의 회전에 맞게 위치를 이동했으므로
	//원래 위치를 기준으로 계산하는 저 함수를 그대로 쓸수 없기 때문
	//따라서,여기선 직접 계산을 해줘야 한다
	if ((circle_obb_center - closest).GetLength() < GetRadius()) {
		return true;
	}
	return false;

	/*
	if (isPointCollision(closest)) {
		return true;
	}

	return false;
	*/
}

