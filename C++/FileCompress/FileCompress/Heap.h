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