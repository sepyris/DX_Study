#pragma once
//스테이지를 만들기 위해 장애물 수를 작성
#define OBSTACKLE_COUNT 50
#define ENEMY_COUNT 50
#define ITEM_MAX_COUNT 50
class CollisionScene : public Scene {
private:
	RectCollider* player; // 플레이어

	RectCollider* obstackle[OBSTACKLE_COUNT]; //벽
	CircleCollider* enemy[ENEMY_COUNT]; // 적
	CircleCollider* item[ITEM_MAX_COUNT];// 아이템

	RectCollider* end_stage; // 종료지점
	RectCollider* dummy_effect;//회전 구현을 위한더미
	

	float interval = 1; // 인터벌 시간 

	int stage = 1; //현재 스테이지 번호
	int earn_coin = 0;//얻은 코인
	int stage_coin = 0;//스테이지내 얻어야 하는 코인
	bool is_collision = false; //적 오브젝트랑 충돌 확인
	bool move_right[ENEMY_COUNT];//적 오브젝트 움직임 방향
	bool move_hor[ENEMY_COUNT]; // 좌우로 움직임 여부
	bool move_down[ENEMY_COUNT];//적 오브젝트 움직임 방향
	bool move_ver[ENEMY_COUNT];//상하로 움직임 여부
	int count = 0; //아이템 생성 반복문을 위한 카운트


	//스테이지 생성
	void CreateStage(int stage);

	//스테이지 삭제
	void DeleteStage();

	//스테이지 업데이트
	void StageUpdate();

	//스테이지 종료 체크
	void EndCheck();

	//스테이지 초기화
	void ResetStage();


public:
	CollisionScene();
	~CollisionScene();
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

};