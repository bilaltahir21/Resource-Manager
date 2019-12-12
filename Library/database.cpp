#include  "database.h"

void database::print_menu() const
{
	cout << "						Files Database";
	cout << "\n1. Print file information from database";
	cout << "\n2. Load data from file in Library";
	cout << "\n3. Insert a file";
	cout << "\n4. Delete a file";
	cout << "\n5. Request access to a file";
	cout << "\n6. Release a file by a user\n\n";

	cout << "Enter KEY for required operation: ";
}

void database::value_setter(int& var, const string& msg, const int start, const int end) const
{
	bool check = true;
	int value;
	while (check)
	{
		cin >> value;
		if (value >= start && value <= end)
		{
			var = value;
			check = false;
		}
		else
		{
			cout << endl << msg << ": ";
		}
	}
}

void database::string_setter(string& var) const
{
	bool check = true;
	char value;
	while (check)
	{
		cin >> value;
		if (value == 'R' || value == 'W')
		{
			var = value;
			check = false;
		}
		else
		{
			cout << endl << "Enter the value again ('R' or 'W'): ";
		}
	}
}

void database::interface()
{
	print_menu();

	char choice = NULL;
	cin.get(choice);
	while (choice != '`')
	{
		if (choice == '1')
		{
			system("CLS");
			obj_.print_table();
			_getch();
		}
		else if (choice == '2')
		{
			system("CLS");
			load_table("users.txt", obj_);
			_getch();
		}
		else if (choice == '3')
		{
			system("CLS");
			//code to insert a file
			int file_id;
			cout << "Enter FileID (5000-99999): ";
			value_setter(file_id, "Enter FileID again (5000-99999):", 5000, 99999);

			int user_id;
			cout << "\nEnter UserID (0-10000): ";
			value_setter(user_id, "\nEnter UserID again (0-10000): ", 0, 10000);

			int priority;
			cout << "\nEnter priority (0-100):";
			value_setter(priority, "\nEnter priority again (0-100):", 0, 100);

			string access;
			cout << "\nHow you want to access file? ('R' or 'W'):";
			string_setter(access);

			auto* data = new hash_node(file_id, user_id, priority, access);
			obj_.insert(file_id, data);

			_getch();
		}
		else if (choice == '4')
		{
			system("CLS");
			//code to delete a file
			int file_id;
			cout << "Enter FileID (5000-99999): ";
			value_setter(file_id, "Enter FileID again (5000-99999):", 5000, 99999);

			int user_id;
			cout << "\nEnter UserID (0-10000): ";
			value_setter(user_id, "\nEnter UserID again (0-10000): ", 0, 10000);

			int priority;
			cout << "\nEnter priority (0-100):";
			value_setter(priority, "\nEnter priority again (0-100):", 0, 100);

			string access;
			cout << "\nHow you want to access file? ('R' or 'W'):";
			string_setter(access);

			auto* data = new hash_node(file_id, user_id, priority, access);
			obj_.remove(file_id, data);
			_getch();
		}
		else if (choice == '5')
		{
			system("CLS");

			int file_id;
			cout << "Enter FileID (5000-99999): ";
			value_setter(file_id, "Enter FileID again (5000-99999):", 5000, 99999);

			int user_id;
			cout << "\nEnter UserID (0-10000): ";
			value_setter(user_id, "\nEnter UserID again (0-10000): ", 0, 10000);

			int priority;
			cout << "\nEnter priority (0-100):";
			value_setter(priority, "\nEnter priority again (0-100):", 0, 100);

			string access;
			cout << "\nHow you want to access file? ('R' or 'W'):";
			string_setter(access);

			hash_node h;
			h.filei_id = file_id;
			details d;
			d.user_id = user_id;
			d.priority = priority;
			d.access = access;

			/*
			 *Printing if the file has been print or the file
			 * does not even exist in the file database
			 */
			const bool if_access = get_access(file_id, h, d);
			if (!if_access)
			{
				cout << "\nFILE DOES NOT EXIST\n";
			}
			else
			{
				cout << "\nFile accessed...!\n";
			}
			_getch();
		}
		else if (choice == '6')
		{
			system("CLS");


			int file_id;
			cout << "Enter FileID (5000-99999): ";
			value_setter(file_id, "Enter FileID again (5000-99999):", 5000, 99999);

			int user_id;
			cout << "\nEnter UserID (0-10000): ";
			value_setter(user_id, "\nEnter UserID again (0-10000): ", 0, 10000);

			hash_node h;
			h.filei_id = file_id;
			details d;
			d.user_id = user_id;

			/*
			 *Printing if the file has been print or the file
			 * does not even exist in the file database
			 * 1. FileID, 2.Data from getter, 3.User to delete
			 */
			const bool if_access = release_access(file_id, h, d);
			if (!if_access)
			{
				cout << "\nFILE DOES NOT EXIST\n";
			}
			else
			{
				cout << "\nFile released...!\n";
			}

			_getch();
		}

		cin.get(choice);
		system("CLS");
		print_menu();
	}

	cout << endl;
}

void database::load_table(const char* file_name, hash_table<int, hash_node>& obj)
{
	//input stream for filing
	std::ifstream input_file(file_name);

	//if file is available
	if (input_file.fail())
	{
		std::cout << "file error!\n";
		return;
	}

	std::string input, token;
	std::vector<std::string> storage;

	//to skip the first line of description
	std::getline(input_file, input);

	/*
	 *Here we're using a stringStream to act as a stream
	 *which is used in the function std::getline()
	 *and the vector is being used to store the tokens,
	 *we made. And the max_heap object 'obj' is passed by
	 *reference to make the real changes.
	 */

	while (std::getline(input_file, input))
	{
		if (!input.empty() && input != "\t")
		{
			std::istringstream ss(input);

			while (std::getline(ss, token, '\t'))
			{
				storage.push_back(token);
			}
			//Data parsed in vector "storage" as
			//0. File ID, 1. User ID, 2. Priority, 3. Access

			const int file_id = atoi(storage[0].c_str());

			hash_node data(file_id, atoi(storage[1].c_str()), atoi(storage[2].c_str()), storage[3]);
			/*Writer got exclusive access*/
			if (storage[3] == "W")
			{
				if (!storage.empty())
				{
					for (int i = 4; i < int(storage.size()); i = i + 3)
					{
						const details temp(atoi(storage[i].c_str()), atoi(storage[i + 1].c_str()), storage[i + 2]);
						data.waiting_list.insert(temp);
					}
				}
				obj.insert(file_id, &data);
			}
			else
			{
				if (!storage.empty())
				{
					bool check = true;
					for (int i = 4; i < int(storage.size()); i = i + 3)
					{
						details temp(atoi(storage[i].c_str()), atoi(storage[i + 1].c_str()), storage[i + 2]);
						/*
						 *This is the condition to if the next user is writing
						 *then we will write everything to the waiting queue
						 *
						 */
						if (storage[i + 2] == "W")
						{
							check = false;
						}
						if (check)
						{
							if (data.currently_accessing.at(0).access == "R" && temp.access == "R")
							{
								data.currently_accessing.push_back(temp);
							}
						}
						else
						{
							data.waiting_list.insert(temp);
						}
					}
				}
				obj.insert(file_id, &data);
			}
			//managing vector space
			storage.clear();
		}
	}

	input_file.close();

	system("CLS");
	cout << "\nTable loaded...!\n";
}

bool database::get_access(const int key, const hash_node& data, const details& user_data)
{
	hash_node* temp = obj_.get_data(key, data);
	if (temp)
	{
		if (temp->currently_accessing.empty() && temp->waiting_list.empty())
		{
			temp->currently_accessing.push_back(user_data);
		}
		else
		{
			temp->waiting_list.insert(user_data);
		}
		return true;
	}
	return false;
}

bool database::release_access(const int key, hash_node& data, details& user_data)
{
	hash_node* temp = obj_.get_data(key, data);

	/*
	 *	Now we will use use the pointer of the object
	 *	which we have taken from the table and
	 *	we will change the object because we have access to the real object
	 */

	vector<details>::iterator iter = temp->currently_accessing.begin();
	int count = 0;
	if (!temp->currently_accessing.empty())
	{
		while (iter != temp->currently_accessing.end())
		{
			/*making the iterator traverse to correct position*/
			if (*iter == user_data)
			{
				break;
			}
			count++;
			++iter;
		}
	}
	if (count == int(temp->currently_accessing.size())) //type casting to avoid some warning generated by compilor
	{
		cout << "USER DOES NOT EXIST...!";
		return false;
	}

	temp->currently_accessing.erase(iter);

	/*moving the users from the waiting list to the vector of currently accessing users*/
	if (!temp->waiting_list.empty() && temp->waiting_list.find_max().access == "R")
	{
		while (!temp->waiting_list.empty() && temp->waiting_list.find_max().access == "R")
		{
			details tempX(temp->waiting_list.extract_max());
			temp->currently_accessing.push_back(tempX);
		}
	}
	return true;
}