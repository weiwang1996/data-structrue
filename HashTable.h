#pragma once

#include <vector>

namespace CLOSE
{
	enum State
{
	EMPTY,
	EXIST,
	DELETE,
};

template<class K, class V>
struct HashNode
{
	pair<K,V> _kv;
	State _state;

	HashNode()
		:_state(EMPTY)
	{}
};

template<class K>
struct __Hash
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct __Hash<string>
{
	static size_t BKDRHash(const char * str)
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str )
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}

	size_t operator()(const string& s)
	{
		return BKDRHash(s.c_str());
	}
};

template<class K, class V, class Hash = __Hash<K>>
class HashTable
{
	typedef HashNode<K, V> Node;
public:
	HashTable()
		:_size(0)
	{}

	bool Insert(const pair<K, V>& kv)
	{
		// 空间
		CheckCapacity();

		size_t index = _HashFunc(kv.first);
		size_t i = 1;
		while (_tables[index]._state == EXIST)
		{
			if (_tables[index]._kv.first == kv.first)
			{
				return false;
			}

			index += i*i;
			index %= _tables.size();
			++i;

			// 线性探测
		/*	++index;
			if (index == _tables.size())
			{
				index = 0;
			}*/

			// 二次探测

		}

		_tables[index]._kv = kv;
		_tables[index]._state = EXIST;
		++_size;
		return true;
	}

	Node* Find(const K& key)
	{
		size_t index = _HashFunc(key)%_tables.size();
		while (_tables[index]._state != EMPTY)
		{
			if (_tables[index]._kv.first == key)
			{
				if (_tables[index]._state == EXIST)
				{
					return &_tables[index];
				}
				else
				{
					return NULL;
				}
			}
			++index;
			if (index == _tables.size())
			{
				index = 0;
			}
		}

		return NULL;
	}

	bool Remove(const K& key)
	{
		Node* ret = Find(key);
		if (ret)
		{
			ret->_state = DELETE;
			--_size;
			return true;
		}
		else
		{
			return false;
		}
	}

	size_t _HashFunc(const K& key)
	{
		Hash hash;
		return hash(key)%_tables.size();
	}

	void CheckCapacity()
	{
		if (_tables.empty())
		{
			_tables.resize(GetNextPrime(0));	
		}
		else if (_size*10 / _tables.size() == 7)
		{
			size_t newSize = GetNextPrime(_tables.size());
		/*	vector<Node> newTables;
			newTables.resize(newSize);*/
			HashTable<K, V, Hash> newHT;
			newHT._tables.resize(newSize);
			for (size_t i = 0 ;i < _tables.size(); ++i)
			{
				if(_tables[i]._state == EXIST)
					newHT.Insert(_tables[i]._kv);
			}

			_tables.swap(newHT._tables);
		}
	}

	size_t GetNextPrime(size_t curSize)
	{
		// 使用素数表对齐做哈希表的容量，降低哈希冲突
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList [_PrimeSize] =
		{
			53ul,         97ul,         193ul,       389ul,       769ul,
			1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
			49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		
		for (size_t i = 0; i < _PrimeSize; ++i)
		{
			if (_PrimeList[i] > curSize)
			{
				return _PrimeList[i];
			}
		}

		return _PrimeList[_PrimeSize-1];

	}

protected:
	//pair<K, V>* _tables;
	//size_t _size;
	//size_t _capacity;

	vector<Node> _tables;
	size_t _size;
};

struct StudentInfo
{
	string id;
	string name;
	//....
};

void TestHashTables()
{
	int a[] = {89,18,49,58,9};
	HashTable<int, int> ht;
	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		ht.Insert(make_pair(a[i], i));
	}

	for (size_t i = 0; i < 60; ++i)
	{
		ht.Insert(make_pair(i, i));
	}

	ht.Remove(49);
	HashNode<int, int>* ret = ht.Find(9);

	// 1.哈希关注效率--直接影响效率-哈希冲突 负载因子+素数

	HashTable<string, string> dict;
	dict.Insert(make_pair("left", "左边"));
	dict.Insert(make_pair("eftl", "左边"));
	dict.Insert(make_pair("left11", "左边"));
	dict.Insert(make_pair("left221", "左边"));
	dict.Insert(make_pair("left31", "左边"));
	dict.Insert(make_pair("left3131", "左边"));
	dict.Insert(make_pair("right", "左边"));
	//HashTable<string, int> countHT;

	//HashTable<StudentInfo, int, >
}
}

namespace BUCKET
{
	template<class K, class V>
	struct HashNode
	{
		pair<const K, V> _kvs;
		HashNode<K, V>* _next;

		HashNode(const pair<const K, V>& kv)
			:_kvs(kv)
		{}
	};

	template<class K>
	struct __Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>
	struct __Hash<string>
	{
		static size_t BKDRHash(const char * str)
		{
			unsigned int seed = 131; // 31 131 1313 13131 131313
			unsigned int hash = 0;
			while (*str )
			{
				hash = hash * seed + (*str++);
			}
			return (hash & 0x7FFFFFFF);
		}

		size_t operator()(const string& s)
		{
			return BKDRHash(s.c_str());
		}
	};

	template<class K, class V, class Hash = __Hash<K>>
	class HashTable
	{
		typedef HashNode<K,V> Node;
	public:
		HashTable()
			:_size(0)
		{}

		bool Insert(const pair<const K, V>& kv)
		{
			CheckCapacity();

			size_t index = _HashFunc(kv.first, _tables.size());
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_kvs.first == kv.first)
				{
					return false;
				}

				cur = cur->_next;
			}

			// 头插
			Node* tmp = new Node(kv);
			tmp->_next = _tables[index];
			_tables[index] = tmp;

			++_size;
			return true;
		}

		Node* Find(const K& key)
		{
			size_t index = _HashFunc(key, _tables.size());
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_kvs.first == key)
				{
					return cur;
				}

				cur = cur->_next;
			}

			return NULL;
		}

		bool Remove(const K& key)
		{
			size_t index = _HashFunc(key, _tables.size());
			Node* prev = NULL;
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_kvs.first == key)
				{
					// 1.中间/尾
					// 2.头
					if(prev)
						prev->_next = cur->_next;
					else
						_tables[index] = cur->_next;

					delete cur;

					return true;
				}

				prev = cur;
				cur = cur->_next;
			}

			return false;
		}

		size_t GetNextPrime(size_t curSize)
		{
			// 使用素数表对齐做哈希表的容量，降低哈希冲突
			const int _PrimeSize = 28;
			static const unsigned long _PrimeList [_PrimeSize] =
			{
				53ul,         97ul,         193ul,       389ul,       769ul,
				1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
				49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
				1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
				50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};

			for (size_t i = 0; i < _PrimeSize; ++i)
			{
				if (_PrimeList[i] > curSize)
				{
					return _PrimeList[i];
				}
			}

			return _PrimeList[_PrimeSize-1];
		}

		void CheckCapacity()
		{
			// 负载因子==1是扩容
			if (_size == _tables.size())
			{
				size_t newSize = GetNextPrime(_tables.size());
				vector<Node*> newTables;
				newTables.resize(newSize);

				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;

						size_t index = _HashFunc(cur->_kvs.first, newTables.size());
						cur->_next = newTables[index];
						newTables[index] = cur;

						cur = next;
					}

					_tables[i] = NULL; 
				}

				_tables.swap(newTables);
			}
		}

		size_t _HashFunc(const K& key, size_t size)
		{
			Hash hash;
			return hash(key)%size;
		}
	protected:
		vector<Node*> _tables;
		size_t _size;
	};

	void TestHashTables()
	{
		HashTable<int, int> tables;
		int a[] = {51, 105, 52, 3, 55, 2, 106, 53, 0};
		for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
		{
			tables.Insert(make_pair(a[i], i));
		}

		for (size_t i = 0; i < 80; ++i)
		{
			tables.Insert(make_pair(i, i));
		}

		tables.Remove(55);
		tables.Remove(2);

		cout<<tables.Find(55)<<endl;
		cout<<tables.Find(2)<<endl;

		HashTable<string, string> dict;
		dict.Insert(make_pair("sort", "sort"));
		dict.Insert(make_pair("sort1", "sort"));
		dict.Insert(make_pair("sor1t", "sort"));
		dict.Insert(make_pair("sort32", "sort"));
		dict.Insert(make_pair("left", "sort"));
		dict.Insert(make_pair("right", "sort"));
	}
}

