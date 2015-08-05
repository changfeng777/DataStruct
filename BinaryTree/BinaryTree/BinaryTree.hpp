#pragma once

#include<queue>
#include<stack>

// һ�������ʵ�ֽӿ�ʵ��

template<class T>
struct BinaryTreeNode
{
	T _data;				// ����
	BinaryTreeNode<T>* _left;	// ����
	BinaryTreeNode<T>* _right;	// �Һ���

	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}

	~BinaryTree()
	{
		Destory();
	}

	// 1.����������
	void CreateTree(T array[], size_t size)
	{
		int index = 0;
		_CreateTree(_root, array, size, index);
	}

	// 2.����������(ǰ�����򡢺��򡢲���)
	void PrevOrder()
	{
		cout<<"PrevOrder:";
		_PrevOrder(_root);
		cout<<endl;
	}

	void InOrder()
	{
		cout<<"InOrder:";
		_InOrder(_root);
		cout<<endl;
	}
	void PostOrder()
	{
		cout<<"PostOrder:";
		_PostOrder(_root);
		cout<<endl;
	}

	void LevelOrder()
	{
		cout<<"LevelOrder:";
		if (_root == NULL)
			return;

		// 1.����и��ڵ�
		queue<BinaryTreeNode<T>*> q;
		q.push(_root);

		// ����Ϊ��ʱ�������
		while (!q.empty())
		{
			BinaryTreeNode<T>* root = q.front();
			if (root->_left)
			{
				q.push(root->_left);
			}

			if (root->_right)
			{
				q.push(root->_right);
			}

			cout<<root->_data<<" ";
			q.pop();
		}
		cout<<endl;
	}

	// �ǵݹ�ʵ��ǰ/��/�������
	void PrevOrder_NonR()
	{
		cout<<"PrevOrder_NonR:";
		stack<BinaryTreeNode<T>*> s;
		if (_root)
		{
			s.push(_root);
		}

		while (!s.empty())
		{
			BinaryTreeNode<T>* root = s.top();
			cout<<root->_data<<" ";
			s.pop();

			if (root->_right)
			{
				s.push(root->_right);
			}

			if (root->_left)
			{
				s.push(root->_left);
			}
		}

		cout<<endl;
	}

	void InOrder_NonR()
	{
		cout<<"InOrder_NonR:";
		stack<BinaryTreeNode<T>*> s;
		if (_root)
		{
			s.push(_root);
		}

		while (!s.empty())
		{
			BinaryTreeNode<T>* root = s.top();

			if (root->_right)
			{
				s.push(root->_right);
			}

			if (root->_left)
			{
				s.push(root->_left);
			}
		}

		cout<<endl;
	}


	// 3.����
	BinaryTreeNode<T>* Find(const T& x)
	{
		return _Find(_root, x);
	}

	int Height()
	{
		return _Height(_root);
	}

	int Size()
	{
		return _Size(_root);
	}

	void Destory()
	{
		_Destory(_root);
		_root = NULL;
	}

protected:
	// ����������
	void _CreateTree(BinaryTreeNode<T>*& root, T array[], size_t size, int& index)
	{
		if (index < size && array[index] != '#')
		{
			root = new BinaryTreeNode<T>(array[index]);
			_CreateTree(root->_left, array, size, ++index);
			_CreateTree(root->_right, array, size, ++index);
		}
	}

	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;

		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _InOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}

	void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}

	BinaryTreeNode<T>* _Find(BinaryTreeNode<T>* root, const T& x)
	{
		if (root == NULL)
			return  NULL;

		if (root->_data == x)
			return root;

		BinaryTreeNode<T>* ret = NULL;
		if (ret = _Find(root->_left, x))
		{
			return ret;
		}

		if (ret = _Find(root->_right, x))
		{
			return ret;
		}

		return NULL;
	}

	int _Height(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int leftHeight = _Height(root->_left) + 1;
		int rightHeight = _Height(root->_right) + 1;

		return leftHeight > rightHeight ? leftHeight : rightHeight;
	}

	int _Size(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	void _Destory(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;
		
		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}

private:
	BinaryTreeNode<T>* _root;	// ���ڵ�
};