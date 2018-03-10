#include "Vector.h"

// template class Vector <class T > ;
template class Vector < int > ;


template <typename T>
Vector<T>::Vector(int capacity)
{
	_capacity = capacity;
	_size = 0;
	_elem = new int[_capacity];
}

template <typename T>
Vector<T>::Vector(T const *A, Rank lo, Rank hi) {
	copyFrom(A, lo, hi);
} // �������临��

template <typename T>
Vector<T>::Vector(Vector<T> const &V, Rank lo, Rank hi) {
	copyFrom(V._elem, lo, hi);
}

template <typename T>
Vector<T>::Vector(Vector<T> const &V) {
	copyFrom(V._elem, 0, V._size);
}

template <typename T>
Vector<T>::~Vector(void)
{
	delete[] _elem;
	_elem = nullptr;
}

template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
	// ��������
	// [lo, hi);
	// lo�Ǹ���������ߵ��Ǹ�λ��
	// hi�ǵ�һ�������ڸ������Ԫ��λ�ã���Ȼ���ܲ����ڣ��������ǿ��Լ��������
	_capacity = 2 * (hi - lo);
	// ����ռ�
	_elem = new T[_capacity];
	// ��ģ��0
	_size = 0;

	// ��һ���Ƽ���
	while (lo < hi) {
		_elem[_size] = A[lo];
		++_size;
		++lo;
	}
}

