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
} // 数组区间复制

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
	// 分配容量
	// [lo, hi);
	// lo是该区间最左边的那个位置
	// hi是第一个不属于该区间的元素位置，虽然可能不存在，但是我们可以假设其存在
	_capacity = 2 * (hi - lo);
	// 申请空间
	_elem = new T[_capacity];
	// 规模清0
	_size = 0;

	// 逐一复制即可
	while (lo < hi) {
		_elem[_size] = A[lo];
		++_size;
		++lo;
	}
}

