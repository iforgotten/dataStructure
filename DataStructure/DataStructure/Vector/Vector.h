#pragma once
typedef int Rank;					// ��
#define DEFAULT_CAPACITY 3			// ��ʼ������ռ�

template<typename T>
class Vector
{
private:
	Rank _size;				// �洢����Ч���ݵĸ���
	int _capacity;			// ������������
	T* _elem;				// ������

	void copyFrom(T const *A, Rank lo, Rank hi);
	// ���ݺ��������ñ�������
	void expand();
protected:
	// ���ֲ���
	static Rank binSearch(T *elem, T const &e, Rank lo, Rank hi);
	// Fibonacci ����
	static Rank fibSearch(T *elem, T const &e, Rank lo, Rank hi);
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

	// 0 <= r <= _size-1
	int get(Rank r) const;
		// 0 <= r <= _size
	void put(Rank r, T const &e);
	// Ѱ�ȷ���
	// 0 <= r <= _size
	T &operator[](Rank r) const;
	// ������������ز������
	Rank insert(Rank r, T const &e); 
	// ����ɾ��Ԫ�صĸ���
	// [lo, hi)
	int remove(Rank lo, Rank hi);
	// ��Ԫ��ɾ��, ���ر�ɾ��Ԫ��
	int remove(Rank r);
	// ������ң�����ҵ��������ҵ���Ԫ�ص�λ�ã����û���ҵ������طǷ�λ��
	int find(T const &e, Rank lo, Rank hi) const;
	// ��������ȥ�ز���,����ɾ��Ԫ���ܸ���
	int deduplicate();
	// ����ָ����ʽ��Ҳ�����ú�������ģʽ��������������ѧϰ��
	void traverse(void (*visit)(T&));
	// ������򣬷���0�����򷵻�����Եĸ���
	int disordered() const;
	// ����������ȥ�ز���.����ɾ����Ԫ�صĸ���
	int uniquify();
	// �������������㷨
	Rank search(T const &e, Rank lo, Rank hi) const;
};

