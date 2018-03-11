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
protected:
	void copyFrom(T const *A, Rank lo, Rank hi);

	// ���ݺ��������ñ�������
	void expand();
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
	// Ѱ�ȷ���
	// 0 <= r <= _size
	T &operator[](Rank r) const;
	// ������������ز������
	Rank insert(Rank r, T const &e); 
	// ����ɾ��Ԫ�صĸ���
	// [lo, hi)
	int deleteBetween(Rank lo, Rank hi);
};

