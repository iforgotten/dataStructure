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
	int remove(Rank lo, Rank hi);
	// 单元素删除, 返回被删除元素
	int remove(Rank r);
	// 区间查找，如果找到，返回找到的元素的位置，如果没有找到，返回非法位置
	int find(T const &e, Rank lo, Rank hi) const;
	// 无序向量去重操作,返回删除元素总个数
	int deduplicate();
	// 函数指针形式；也可以用函数对象模式，函数对象正在学习中
	void traverse(void (*visit)(T&));
	// 如果有序，返回0；无序返回逆序对的个数
	int disordered() const;
};

