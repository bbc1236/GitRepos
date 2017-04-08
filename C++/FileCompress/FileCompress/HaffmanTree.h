#pragma once

#include "Heap.h"

template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;
	T _w;							//CharInfo

	HuffmanTreeNode(const T& weight)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _w(weight)
	{}
};

template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		:_root(NULL)
	{}

	HuffmanTree(const T* a, size_t n,const T& invalid)//infor[256]
	{
		struct NodeCompare
		{
			bool operator()(const Node* l, const Node* r)
			{
				return l->_w < r->_w;		//注意为const，调用const函数
			}
		};

		//通过小堆取_count最小的节点
		Heap<Node*, NodeCompare> minHeap;
		for (size_t i = 0; i < n; ++i)
		{
			if (a[i] != invalid)			//需要重载!=() const
			{
				minHeap.Push(new Node(a[i]));
			}	
		}

		//构建Huffman树		
		while (minHeap.Size()>1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();

			Node* right = minHeap.Top();
			minHeap.Pop();

			Node* parent = new Node(left->_w + right->_w);

			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;

			minHeap.Push(parent);
		}

		_root = minHeap.Top();
	}

	Node* GetRoot()
	{
		return _root;
	}

	~HuffmanTree()
	{
		Destory(_root);
		_root = NULL;
	}

	void Destory(Node* root)
	{
		if (root == NULL)
			return;

		Destory(root->_left);
		Destory(root->_right);
		delete root;
	}
protected:
	Node* _root;
};