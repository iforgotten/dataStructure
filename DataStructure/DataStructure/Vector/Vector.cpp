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
int Vector<T>::get(Rank r) const {
	return _elem[r];
}
template <typename T>
void Vector<T>::put(Rank r, T const &e) {
	_elem[r] = e;
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
int Vector<T>::remove(Rank lo, Rank hi) {
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

template <typename T>
int Vector<T>::remove(Rank r) {
	// The range of the locations of the elments are in [lo, hi)
	T elem = _elem[r];
	remove(r, r+1);
	return elem;
} // 返回被删除元素

template <typename T>
int Vector<T>::find(T const &e, Rank lo, Rank hi) const {

	while((lo < hi--) && (_elem[hi] != e));
	return hi;
} // 返回最后一个查找位置
template <typename T>
int Vector<T>::deduplicate() {
	// 备份原向量规模
	int oldSize = _size;
	// [0, loc)
	int loc = 1;
	while(loc < _size) {
		// 三元表达式规范
		(find(_elem[loc], 0, loc) < 0) ? 
			loc++
		: remove(loc);
	}

	return oldSize - _size;
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) {
	for(int i = 0; i < _size; ++i)
		visit(_elem[i]);
}

template <typename T>
int Vector<T>::disordered() const {
	// 逆序对个数
	int count = 0;
	for(int i = 1; i < _size; ++i) {
		count += (_elem[i-1] > _elem[i]);
 	}
	return count;
} // 返回逆序对个数

// 去重操作低效版本
/*
template <typename T>
int Vector<T>::uniquify() {
	int oldSize = _size;

	for(int i = 1; i < _size; ++i) {
		if(_elem[i-1] == _elem[i]) {
			remove(i);
		}
	}
	return oldSize - _size;
} // 低效版去重操作，返回删除的元素
*/ 

// 高校版本
template <typename T>
int Vector<T>::uniquify() {
	int oldSize = _size;
	// 位置指针；size 与loc相差1
	int i = j = 0;
	while(++j < _size-1) {
		// 不相等，则前移
		if(_elem[i] != _elem[j]) 
			_elem[++i] = _elem[j];
	}
	_size = ++i;
	return oldSize - _size;
} // 返回删除元素个数

template <typename T>
int Vector<T>::search(T const &e, Rank lo, Rank hi) const {
	return (rand() % 2) ? 
		binSearch(_elem, e, lo, hi) 
		: fibSearch(_elem, e, lo, hi);
} // 随机选择搜素算法

template <typename T>
static Rank Vector<T>::binSearch(T *elem, T const &e, Rank lo, Rank hi) {
	Rank mid = (lo + hi) >> 1;
	// 采用迭代代替递归，因为递归的一些不必要操作浪费时间
	while(lo < hi) {
		if(elem[mid] < e) {
			// (mid,hi)
			lo = mid + 1;	// 深入后半段，继续查找
		} else if (e < elem[mid]) {
			// [lo, mid)
			hi = mid;		// 深入前半段，继续查找
		} else {
			// 命中
			return mid;
		}
	}

	// 查找失败
	return -1;	
}