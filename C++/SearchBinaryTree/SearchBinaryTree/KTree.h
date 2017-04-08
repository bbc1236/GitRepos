#pragma once
#include<iostream>
using namespace std;

template<class K>
struct KTreeNode
{
	KTreeNode<K>* _left;
	KTreeNode<K>* _right;

	K _key;

	KTreeNode(const K& key)
		:_left(NULL)
		, _right(NULL)
		, _key(key)
	{}
};

template<class K>
class KTree
{
	typedef KTreeNode<K> Node;
public:
	KTree()
		:_root(NULL)
	{}

	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}

	Node* FindR(K& key)
	{
		return _FindR(_root, key);
	}
protected:

	bool _RemoveR(Node*& root, const K& key)
	{
		if (root == NULL)
			return false;
		if (root->_key > key)
		{
			return _RemoveR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _RemoveR(root->_right, key);
		}
		else
		{
			Node* del = root;

			if (root->_left == NULL)
				root = root->_right;
			else if (root->_right == NULL)
				root = root->_left;
			else
			{
				Node* Subleft = root->_right;
				Node* parent = root;

				//找右子树的最左节点
				while (Subleft->_left)
				{
					parent = Subleft;
					Subleft = Subleft->_left;
				}

				//值替换
				del->_key = Subleft->_key;
				del = Subleft;

				//1.右子树只有一个节点
				//2.进入了循环
				if (parent->_left == Subleft)
					parent = Subleft->_right;
				else
					parent = Subleft->_left;

				delete del;
				return true;
			}
		}
	}

	Node* _FindR(Node* root, const K& key)
	{
		if (root == NULL)
			return NULL;
		if (root->_key > key)
		{
			return _FindR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _FindR(root->_right, key);
		}
		else
		{
			return root;
		}
	}

	bool _InsertR(Node*& root, K& key)
	{
		if (root == NULL)
		{
			root = new Node(key);
			return true;
		}

		if (root->_key > key)
		{
			return _Insert(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _Insert(root->_right, key);
		}
		else
		{
			return false;
		}
	}

protected:
	Node* _root;
};