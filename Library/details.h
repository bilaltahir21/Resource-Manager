#pragma once
#include <string>

/*
 *	This class stores the information of the user
 *	which include the user_id, priority, 
 *	and the access type of the user
 */
class details	// NOLINT
{
public:

	int user_id{};
	int priority{};
	std::string access;

	details();

	/*Parameterized constructor which will be used in filing*/
	details(const int id, const int pri, const std::string& acc);

	bool operator!=(const details obj) const;

	bool operator==(const details obj) const;

	bool operator<(const details obj) const;

	bool operator>(const details obj) const;
};
