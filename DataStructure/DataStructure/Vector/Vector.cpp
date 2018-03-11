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
} // ���ݺ��������ñ�������

template <typename T>
T Vector<T>::&operator[](Rank r) const {
	return _elem[r];
} // 0 <= r <= _size

template <typename T>
Rank Vector<T>::insert(Rank r, T const &e) {
	expand(); // ����б�Ҫ�����������

	// locatino in [r,_size)
	for(int i = _size; i > r; --i) {
		_elem[_size] = _elem[_size-1]; 
	}
	_elem[r] = e;
	_size++;
	return r;
} // ��������

template <typename T> 
int Vector<T>::deleteBetween(Rank lo, Rank hi) {
	// ����ɾ�� [lo, hi)
	// �߽�����
	if(lo == hi) 
		return 0;
	// ����Ԫ�أ��൱��ɾ��Ԫ��
	// �����ĸ��� == _size; ����λ�õĹ�ϵ�����һλ����Ϊ��C�У����ڴ�ƫ���±��Ǵ�0��ʼ��
	while(hi < _size) {
		_elem[lo++] = _elem[hi++];
	}
	// Ӱ��_size
	_size = lo;
	return hi - lo;
} // ����ɾ��������Ԫ�صĸ���