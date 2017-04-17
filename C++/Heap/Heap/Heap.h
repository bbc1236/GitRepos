#pragma once
#include <iostream>
using namespace std;

#include <vector>

#include <assert.h>

template <class T>
struct Greater
{
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};

template <class T>
struct Less
{
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};

//�����
template <class T, class Compare = Greater<T>>
class Heap
{
public:
	Heap()
	{}

	Heap(T* a, int n)
		:_array(a, a + n)//���õ�����ʵ�ֿ���n����С�ռ�
	{

		for (int i = (_array.size() - 2) / 2; i >= 0; --i)
		{
			_AdjustDown(i);
		}
	}

	void Push(const T& data)
	{
		_array.push_back(data);
		_AdjustUp(_array.size() - 1);
	}

	void Pop()
	{
		//vector ���пջ���
		swap(_array[0], _array[_array.size() - 1]);
		_array.pop_back();
		_AdjustDown(0);
	}

	size_t Size()
	{
		return _array.size();
	}

	bool Empty()
	{
		return _array.empty();
	}

	T& Top()
	{
		assert(!Empty());
		return _array[0];
	}

protected:

	//���ϵ���
	void _AdjustUp(int root)
	{
		int child = root;
		int parent = (root - 1) / 2;

		while (child >0)
		{
			Compare compare;
			if (compare(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	//���µ���
	void _AdjustDown(int root)
	{
		int parent = root;
		int child = parent * 2 + 1;
		int size = _array.size();

		//ע���������
		while (child < size)
		{
			Compare compare;
			if (child + 1 < size && compare(_array[child + 1], _array[child]))
			{
				++child;
			}

			if (compare(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);

				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

protected:
	vector<T> _array;
};

//���ȼ�����
template <class T,class Compare=Greater<T>>
class PriorityQueque
{
public:
	void Push(const T& data)
	{
		_hp.Push()
	}

	void Pop()
	{
		_hp.Pop();
	}

	bool Empty()
	{
		return _hp.Empty();
	}

	T& Top()
	{
		return _hp.Top();
	}

protected:
	Heap<T, Compare> _hp;
};




//topK����
void AdjustDown(int* arr,int root,int k)
{
	int parent = root;
	int child = parent * 2 + 1;

	while (child < k)
	{
		if (child + 1 < k&&arr[child + 1] < arr[child])
			++child;
		if (arr[parent]>arr[child])
		{
			swap(arr[parent], arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//1. ������ǰK����������С��
void GetTopK()
{
	//1.����
	int arr[] = { 1, 2, 4, 3, 6, 5, 4, 9, 7, 8, 0 };
	int size = sizeof(arr) / sizeof(arr[0]);
	int k = 5;

	//2.���ѡ���С��
	for (int i = (k-2)/2; i >=0; --i)
	{
		AdjustDown(arr,i,k);
	}

	//3.ʣ�����ͶѶ������бȽϣ����ڶѶ������ͶѶ������н��������µ���
	int cur = k;
	while (cur < size)
	{
		if (arr[0] < arr[cur])
		{
			swap(arr[0], arr[cur]);
			AdjustDown(arr, 0, k);
			++cur;
		}
		else
		{
			++cur;
		}
	}

	//4.��ӡǰK����
	for (int i = 0; i < k; ++i)
		cout << arr[i] << " ";
	cout << endl;

}

//���򡪡���С��
void HeapSort(int* arr,int n)
{
	assert(n>0);

	//����
	for (int i = (n - 2) / 2; i >= 0; --i)
	{
		AdjustDown(arr, i, n);
	}

	//����˳��

	int end = n - 1;
	while (end > 0)
	{
		swap(arr[0], arr[end]);
		AdjustDown(arr, 0, end);
		--end;
	}

	for (int i = 0; i < n; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void TestHeap()
{
	int arr[9] = { 1, 2, 5, 0, 7, 3, 8, 4, 6 };
	Heap<int,Less<int>> hp(arr, sizeof(arr) / sizeof(arr[0]));
	hp.Pop();
	hp.Push(10);

	GetTopK();

	HeapSort(arr, sizeof(arr) / sizeof(arr[0]));

}