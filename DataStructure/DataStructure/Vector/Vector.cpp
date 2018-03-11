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

template <typename T>
void Vector<T>::expand() {
	if(_size < _capacity) {
		return;
	}

	T* oldElem = _elem;
	_elem = new [_capacity <<= 1];
	
	for(int i = 0; i <= _size; ++i) {
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
} // 扩容函数，采用倍增策略

template <typename T>
T Vector<T>::&operator[](Rank r) const {
	return _elem[r];
} // 0 <= r <= _size

template <typename T>
Rank Vector<T>::insert(Rank r, T const &e) {
	expand(); // 如果有必要，则进行扩容

	// locatino in [r,_size)
	for(int i = _size; i > r; --i) {
		_elem[_size] = _elem[_size-1]; 
	}
	_elem[r] = e;
	_size++;
	return r;
} // 返回其秩

template <typename T> 
int Vector<T>::deleteBetween(Rank lo, Rank hi) {
	// 区间删除 [lo, hi)
	// 边界条件
	if(lo == hi) 
		return 0;
	// 左移元素，相当于删除元素
	// 向量的个数 == _size; 与其位置的关系是相差一位。因为在C中，其内存偏移下标是从0开始的
	while(hi < _size) {
		_elem[lo++] = _elem[hi++];
	}
	// 影响_size
	_size = lo;
	return hi - lo;
} // 区间删除，返回元素的个数