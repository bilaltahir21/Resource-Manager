#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "hash_node.h"

const int max_size = 51;

template <class Key, class Data>
class hash_table  // NOLINT
{
public:
	hash_table()
	{
		table_.resize(max_size);
	}

	//Our black-box function to determine 
	//the right index for the incoming key
	int hash_func(const int key) const
	{
		return int(key % max_size);
	}

	Data* get_data(Key key, Data data)
	{
		if (search(key, data))
		{
			const int hash_val = hash_func(key);
			typename list<Data>::iterator iter = table_[hash_val].begin();
			while (*iter != data)
			{
				++iter;
			}
			if (iter != table_[hash_val].end())
			{
				return &(*iter);
			}
		}
		return nullptr;
	}

	void insert(Key key, Data *data)
	{
		const int hash_val = hash_func(key);

		auto point = table_.begin();
		std::advance(point, hash_val);

		point->push_back(*data);
		std::cout << "\nFile inserted...!\n";
	}

	bool search(Key key, Data data)
	{
		const int hash_val = hash_func(key);

		auto point = table_.begin();
		std::advance(point, hash_val);

		auto container = point->begin();
		while (container != point->end())
		{
			if (*(container) == data)
			{
				return true;
			}
			++container;
		}
		return false;
	}

	void remove(Key key, Data *data)
	{
		const int hash_val = hash_func(key);

		auto point = table_.begin();
		std::advance(point, hash_val);

		if (point->empty())
		{
			std::cout << "No data found...!" << std::endl;
			return;
		}

		auto container = point->begin();
		while (*container != *data)
		{
			++container;
		}

		point->erase(container);
		std::cout << "\nFile deleted...!";
	}

	void print_table()
	{
		int num = 0;
		for (auto i = table_.begin(); i != table_.end(); ++i)
		{
			for (auto j = i->begin(); j != i->end(); ++j)
			{
				if (i->empty() == false)
				{
					++num;
					std::cout << "H" << num << "->" << "\t" << *j;
				}
			}
			if (i->empty() == false)
			{
				std::cout << std::endl;
			}
		}
	}

	~hash_table() = default;

protected:
	std::vector<std::list<Data>> table_;
};
