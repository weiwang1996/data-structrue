#include<iostream>
#include<assert.h>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
template<class T>
struct TreeNode
{
	TreeNode<T> * _left;
	TreeNode<T>* _right;
	T  _data;
	TreeNode(const T&x)
		:_left(NULL)
		, _right(NULL)
		, _data(x)
	{}
};
template<class T>
class BinaryTree
{
	typedef TreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(T *arr, size_t n, const T& invalid)
	{
		size_t index = 0;
		_root = _Create(arr, n, invalid, index);
	}
	~BinaryTree()
	{
		_Destory(_root);
	}	void InOrder(Node* root)
	{
		if (root == NULL)
			return;
		Node* cur = root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push();
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cout << top->_data << " ";
			cur = top->_right;
		}
	}
	void PostOrder(Node* root)
	{
		if (root == NULL)
			return;
		stack<Node*> s;
		Node* cur = root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			Node*prev = top;
			if (top->_right == NULL || top->_right == prev)
			{
				cout << top->_data << "  ";
				prev = top;
				s.pop();
			}
			else
			{
				cur = cur->_right;
			}
		}
	}
	void LevelOrder()
	{
		_LevelOrder(_root);
		cout << endl;
	}
	size_t LevelK(size_t k)
	{
		return _LevelK(_root, k);
	}
	size_t LeafSize()
	{
		return _LeafSize(_root);
	}
	size_t Depth()
	{
		return _Depth(_root);
	}
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}
	void Image()
	{
		_Image(_root);
	}
	bool InTheTree(const T&x)
	{
		return _InTheTree(_root, x);
	}
	bool  IsBalance()
	{
		return _IsBalance(_root);
	}
	bool IsComplete()//判断是否平衡 把所有节点都入栈，出的时候查看左右子树是否存在，
		//若是不存在那么以后的所有节点不应该存在 子树。
	{
		bool flag = false;
		if (_root == NULL)
			return true;
		queue<Node*> q;
		q.push(_root);
		while (!q.empty())
		{
			Node*temp = q.front();
			if (temp->_left)
			{
				if (flag == true)
					return false;
				q.push(temp->_left);
			}
			else
				flag = true;//如果没有左孩子，标志位置为真
			if (temp->_right)
			{
				if (flag == true)
					return false;
				q.push(temp->_right);
			}
			else
				flag = true;
			q.pop();
		}
		return true;
	}
	size_t Maxlen()
	{
		size_t maxlen = 0;
		_Maxlen(_root, maxlen);
		return maxlen;
	}
	bool HasSubTree(Node*childroot)
	{
		return IsChildTree(_root, childroot);
	}
	bool IsChildTree(Node* _root, Node* childroot)
	{
		if (childroot == NULL)
			return false;
		else if (_root == NULL)
			return false;
		bool flag = false;
		if (_root->_data == childroot->_data)
			flag = _IsChildTree(_root, childroot);
		if (!flag)
			flag = IsChildTree(_root->_left, childroot) || IsChildTree(_root->_right, childroot);
		return flag;
	}
	Node* GetRoot()const
	{
		return _root;
	}
	
	Node* Find(const T&x)
	{
		return _Find(_root, x);
	}
	Node* GetLastestAncetor(Node* x1, Node* x2)
	{
		if (_root == NULL)
			return NULL;
		stack<Node*> s1, s2;
		if (!_GetPaths(_root, x1, s1) || !_GetPaths(_root, x2, s2))
		{
			return NULL;
		}
		//找到了
		while (s1.size() != s2.size())
		{
			if (s1.size() > s2.size())
				s1.pop();
			else
				s2.pop();
		}
		while (!s1.empty()&&!s2.empty()&&s1.top() != s2.top())
		{
			s1.pop();
			s2.pop();
		}
		return s1.top();
	}
protected:
	Node* _Find(Node* root, const T&x)
	{
		if (root == NULL)
			return NULL;
		if (root->_data == x)
			return root;
		Node* ret = NULL;
		if (ret = _Find(root->_left, x))
			return ret;
		else if (ret = _Find(root->_right, x))
			return ret;
	}
	//求一个节点的路径
	bool _GetPaths(Node* root, Node*node, stack<Node*>&s)
	{
		if (root == NULL)
			return false;
		s.push(root);
		if (node == root)
			return true;
		if (_GetPaths(root->_left, node, s))
			return true;
		if (_GetPaths(root->_right, node, s))
			return true;
		s.pop();
		return false;
	}

	//判断一个树是另一个树的子结构
	bool _IsChildTree(Node* root, Node* childroot)
	{
		if (childroot == NULL)
			return true;
		else if (root == NULL)
			return false;	
		if (root->_data != childroot->_data)
			return false;
		else
		return _IsChildTree(root->_left, childroot->_left) && _IsChildTree(root->_right, childroot->_right);		
	}
	//一个树中最长路径
	size_t _Maxlen(Node* root, size_t &maxlen)
	{
		if (root == NULL)
		{
			return 0;
		}
		size_t left = _Maxlen(root->_left, maxlen);
		size_t right = _Maxlen(root->_right, maxlen);

		if ((left + right) > maxlen)
			maxlen = left + right;
		return left > right ? left + 1 : right + 1;
	}
	//判断节点是否在树中
	bool _InTheTree(Node* root, const T&x)
	{
		if (root == NULL)
			return false;
		if (root->_data == x)
			return true;
		return _InTheTree(root->_left, x) || _InTheTree(root->_right, x);
	}
	//判断树是否平衡
	bool _IsBalance(Node* _root)
	{
		if (_root == NULL)
			return true;
		int dl = _Depth(_root->_left);
		int dr = _Depth(_root->_right);
		if ((abs(dr-dl)>=2))
			return false;
		return _IsBalance(_root->_left) && _IsBalance(_root->_right);
	}
	//树的镜像
	void _Image(Node* root)
	{
		if (root== NULL)
			return;
		if (root->_left == NULL&&root->_right == NULL)
			return;
		swap(root->_left, root->_right);
		if (root->_left)
			_Image(root->_left);
		if (root->_right)
			_Image(root->_right);
	}
	//前序遍历
	void _PrevOrder(Node* root)
	{
		if (root == NULL)
			return;
		cout << root->_data <<"  ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	//树的高度
	size_t _Depth(Node* root)
	{
		if (root == NULL)
			return 0;
		if (root->_left == NULL&&root->_right == NULL)
			return 1;
		size_t left = _Depth(root->_left);
		size_t right = _Depth(root->_right);
		return left > right ? left + 1 : right + 1;
	}
	//第K层节点数
	size_t _LevelK(Node* root,size_t k)
	{
		if (root == NULL)
			return 0;
		if (k == 1)
			return 1;
		return _LevelK(root->_left, k - 1) + _LevelK(root->_right, k - 1);
	}
	//叶子节点数
	size_t _LeafSize(Node* root)
	{
		if (root == NULL)
			return 0;
		if (root->_left == NULL&&root->_right == NULL)
			return 1;
		return _LeafSize(root->_left) + _LeafSize(root->_right);
	}
	//层序遍历
	void _LevelOrder(Node* root)
	{
		if (root == NULL)
			return;
		queue<Node*> q;
		q.push(root);
		while (!q.empty())
		{
			Node* ret = q.front();
			cout << ret->_data << " ";
			if (ret->_left)
			q.push(ret->_left);
			if (ret->_right)
			q.push(ret->_right);
			q.pop();
		}
	}
	//销毁二叉树
	void _Destory(Node* root)
	{
		if (root == NULL)
			return;
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
		root = NULL;
	}
	//创建二叉树
	Node* _Create(T* arr, size_t n, const T&invalid, size_t &index)
	{
		Node* root = NULL;
		if (index < n&&arr[index] != invalid)
		{
			root = new Node(arr[index]);
			root->_left = _Create(arr, n, invalid, ++index);
			root->_right= _Create(arr, n, invalid, ++index);
		}
		return root;
	}

private:
	Node* _root;
};
void Test1()
{
	int array[] = { 1, 2, 3,7, '#', '#', '#', 4, '#', '#', 5, /*6, '#',*/ '#', '#' };
	int array1[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', '#' };
	//BinaryTree<int> b1(array1,sizeof(array1)/sizeof(array1[1]),'#');
	BinaryTree<int> b1(array, sizeof(array) / sizeof(array[1]), '#');

	//cout << b1.LeafSize()<<endl;
//	cout << b1.LevelK(3);
	b1.LevelOrder();
	//b1.PrevOrder();
	//b1.Image();
	//b1.PrevOrder();
	cout << b1.IsBalance() << endl;
	cout << b1.IsComplete() << endl;
    cout << b1.Depth();
}
void Test2()
{
	int array[] = { 1, 2, 3, 7, '#', '#', '#', 4,'#', '#', 5, 6, '#', '#', '#' };
	int array1[] = { 1, 2, '#', '#', 5, '#', '#' };

	BinaryTree<int> b(array, sizeof(array) / sizeof(array[1]), '#');

	BinaryTree<int> b1(array1, sizeof(array1) / sizeof(array1[1]), '#');
	b.LevelOrder();
	 if( b.HasSubTree(b1.GetRoot()))
		 cout << "IsChildTree"<<endl;
	//cout << "maxlen=" << b1.Maxlen()<<endl;

}
void Test3()
{
	int array[] = { 1, 2, 3, 7, '#', '#', '#', 4, '#', '#', 5, 6, '#', '#', '#' };
	BinaryTree<int> b(array, sizeof(array) / sizeof(array[1]), '#');
	b.LevelOrder();
	TreeNode<int>* n1 = b.Find(7);
	TreeNode<int>* n2 = b.Find(6);
	cout<<b.GetLastestAncetor(n1, n2)->_data<<endl;
	
}
int main()
{
	Test3();
//	Test2();
	//Test1();
}
