#pragma once
typedef int Rank;					// ��
#define DEFAULT_CAPACITY 3			// ��ʼ������ռ�

template<typename T>
class Vector
{
private:
	Rank _size;				// �洢����Ч���ݵĸ���
	int _capacity;			// ������������
	int* _elem;				// ������

	void copyFrom(T const *A, Rank lo, Rank hi);
	void expand();
protected:

public:
	// Ĭ�Ϲ���
	Vector(int capacity = DEFAULT_CAPACITY);
	// ����Ѿ�����һ�����飬����������临��
	// ����Ϊ��[lo,hi)
	Vector(T const *A, Rank lo, Rank hi);
	// �������临��
	Vector(Vector<T> const &V, Rank lo, Rank hi);
	// �������帴��
	Vector(Vector<T> const &V);
	~Vector();

};

