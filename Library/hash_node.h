#pragma once
#include "details.h"
#include "max_heap.h"

/*
 *This class has all the information of a file and its users
 * and it is the data stored on each node in the linked list
 */
class hash_node	// NOLINT
{
public:
	/*This is the file number*/
	int filei_id{};
	/*It will manage the current users of teh file*/
	vector<details> currently_accessing;
	/*It will manage the waiting users of the file*/
	max_heap<details> waiting_list;

	/*
	 *	Default constructor but its doing nothing as 
	 *	the data members have some default values 
	 *	assigned to them
	 */
	hash_node();

	/*	
	 *	Parameterized constructor used in filing 
	 */
	hash_node(const int key, const int id, const int priority, const string& access);

	/*A copy constructor*/
	void operator=(const details& obj);

	/*Returns if the waiting list is empty*/
	bool queue_empty() const;

	/*Comparison operator == overloaded*/
	bool operator==(const hash_node obj) const;

	/*Comparison operator != overloaded*/
	bool operator!=(const hash_node obj) const;

	//overloading for printing the hash_node, friend as parameters more than one
	//and also because item class is to the right of ostream(cout), and operator works
	//like object.operator<<(....), by reference return allows cascading
	//friend so implemented here for consistency
	friend std::ostream& operator<<(std::ostream& stream, hash_node& right);
};
