#pragma once
/*
3D공간에서 어떤 오브젝트와 다른 오브젝트가 충돌 하는것은
기본적으로는 그 둘이 각자 가지고 있는 충돌 영역 내지 충돌 판정이라 불리는것을
서로 비교,충돌하는 지점이 있는지 없는지 검사하는 식으로 판정

문제는 충돌 했는지의 여부를 판단하는 알고리즘이라는것이
종류도 많고 상당히 복잡한것들이 많음
그래서 여기서는 그 중 주로 쓰이는 2가지 알고리즘을 사용할 예정
(어느 알고리즘도 적용하지 않은 버전,AABB알고리즘,OBB알고리즘)


*/


class Collider:public Transform
{
public:
	enum class TYPE {
		RECT,
		CIRCLE
	};
	//본 클래스는 두 자식 클래스에게 상속할것을 전제로 만든 클래스
	//따라서 리스코프 치환 원칙에 따라 자식 클래스들을 본 클래스로 취급해
	//사용할 상황이 매우 많음
	//따라서, 부모클래스측에서 어떤 자식 클래스를 쓰는것인지 판단하기 위해
	//멤버로서 어떤 클래스인지를 기록하는 열거형 클래스 멤버를 만들것이고
	//거기에 사용할 열거형 클래스를 public으로 공표 한것

protected:
	TYPE type;//그렇게 선언된 열거형 클래스를 protected멤버로 하나 생성

	VertexShader* VS;
	PixelShader* PS;

	VertexBuffer* VB;

	ColourBuffer* CB;
	//여기까지는 기존에 사용한것과 동일
	MatrixBuffer* WB;
	//이 충돌 판정 클래스가 자기자신을 주체적으로 출력하게 만들것이므로
	//그 과정에서 사용할 월드 버퍼를 직접 만들어준것

	vector<VertexPos> vertices;//거기에 사용할 정점
	//다만 이 클래스는 기존의 정점이 아니라
	//색상값은 아예 사용하지 않고 위치만 기록하는 정점을 사용함
	// 색상버퍼에 있는 색만으로 테두리만을 그릴 예정이기 때문
	//


public:
	Collider();
	virtual ~Collider();
	void Render();

	TYPE GetType() { return type; }

	virtual bool isCollision(Collider* collider,Vector2* overwrap = NULL);
	//입력받은 충돌판정이 어떤 타입이냐에 따라 아래에 있는 다른 함수를 호출하는 중개함수

	//아래의 두 함수(+선 충돌 판정)는 전부
	//특정한 대상과 충돌 했는지를 검사하는 함수
	virtual bool isPointCollision(Vector2 point) = 0;
	virtual bool isCircleCollision(class CircleCollider* collider) = 0;
	virtual bool isRectCollision(class RectCollider* collider, Vector2* overwrap = NULL) = 0;

	void SetColor(float r, float g, float b) {
		CB->data.colour = Float4(r, g, b, 1);
	}
protected:
	virtual void CreateLine() = 0;

	//이 충돌 판정의 테두리선을 정의 하는 함수
	//원을 그릴지 사각형을 그릴지 부모클래스 단계에선 알수 없으므로
	//이를 자식 클래스에서 그리도록 강제
};