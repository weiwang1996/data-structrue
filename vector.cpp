#include<iostream>
using namespace std;
template<class T>
class Vector
{
public:
	typedef T* Iterator;
		typedef const T* ConstIterator;
public:
	Vector()
		:_start(0)
		, _finish(0)
		, _endOfStorage(0)
	{
		CheckCapacity();
	}
	Vector(const T*array, size_t size)
		:_start(new T[size])
		, _finish(_start)
		, _endOfStorage(_start + size)
	{
		for (size_t idx = 0; idx < size; ++idx)
		{
			_start[idx] = array[idx];
		}
	}
	Vector<T>&operator=(const Vector<T>& v)
	{
		if (this != &v)
		{
			Vector<int>temp(v);
			Swap(temp);
		}
		return *this;
	}
	~Vector()
	{
		delete[]_start;
		_endOfStorage = NULL;
		_finish = NULL;
	}
	Iterator Begin()
	{
		return _start;
	}
	ConstIterator Begin()const
	{
		return _start;
	}
	Iterator end()
	{
		return _finish;
	}
	ConstIterator end()const
	{
		return _finish;
	}
	size_t Size()const
	{
		return _finish - _start;
	}
	size_t Capacity()const
	{
		return _endOfStorage - _start;
	}
	bool Empty()const
	{
		if (_start == _finish)
			return false;
		else
			return true;
	}
	T &operator[](size_t index)
	{
		return *(_start + index);
	}
	const T &operator[](size_t index)const
	{
		return *(_start + index);
	}
	T &At(size_t index)
	{
		return _start[index];
	}
	const T &At(size_t index)const
	{
		return _start[index];
	}
	// 获取Vector中的第一个元素
	T& Front()
	{
		return *_start;
	}
	const T& Front()const
	{
		return *_start;
	}

	// 获取Vector中的最后一个元素
	T& Back()
	{
		return *_finish;
	}
	const T& Back()const
	{
		return *_finish;
	}

	void PushBack(const T& x)
	{
		CheckCapacity();
		*_finish = x;
		++_finish;
	}
	void PopBack()
	{
		_finish = _finish - 1;
		--_finish;
	}

	// 在pos位置上插入元素x
	Iterator Insert(Iterator pos, const T& x)
	{
		CheckCapacity();
		if (pos == _finish)
		{
			PushBack(x);
			return pos;
		}
		Iterator cur = _finish;
		while (cur != pos)
		{
			*cur = *(cur - 1);
			cur = cur - 1;
		}
		*pos = x;
		++_finish;
		return pos;
	}

	// 删除pos位置上面的元素
	Iterator Erase(Iterator pos)
	{
		delete *pos;
		while (pos<_finish)
		{
			*(pos) = *(pos + 1);
			pos++;
		}
		_finish--;
		return pos;
	}

	// 给Vector赋值n个值为x的元素
	void Assign(size_t n, const T& x)
	{

		CheckCapacity()
			int i = 0;
		while (i < n)
		{
			PushBack(x);
			i++;
		}
	}

private:
	Iterator _start;
	Iterator _finish;
	Iterator _endOfStorage;
private:
	void CheckCapacity()
	{
		if (_finish == _endOfStorage)
		{
			size_t capacity = 2 * (_endOfStorage - _start) + 1;
			T* temp = new T[capacity];
			T*pos = _start;
			size_t idx = 0;
			while (pos < _endOfStorage)
			{
				temp[idx] = *pos;
				idx++;
				pos++;
			}
			delete[]_start;
			_start = temp;
			_finish = _start + idx;
			_endOfStorage = _start + capacity;
		}
	}
	void Swap(Vector<T>&v)
	{
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endOfStorage, v._endOfStorage);
	}
};
int main()
{
	return 0;
}