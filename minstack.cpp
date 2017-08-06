#include<iostream>
#include<stack>
using namespace std;
template<class T>
class MinStack
{
public:
	void Push(const T&t)
	{
		s.push(t);
		if (min.empty() || t < min.top())
		{
			min.push(t);
		}
		else
		{
			min.push(min.top());
		}
	}
	void Pop()
	{
		if (!s.empty())
		{
			s.pop();
			min.pop();
		}
	}
	T& Min()
	{
		return min.top();
	}
	T& Top()
	{
		return s.top();
	}
	size_t Size()
	{
		return s.size();
	}
	bool Empty()
	{
		return s.empty();
	}
private:
	stack<T> s;
	stack<T> min;
};
int main()
{
	MinStack<int> s1;
	s1.Push(1);
	s1.Push(6);
	s1.Push(0);
	s1.Push(9);
	s1.Push(2);	
	s1.Pop();
	s1.Pop();
	s1.Pop();
	s1.Pop();
	cout << s1.Top()<<endl;
	cout << s1.Min();
}
char SearchChar(const char* str)
{
	char HushTable[256] = {0};//创建字符的哈希表
	while (*str != '\0')
	{
		if (HushTable[*str] == 0)
			++HushTable[*str];
		else
			return *str;
		str++;
	}
}
int main()
{
	char *str = "abcdefbcdefabc";
	cout << SearchChar(str)<<endl;
	return 0;
}