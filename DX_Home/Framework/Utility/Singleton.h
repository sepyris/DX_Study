#pragma once
template<typename T>
class Singleton
/*
싱글톤(Singleton) : "디자인 패턴" 중 한 가지로
한 프로그램에서 같은 클래스의 인스턴스가 둘 이상 만들어지는 걸 막는 형태로
클래스를 만드는 방식

생성자, 소멸자 등을 외부에서 접근할 수 없게 만들고
이 클래스의 유일한 객체를 static 멤버 변수로 저장하여,
이 유일한 인스턴스에 접근하는 static 멤버 함수를 통해서 객체 생성과 접근을
동시에 행하는 구조
*/
{
protected:
	static T* instance;

public:
	static T* Get()
	{
		if (instance == nullptr)
			instance = new T();

		return instance;
	}

	static void Delete() { delete instance; }
};

template<typename T>
T* Singleton<T>::instance = NULL;