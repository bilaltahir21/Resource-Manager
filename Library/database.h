#pragma once
#include "hash_table.h"
#include "hash_node.h"
#include <fstream>
#include <sstream>
#include <conio.h>
#include <string>

/*
 *	This the database which is handling all the data of the file and its users
 *	no one can access and change its data in menu
 *	as it has its own interface
 */
class database:public hash_table<int, hash_node>
{
private:
	void print_menu() const;

	/*Trying to remove the redundancy  from the code. So, making a setter function*/
	void value_setter(int& var, const string& msg, const int start, const int end) const;
	/*Same purpose but making specifically for strings*/
	void string_setter(string& var) const;

public:
	void interface();

private:
	hash_table<int, hash_node> obj_;


	/*This the functon to load file even with multiple users*/
	void load_table(const char* file_name, hash_table<int, hash_node>& obj);


	/*
	 *	Making this function a boolean 
	 *	because we want a message on the console 
	 *	if the file has been accessed or the file 
	 *	does not even exist in the file database
	 */
	bool get_access(const int key, const hash_node& data, const details& user_data);

	/*
	*	Making this function a boolean
	*	because we want a message on the console
	*	if the file has been accessed or the file
	*	does not even exist in the file database
	*/
	bool release_access(const int key, hash_node& data, details& user_data);
};
