#pragma once
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

// Max Heap
template<class T>
class max_heap
{
private:
	// vector to store heap elements
	std::vector<T> h_;
	T temp_min_;

	// return parent of A[i]
	// don't call this function if it is already a root node
	int parent(const int i) const
	{
		return (i - 1) / 2;
	}

	/*---------------------------------Function to heapify-down the values---------------------------------*/
	// Heapifying-down recursively
	// the node at index i and its two direct children
	// violates the heap property
	void heapify_down(int i)
	{
		/*
		 *	Here we'll calculate the indices of the direct children of the given value in the heap
		 *	then we will calculate the greater value from the parent and its children.
		 *	Then we'll select the required index and shift it down with the greater value using swapping.
		 *	This function will be called recursively.
		 */

		// index of the left child
		int left = 2 * i + 1;
		// index of the right child
		int right = 2 * i + 2;
		/*
		 *	Storing the value of the parent as the greater value,
		 *	which might not be the case in every scenario
		 */
		int largest = i;


		/*
		 *	compare A[i] with its left and right child
		 *	and find largest value
		 */
		if (left < int(size()) && (h_[left] > h_[i]))
		{
			largest = left;
		}

		if (right < int(size()) && h_[right] > h_[largest])
		{
			largest = right;
		}

		/*
		 *	Swapping child with greater value
		 *	and heapifying-down using child
		 */
		if (largest != i)
		{
			swap(h_[i], h_[largest]);
			heapify_down(largest);
		}
	}

	/*----------------------------------Function to heapify-up the values---------------------------------*/
	void heapify_up(int i)
	{
		/*
		 *	Same terminology as the heapify_down is being used
		 *	where there is the parent with the smaller value, we will
		 *	shift the child up by swapping. Then the function will
		 *	be called recursively.
		 */
		// check if node at index i and its parent violates 
		// the heap property
		if (i /*if current is not node*/ && h_[parent(i)] < h_[i])
		{
			// swap the two if heap property is violated
			//T holder = h_[i];
			//h_[i] = h_[parent(i)];
			//h_[parent(i)] = h_[i];
			swap(h_[i], h_[parent(i)]);

			// call Heapify-up on the parent
			heapify_up(parent(i));
		}
	}

public:
	max_heap()
	{
		
	};

	//Building a priority queue from an unsorted array
	void build_queue(std::vector<T> arra)
	{
		typename std::vector<T>::iterator i = arra.begin();
		for (; i < arra.end(); ++i)
		{
			insert(*i);
		}
	}

	vector<T> ret()
	{
		return h_;
	}

	// return size of the heap
	int size() const
	{
		return int(h_.size());
	}

	// function to check if heap is empty or not
	bool empty() const
	{
		return size() == 0;
	}

	// insert key into the heap
	void insert(T key)
	{
		if(h_.empty())
		{
			temp_min_ = key;
		}
		if (key < temp_min_)
		{
			temp_min_ = key;
		}

		// insert the new element to the end of the vector
		h_.push_back(key);

		// get element index and call heapify-up procedure
		const int index = size() - 1;
		heapify_up(index);
	}

	/*
	 *	function to remove element with highest priority
	 *	(which is always present at root)
	 */
	T extract_max()
	{
		try
		{
			// if heap has no elements, throw an exception
			if (size() == 0)
				throw std::out_of_range("Vector<X>::at() : "
					"index is out of range -> (Heap underflow) ");

			// replace the root of the heap with the last element
			// of the vector
			T holder = h_[0];
			h_[0] = h_.back();
			h_.pop_back();

			// call heapify-down on root node
			heapify_down(0);

			return holder;
		}
			// catch and print the exception
		catch (const std::out_of_range& oor)
		{
			std::cout << "\n" << oor.what();
		}
		return temp_min_;
	}

	// function to return element with highest priority (present at root)
	T find_max()
	{
		try
		{
			// if heap has no elements, throw an exception
			if (size() == 0)
				throw std::out_of_range("Vector<X>::at() : "
					"index is out of range -> (Heap underflow) ");

			// else return the top (first) element
			return h_.at(0); // which is root at h_[0]
		}
			// catch and print the exception
		catch (const std::out_of_range& oor)
		{
			std::cout << "\n" << oor.what();
		}
		return temp_min_;
	}

	T find_second_max()
	{
		try
		{
			// if heap has no elements, throw an exception
			if (size() < 2)
				throw std::out_of_range("Vector<X>::at() : "
					"index is out of range -> (Heap underflow) ");

			T temp = extract_max();
			T holder = find_max();
			insert(temp);
			return holder;
		}
		// catch and print the exception
		catch (const std::out_of_range& oor)
		{
			std::cout << "\n" << oor.what();
		}
		return temp_min_;
	}

	T find_min()
	{
		try
		{
			// if heap has no elements, throw an exception
			if (size() == 0)
				throw std::out_of_range("Vector<X>::at() : "
					"index is out of range -> (Heap underflow) ");

			// else return the top (first) element
			return temp_min_; // which is root at h_[0]
		}
			// catch and print the exception
		catch (const std::out_of_range& oor)
		{
			std::cout << "\n" << oor.what();
		}
		return temp_min_;
	}

	bool operator==(max_heap<T> obj)
	{
		return static_cast<bool>(h_ == obj.ret());
	}

	bool operator!=(max_heap<T> obj)
	{
		return static_cast<bool>(h_ != obj.ret());
	}

};
