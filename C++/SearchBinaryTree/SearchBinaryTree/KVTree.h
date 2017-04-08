#pragma once
#include<iostream>
using namespace std;

template<class K,class V>
struct KTreeNode
{
	KTreeNode<K>* _left;
	KTreeNode<K>* _right;

	K _key;
	V _value;

	KTreeNode(const K& key, const V& value)
		:_left(NULL)
		, _right(NULL)
		, _key(key)
		, _value(value)
	{}
};

template<class K,class V>
class KTree
{
	typedef KTreeNode<K,V> Node;
public:
	KTree()
		:_root(NULL)
	{}

	~KTree()
	{
		Destroy(_root);
	}

	void Destory(Node*& root)
	{
		if (root == NULL)
			return;
		Destory(root->_left);
		Destory(root->_right);

		delete root;
		root = NULL;
	}

	bool InsertR(const K& key, const V& value)
	{
		return _InsertR(_root, key,value);
	}

	bool Insert(const K& key, const V& value)
	{
		Node* parent=NULL:
		Node* cur = _root;

		if (cur == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		else
		{
			while (cur != NULL)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else//���
				{
					return false;
				}
			}

			if (parent->_key > key)
			{
				parent->_left = new Node(key, value);
				return true;
			}
			else
			{
				parent->_right = new Node(key, value);
				return true;
			}
		}
	}

	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}

	bool Remove(const K& key)
	{
		if (_root == NULL)
			reurn false;

		Node* parent = NULL;
		Node* cur = _root;

		while (cur != NULL)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur=cur->_left
			}
			else if (cur->_key<key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else//�ҵ�Ҫɾ���ڵ㣬����ɾ��
			{
				Node* del = cur;
				
				//1.Ҫɾ���ڵ�������ΪNULL
				if (cur->_left == NULL)
				{
					//ע��parent�п���ΪNULL(Ҫɾ���ڵ�Ϊ���ڵ�)
					if (parent == NULL)
						parent = cur->_right;

					if (parent->_left==cur)
						parent->_left = cur->_right;
					else
						parent->_right = cur->_right;

					delete del;
					return true;
				}
				else if (cur->_right == NULL)//2.Ҫɾ���ڵ�������ΪNULL
				{
					if (parent == NULL)
						parent = cur->_left;

					if (parent->_left==cur)
						parent->_left = cur->_left;
					else
						parent->_right = cur->_left;

					delete del;
					return true;
				}
				else
				{
					//3.������������ΪNULL
					parent = cur;
					Node* SubL = cur->_right;//������������ڵ�

					//�ҵ�����ڵ�SubL
					while (SubL->_left)
					{
						parent = SubL;
						SubL = SubL->_left;
					}

					//ֵ�滻ɾ��
					del->_key = SubL->_key;
					del = SubL;

					if (parent->_right == SubL)
					{
						parent->_right = SubL->_right;
					}
					else
					{
						parent->_left = SubL->_right;
					}
					delete del;
					return true;
				}	
			}
		}
	}

	Node* FindR(K& key)
	{
		return _FindR(_root, key);
	}

	Node* Find(K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return NULL;
	}


	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
protected:

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

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

				//��������������ڵ�
				while (Subleft->_left)
				{
					parent = Subleft;
					Subleft = Subleft->_left;
				}

				//ֵ�滻
				del->_key = Subleft->_key;
				del = Subleft;

				//1.������ֻ��һ���ڵ�
				//2.������ѭ��
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

	bool _InsertR(Node*& root,const K& key,const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key,value);
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