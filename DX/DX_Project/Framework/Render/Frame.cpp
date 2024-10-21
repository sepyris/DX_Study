#include "framework.h"
#include "Frame.h"

Frame::Frame(wstring file, Vector2 startUV, Vector2 endUV)
// 파일 주소와 함께 해당 파일 중 출력할 구간을 "이미지 전체에서의 상대좌표로서 입력받았을 때"의 생성자
// 이 이미지 전체에서의 상대좌표를 확인할 일이 어지간하면 없기 때문에,
// 보통은 기본값인 0,0과 1,1을 이용하기 위해 쓰는 것이라 보면 OK
{
	texture = Texture::Add(file); // 파일 불러오기

	Vector2 size = texture->GetSize(); // 불러온 파일의 크기를 받아서 size에 입력

	Vector2 half_size = size * 0.5f; // 정점의 위치를 정의하는 데 쓸 변수

	float left = -half_size.x;
	float right = half_size.x;
	float top = -half_size.y;
	float bottom = half_size.y;
	// 이를 통해 이 이미지가 표시될 상,하,좌,우 정점의 각각의 좌표들을 정의

	vertices.emplace_back(left, top, startUV.x, startUV.y);
	vertices.emplace_back(right, top, endUV.x, startUV.y);
	vertices.emplace_back(left, bottom, startUV.x, endUV.y);
	vertices.emplace_back(right, bottom, endUV.x, endUV.y);

	indices = { 0, 1, 2, 2, 1, 3 };
	// 정점과 인덱스를 등록

	VB = new VertexBuffer(vertices.data(), (UINT)sizeof(VertexUV), (UINT)vertices.size());
	IB = new IndexBuffer(indices.data(), (UINT)indices.size());

	frame_size = endUV - startUV;
	// 전체 프레임의 크기 중 이 프레임이 차지하는 비율이 얼마나 되는지를 frame_size에 기록
	// 이 값은 나중에 이 프레임이 관리하고 있는 이미지 파일에 곱해 실제 크기를 확인하는 데 사용
}

Frame::Frame(wstring file, float x, float y, float w, float h)
// 파일 주소와 함께 해당 파일 중 
// "이미지 내부에서 출력하고자 하는 영역의 절대좌표를 받았을 때"의 생성자
// 
// x, y : 이미지 파일 내에서 출력하고자 하는 스프라이트가 있는
//        사각형 영역이 시작되는 왼쪽 위 점의 좌표
// 
// w, h : width, height로서 출력하고자 하는 스프라이트가 있는
//        사각형 영역의 가로/세로 범위를 지정하는 매개 변수
{
	texture = Texture::Add(file); // 파일 불러오기

	Vector2 size = texture->GetSize(); // 불러온 파일의 크기를 받아서 size에 입력

	Vector2 half_size = size * 0.5f; // 정점의 위치를 정의하는 데 쓸 변수

	float left = -half_size.x;
	float right = half_size.x;
	float top = -half_size.y;
	float bottom = half_size.y;
	// 이를 통해 이 이미지가 표시될 상,하,좌,우 정점의 각각의 좌표들을 정의


	Vector2 cut_start = Vector2(x, y) / size;
	// 출력하고자 하는 위치의 이미지상의 상대좌표(uv값)

	Vector2 cut_size = Vector2(w, h) / size;
	// 출력하고자 하는 그림 사이즈의 상대좌표로서의 길이

	Vector2 cut_end = cut_start + cut_size;
	// 출력하고자 하는 이미지가 끝나는,
	//이미지의 범위를 가리키는 사각형의 오른쪽 아래 점

	vertices.emplace_back(left, top, cut_start.x, cut_start.y );
	vertices.emplace_back(right, top, cut_end.x, cut_start.y );
	vertices.emplace_back(left, bottom, cut_start.x, cut_end.y );
	vertices.emplace_back(right, bottom, cut_end.x, cut_end.y);

	indices = { 0, 1, 2, 2, 1, 3 };
	// 정점과 인덱스를 등록

	VB = new VertexBuffer(vertices.data(), (UINT)sizeof(VertexUV), (UINT)vertices.size());
	IB = new IndexBuffer(indices.data(), (UINT)indices.size());

	frame_size = Vector2(w / texture->GetSize().x,
		                 h / texture->GetSize().y);
	//텍스쳐 전체의 크기를 먼저 구한뒤
	//그것들을 지금 입력받은 스프라이트 각각의 크기로 나눠서
	//전체 사진상에서의 비율을 입력하는것
	 
	 
	//따라서 frame_size에 저장되는 값은 스프라이트의 크기 그 자체가 아니라
	//스프라이트가 전체 크기를 기준으로 얼마나 작은지를 체크하는 값
}

Frame::~Frame()
{
	if (VB != NULL) {
		delete VB;
	}
	if (IB != NULL) {
		delete IB;
	}
	
}

void Frame::Render()
{
	VB->Set();
	IB->Set();
	texture->Set();

	DVC->DrawIndexed((UINT)indices.size(), 0, 0);
	//이 클래스는 인덱스 버퍼를 이용하므로
	// = 꼭지점을 무조건 한번만 쓴다는 보장이 없으므로
	// 꼭지점의 개수 대신
	//어느 꼭지점을 이용할것인지가 저장되어있는 indices의 size를 이용해서
	//총 출력할 꼭지점들의 개수를 입력
}
