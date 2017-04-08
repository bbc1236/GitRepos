#pragma once
#include<iostream>
using namespace std;

template<class T>
struct AVLTreeNode
{
	AVLTreeNode<T>* _left;
	AVLTreeNode<T>* _right;
	AVLTreeNode<T>* _parent
	int _bf;

	T _data;

	AVLTreeNode(const T& data)
		:_left(NULL)
		, _right(NULL)
		, parent(NULL)
		, _bf(0)
		, _data(data)
	{}
};

template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	void Insert(const T& data)
	{

	}



protected:
	Node* _root;
};