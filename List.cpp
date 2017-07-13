#include<iostream>
#include<assert.h>
using namespace std;
template<class T>
struct ListNode
{
	ListNode * _next;
	ListNode * _prev;
	T _data;
	ListNode(const T& x)
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
};
template<class T, class Ref, class Ptr >
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;
	ListIterator(Node *Node)
		:_node(Node)
	{}
	Node * _node;
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &(operator*());
	}
	Self operator++()//前置++
	{
		_node = _node->_next;
		return _node;
	}
	Self operator--(int)//后置--
	{
		Self tmp(*this);
		_node = _node->_prev;
		return tmp;
	}
	Self& operator--()//前置--
	{
		_node = _node->_prev;
		return *this;
	}
	Self operator++(int)//后置++
	{
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}
	bool operator != (const Self& s) const
	{
		return _node != s._node;
	}
};
template<class T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef ListIterator<T, T&, T*> iterator;
	typedef ListIterator<T, const T&, const T*> constiterator;
	List()
		:_head(BuyNode(T()))
	{
		 _head->_prev=_head ;
		_head->_next = _head;
	}
	~List()
	{
			Clear();
			delete _head;
			_head = NULL;
	}
	void Clear()
	{
		Node* cur = _head;
		while (cur->_next!=_head)
		{
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		_head = _head->_next;
		_head = _head->_prev;
	}
	void PushBack(const T& x)
	{
		Node* newnode = BuyNode(x);
		Node*tail = _head->_prev;
		
		tail->_next = newnode;
		newnode->_prev = tail;
		newnode->_next = _head;
		_head->_prev = newnode;
	}
	iterator Begin()
	{
		return iterator(_head->_next);
	}
	constiterator Begin()const
	{
		return constiterator(_head->_next);
	}
	iterator End()
	{
		return iterator(_head);
	}
	constiterator End()const
	{
		return constiterator(_head);
	}
	void Print()
	{
		Node* cur = _head;
		while (cur->_next!= _head)
		{
			cur = cur->_next;
			cout << cur->_data<<"  ";
		}
		cout << endl;
	}
	iterator Find(const T& x)
	{
		iterator it = Begin();
		while (it != _head)
		{
			if (*it == x)
				return it;
			else
				++it;
		}
		return End();
	}
	iterator Erase(iterator pos)
	{
		assert(pos);
		Node *prev = pos._node->_prev;
		Node *next = pos._node->_next;
		Node *cur = pos._node;
		prev->_next = next;
		next->_prev = prev;
		delete cur;
		cur = NULL;
		return prev;//防止迭代器失效 返回当前迭代器的上一个
	}
	iterator Insert(iterator pos, const T&x)
	{
		if (_head == _head->_next)
		{
			Node * cur = BuyNode(x);
			_head->_next = cur;
			cur->_prev = _head;
			cur->_next = _head;
			_head->_prev = cur;
			return cur;
		}
		else
		{
			Node * cur = BuyNode(x);
			Node * prev = pos._node->_prev;
			Node *next = pos._node;
			prev->_next = cur;
			cur->_prev = prev;
			next->_prev = cur;
			cur->_next = next;
			return next;
		}

	}

protected:
	Node* BuyNode(const T& x)
	{
		return new Node(x);
	}
private:
	Node * _head;
};
// PushBack()/Print()
void TestFun1()
{
List<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	l1.Print();
}
//Erase()/Find()
void TestFun2()
{
	List<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	 l1.Erase(l1.Find(1));
	 l1.Erase(l1.Find(2));
	 l1.Erase(l1.Find(3));
	 l1.Erase(l1.Find(4));
	l1.Print();
}
//insert()
void TestFun3()
{
	List<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.Insert(l1.Find(2), 3);
	l1.Insert(l1.Find(3), 4);
	l1.Insert(l1.Find(4), 5);
	//l1.Insert(l1.Find(1), 3);
	//l1.Insert(l1.Find(1), 4);
	//l1.Insert(l1.Find(1), 5);
	l1.Print();
}
int main()
{
	//TestFun1();
	//TestFun2();
	TestFun3();
		return 0;
}
