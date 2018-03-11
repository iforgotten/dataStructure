#pragma once
typedef int Rank;					// 秩
#define DEFAULT_CAPACITY 3			// 初始化分配空间

template<typename T>
class Vector
{
private:
	Rank _size;				// 存储的有效数据的个数
	int _capacity;			// 数据区的容量
	int* _elem;				// 数据区
protected:
	void copyFrom(T const *A, Rank lo, Rank hi);

	// 扩容函数，采用倍增函数
	void expand();
public:
	// 默认构造
	Vector(int capacity = DEFAULT_CAPACITY);
	// 如果已经有了一个数组，数组进行区间复制
	// 区间为：[lo,hi)
	Vector(T const *A, Rank lo, Rank hi);
	// 向量区间复制
	Vector(Vector<T> const &V, Rank lo, Rank hi);
	// 向量整体复制
	Vector(Vector<T> const &V);
	~Vector();
	// 寻秩访问
	// 0 <= r <= _size
	T &operator[](Rank r) const;
	// 插入操作，返回插入的秩
	Rank insert(Rank r, T const &e); 
	// 返回删除元素的个数
	// [lo, hi)
	int deleteBetween(Rank lo, Rank hi);
};

