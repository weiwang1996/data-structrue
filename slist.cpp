#include<iostream>
using namespace std;
template<class T>
struct ListNode
{
	T _data;
	ListNode* _next;
	ListNode(const T&x)
		:_data(x)
		, _next(NULL)
	{}
};
template<class T>
class SeqList
{
	typedef ListNode<T> Node;
public:
	SeqList()
		:_pHead(NULL)
	{}
	~SeqList()
	{
		/*Node* cur = _pHead;
		while (cur)
		{
			Node* del = cur;
			cur = cur->_next;
			_pHead = cur;
			delete del;
			del = NULL;
		}
	_pHead = NULL;*/
	}
	void PushBack(const T& x)
	{
		if (_pHead == NULL)
		{
			_pHead = new Node(x);
		}
		else
		{
			Node* cur=_pHead;
			while (cur->_next)
				cur = cur->_next;
			cur->_next = new Node(x);
		}
	}
	Node*& GetHead()
	{
		return _pHead;
	}

	void Print()
	{
		if (_pHead == NULL)
			return;
		Node* cur =_pHead;
		while (cur)
		{
			cout << cur->_data<<"->";
			cur = cur->_next;
			if (cur == NULL)
				cout << "NULL";
		}
		cout << endl;
	}
	void Reverse()
	{
		if (_pHead == NULL || _pHead->_next == NULL)
			return;
		Node* temp = NULL;
		Node* cur = _pHead;
		Node* newHead = NULL;
		while (cur)
		{
			temp = cur;
			cur = cur->_next;	
			temp->_next = newHead;
			newHead = temp;
		}
		_pHead = newHead;
	}
	void Merge(Node* Head)
	{
		_pHead=_Merge(_pHead, Head);
	}
	void BubbleSort()
	{
		if (_pHead == NULL||_pHead->_next==NULL)
			return;
		Node* pTail = NULL;
		Node*cur = _pHead;
		while (cur)
		{
			cur = cur->_next;
		}
		pTail=cur;
		while (pTail != _pHead)
		{
			bool flag = false;
			cur = _pHead;
			Node* next = cur->_next;
			while (next != pTail)
			{
				if ((cur->_data) > (next->_data))
				{
					swap(cur->_data, next->_data);
					flag = true;
				}
				cur = cur->_next;
				next = next->_next;
			}
			if (flag == false)
				break;
			pTail = cur;
		}
	}
	Node* Find(const T&x)
	{
		if (_pHead == NULL)
			return NULL;
		Node* cur = _pHead;
		while (cur)
		{
			if (cur->_data == x)
				return cur;
			cur = cur->_next;
		}
		return NULL;
	}

	bool IsCircle()
	{
		if (_pHead == NULL)
			return false;
		Node* pFast = _pHead;
		Node* pSlow = _pHead;
		while (pFast&&pFast->_next)
		{
			pSlow = pSlow->_next;
			pFast = pFast->_next->_next;
			if (pFast == pSlow)
				return true;
		}
		return false;
	}

protected:
	Node* _Merge(Node* pHead1, Node*pHead2)
	{
		Node* newhead=NULL;
		if (pHead1 == NULL)
			return pHead2;
		else if (pHead2 == NULL)
			return pHead1;

		if (pHead1->_data < pHead2->_data)
		{
			newhead = pHead1;
			newhead->_next = _Merge(pHead1->_next, pHead2);
		}
		else
		{
			newhead = pHead2;
			newhead->_next = _Merge(pHead1, pHead2->_next);
		}
		return newhead;
	}
	Node* _pHead;
};
void Test()
{
	SeqList<int> list;
	list.PushBack(1);
	list.PushBack(6);
	list.PushBack(3);
	list.PushBack(2);
	list.PushBack(5);
	list.PushBack(7);
	//list.Find(7)->_next = list.Find(3);
	cout<<list.IsCircle()<<endl;
//	list.Print();
//	list.BubbleSort();
//	list.Print();
}
int main()
{
	Test();
	return 0;
}