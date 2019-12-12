#include "hash_node.h"

hash_node::hash_node()
{
}

hash_node::hash_node(const int key, const int id, const int priority, const string& access)
{
	filei_id = key;
	const details dat(id, priority, access);
	currently_accessing.push_back(dat);
}

void hash_node::operator=(const details& obj)
{
	if (currently_accessing.empty() && waiting_list.empty())
	{
		currently_accessing.push_back(obj);
	}
	else if (!currently_accessing.empty())
	{
		waiting_list.insert(obj);
	}
}

bool hash_node::queue_empty() const
{
	return waiting_list.empty();
}

bool hash_node::operator==(const hash_node obj) const
{
	return filei_id == obj.filei_id;
}

bool hash_node::operator!=(const hash_node obj) const
{
	return filei_id != obj.filei_id;
}

std::ostream& operator<<(std::ostream& stream, hash_node& right)
{
	/*Checking if there is any user or not*/
	if (right.currently_accessing.empty())
	{
		stream << "No user accessing the file " << right.filei_id << " ...!\n";
		return stream;
	}

	/*Printing the file number*/
	stream << "File " << right.filei_id << "... ";

	/*These conditions are handling the users the access of reading a file*/
	const int users = right.currently_accessing.size();
	const details temp = right.currently_accessing.at(0);
	const string a = "R";
	/*if user is reading*/
	if (temp.access == a)
	{
		stream << "Access granted to ";
		int i = 0;
		for (; i < users && right.currently_accessing.at(i).access == a; i++)
		{
			stream << "User " << right.currently_accessing.at(i).user_id;
			if (i > 0)
			{
				stream << ", ";
			}
		}
		if (i != 1)
		{
			stream << ", ";
		}
		stream << ", READ";

		/*Printing of the next user*/
		if (users > 1)
		{
			stream << "\n\t" << "Next user " << right.currently_accessing.at(1).user_id;
			stream << ", " << right.currently_accessing.at(1).access;
		}

		/*Printing the number of waiting users if there are any*/
		const int waiting_users = right.waiting_list.size();
		if (waiting_users == 0)
		{
			stream << "\n";
			stream << "\t" << "No user waiting...!\n";
			return stream;
		}
		stream << "\n";
		stream << "\t" << waiting_users << " users in waiting queue...!\n";
		return stream;
	}

	/*These are the conditions for the users with access of writing*/
	stream << "Access granted to User ";
	stream << right.currently_accessing.at(0).user_id;
	stream << ", WRITE";

	/*Printing of the next user*/
	if (users > 1)
	{
		stream << "\n\t" << "Next user " << right.currently_accessing.at(1).user_id;
		stream << ", " << right.currently_accessing.at(1).access;
	}

	/*Printing the number of waiting users if there are any*/
	const int waiting_users = right.waiting_list.size();
	if (waiting_users == 0)
	{
		stream << "\n";
		stream << "\t" << "No user waiting...!\n";
		return stream;
	}
	stream << "\n";
	stream << "\t" << waiting_users << " users in waiting queue...!\n";
	return stream;
}
