#pragma once
template<typename T>
class Singleton
/*
�̱���(Singleton) : "������ ����" �� �� ������
�� ���α׷����� ���� Ŭ������ �ν��Ͻ��� �� �̻� ��������� �� ���� ���·�
Ŭ������ ����� ���

������, �Ҹ��� ���� �ܺο��� ������ �� ���� �����
�� Ŭ������ ������ ��ü�� static ��� ������ �����Ͽ�,
�� ������ �ν��Ͻ��� �����ϴ� static ��� �Լ��� ���ؼ� ��ü ������ ������
���ÿ� ���ϴ� ����
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