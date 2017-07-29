#include<iostream>
#include<assert.h>
using namespace std;
template <class T>
struct ListNode
{
	ListNode(const T&x)
	:_data(x)
	, _next(NULL)
	, _prev(NULL)
	{}
	T _data;
	ListNode<T> *_next;
	ListNode<T>*_prev;
};
template<class T>
class List
{
	typedef ListNode<T> Node;//方便起见 重命名该类型
public:
	List()
		:_pHead(NULL)
		, _pTail(NULL)
	{}
	void PushBack(const T& x)
	{
		if (NULL == _pHead)
			_pHead = _pTail = new Node(x);
		else
		{
			Node *temp = new Node(x);
			_pTail->_next = temp;
			temp->_prev = _pTail;
			_pTail = temp;
		}
	}
	void Print()
	{
		if (_pHead == NULL)
			return;
		else
		{
			Node *cur = _pHead;
			while (cur)
			{
				cout << cur->_data << "  ";
				cur = cur->_next;
			}
			cout << endl;
		}
	}
	void PopFront()
	{
		if (_pHead == NULL)
			return;
		else if (_pHead == _pTail)
		{
			delete _pHead;
			_pHead = _pTail = NULL;
		}
		else
		{
			Node* del = _pHead;
			_pHead = _pHead->_next;
			_pHead->_prev = NULL;
			delete del;
			del = NULL;
		}
	}
	void PushFront(const T&x)
	{
		if (_pHead == NULL)
			_pHead = _pTail = new Node(x);
		else
		{
			Node *temp = new Node(x);
			_pHead->_prev = temp;
			temp->_next = _pHead;
			_pHead = temp;
		}
	}
	void PopBack()
	{
		if (_pHead == NULL)
			return;
		else if (_pHead == _pTail)
		{
			delete _pHead;
			_pHead = _pTail = NULL;
		}
		else
		{
			_pTail = _pTail->_prev;
			delete _pTail->_next;
			_pTail->_next = NULL;
		}
	}
	void Insert(Node* pos, const T& x)
	{
		assert(pos);
		Node*cur = new Node(x);
		Node *prev = pos->_prev;
		Node* next = pos;
		if (prev)
		{
			prev->_next = cur;
			cur->_prev = prev;
		}
		cur->_next = next;
		next->_prev = cur;
		if (prev == NULL)
			_pHead = cur;
	}
	void Erase(Node *pos)
	{
		assert(pos);
		if (_pHead == NULL)
			return;
		else if (_pHead == _pTail)
		{
			if (pos != _pHead)
				return;
			else
				delete _pHead;
			_pHead = _pTail = NULL;
		}
		Node* prev = pos->_prev;
		Node *next = pos->_next;
		if (prev == NULL)
		{
			next->_prev = NULL;
			_pHead = next;
			delete pos;
			pos = NULL;
		}
		else if (next == NULL)
		{
			prev->_next = NULL;
			_pTail = prev;
			delete pos;
			pos = NULL;
		}
		else
		{
			prev->_next = next;
			next->_prev = prev;
			delete pos;
			pos = NULL;
		}
	}
	Node* Find(const T&x)
	{
		if (_pHead == NULL)
		{
			return NULL;
		}
		else
		{
			Node *cur = _pHead;
			while (cur)
			{
				if (cur->_data == x)
					return cur;
				cur = cur->_next;
			}
			return NULL;
		}
	}
	T& Front()
	{
		if (_pHead == NULL)
			return;
		return _pHead->_data;
	}
	T& Back()
	{
		if (_pHead == NULL)
			return;
		else
			return _pTail->_data;
	}
	bool Emtpy()
	{
		if (_pHead == NULL)
			return true;
		else
			return false;
	}
private:
	Node *_pHead;
	Node *_pTail;
};
template <class T,class container>
class Queue
{
public:
	void Push(const T& x)
	{
		return _con.PushBack(x);
	}
	void Pop()
	{
		return _con.PopFront();
	}
	void Print()
	{
		return _con.Print();
	}
	T& Front()
	{
		return _con.Front();
	}
	T& Back()
	{
		return _con.Back();
	}
	bool Emtpy()
	{
		return _con.Emtpy();
	}
protected:
	container _con;
};
int main()
{
	Queue<int, List<int>> q;
	q.Push(1);
	q.Push(2); 
	q.Push(3);
	q.Pop();
	q.Print();
	return 0;
}
