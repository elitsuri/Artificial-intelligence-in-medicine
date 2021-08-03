#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
//----------------------------------------------------------
using namespace std;
//----------------------------------------------------------
ifstream file;
ofstream file_out;
vector<string> data;
vector<string> temp_vec;
vector<bool> delete_list;
vector<int> days;
vector<vector<string>> my_data;
vector<vector<string>> my_data2;
string val, f_name, l_name, test_date, requ_date, temp, history_time;
string date_delete, time_delete, test_time, requ_time, history_date;
//----------------------------------------------------------
void open_file();
void get_command();
void read_data();
int get_rows();
void transfer_data(int row);
void print_line();
void find_val_delete();
bool delete_value(int row);
void get_value_show();
void display_history();
void update_value();
void get_value_del();
void show_history();
void print_the_line(int row);
//----------------------------------------------------------
int main()
{
	open_file();
	read_data();
	my_data2 = my_data;
	get_command();
	cin.get();
	return(EXIT_SUCCESS);
}
//----------------------------------------------------------
void open_file()
{
	file.open("project_db_forSubmission.csv", std::ios::app);
	if(!file.is_open())
	{
		exit(EXIT_FAILURE);
		cerr << "Can't open file\n";
	}
}
//----------------------------------------------------------
void read_data()
{
	int row;
	row = get_rows();
	my_data.resize(row);
	delete_list.resize(row);
	days.resize(row);
	file.close();
	open_file();
	transfer_data(row);
	file.close();
}
//----------------------------------------------------------
void get_command()
{
	int command = 0;
	while(command != 5)
	{
		cout << "\nEnter command function:\n 1. Display name and value\n"
			<< " 2. Display history\n 3. Update measurement\n"
			<< " 4. Delete Value\n 5. Exit\n\n";
		cout << "Your choice: ";
		cin >> command;
		if(command == 1)
			get_value_show();
		if(command == 2)
			display_history();
		if(command == 3)
			update_value();
		if(command == 4)
			get_value_del();
	}
}
//----------------------------------------------------------
int get_rows()
{
	int row = 0;
	getline(file, temp, '¿');
	while(1)
	{
		getline(file, temp, '\n');
		if(!file.good())
			break;
		row++;
		if(temp == "" || temp == "\n")
			continue;
	}
	return (row - 1);
}
//----------------------------------------------------------
void transfer_data(int row)
{
	int x = 0;
	getline(file, temp, '\n');
	while(1)
	{
		if((!file.good()) || x == row)
			break;
		getline(file, temp, ',');
		if(temp == "")
			getline(file, temp, '\n');
		if(temp == ",")
		{
			x++;
			continue;
		}
		if(x < row)
		{
			my_data[x].push_back(temp);
			continue;
		}
	}
}
//----------------------------------------------------------
void get_value_show()
{
	cout << "\nEnter value: "; cin >> val;
	cout << "Enter first name: "; cin >> f_name;
	cout << "Enter last name: "; cin >> l_name;
	cout << "Enter the test date: "; cin >> test_date;
	cout << "Enter the request date: "; cin >> requ_date; cin >> requ_time;
	requ_date.append(" ").append(requ_time); cout << endl;
	print_line();
}
//----------------------------------------------------------
void print_line()
{
	int idx, max = 0;
	bool flag = true;
	for(unsigned i = 0; i < my_data.size(); i++)
	{
		if(delete_list[i])
			continue;
		string t = requ_date.substr(0, 10);
		string s = my_data[i][6].substr(0, 9);
		string h = my_data[i][5].substr(10, 12);
		string m = my_data[i][5].substr(0, 9);
		int p = stoi(h);
		int date_day = stoi(t);
		if(f_name == my_data[i][0] && l_name == my_data[i][1] &&
		   val == my_data[i][2] && test_date == m)
		{
			idx = i;
			if(requ_date.substr(0, 2) == my_data[i][6].substr(0, 2))
			{			
				if(delete_list[i + 1] && date_day > p)
				{
					print_the_line(i + 1);
					flag = false;
				}
				if(max < p)
				{
					days[i] = date_day;
					max = p;
				}
			}
		}
	}
	if(flag)
	{
		cout << "Obtained: " << my_data[idx][4] << endl;
		cout << "Value: " << my_data[idx][3] << endl;
	}
}
//----------------------------------------------------------
void display_history()
{
	cout << "\nEnter value: "; cin >> val;
	cout << "Enter first name: "; cin >> f_name;
	cout << "Enter last name: "; cin >> l_name;
	cout << "Enter recomanded date: "; cin >> history_date;
	cout << "Enter the start date: "; cin >> test_date;  cin >> test_time;
	test_date.append(" ").append(test_time);
	cout << "Enter the end date: "; cin >> requ_date; cin >> requ_time;
	requ_date.append(" ").append(requ_time); cout << endl;
	show_history();
}
//----------------------------------------------------------
void show_history()
{
	for(unsigned i = 0; i < my_data.size(); i++)
	{
		string the_date = my_data[i][5].substr(0, 9);
		string the = my_data[i][6].substr(0, 9);
		int p = stoi(requ_date);
		int d = stoi(the);

		if(f_name == my_data[i][0] && l_name == my_data[i][1] && val == my_data[i][2]
		   && the_date == history_date && d > 22 && p > d)
		{
			cout << my_data[i][0] << '\n' << my_data[i][1] << '\n'
				<< my_data[i][2] << '\n' << my_data[i][3] << '\n'
				<< my_data[i][4] << '\n' << my_data[i][5] << '\n'
				<< my_data[i][6].append("\n\n");
		}
	}
}
//----------------------------------------------------------
void update_value()
{
	int index;
	cout << "\nEnter value: "; cin >> val;
	cout << "Enter first name: "; cin >> f_name;
	cout << "Enter last name: "; cin >> l_name;
	cout << "Enter recomanded date: "; cin >> history_date; cin >> history_time;
	history_date.append(" ").append(history_time); cout << endl;
	for(unsigned i = 0; i < my_data.size(); i++)
	{
		string the = my_data[i][5].substr(9, 14);
		string d = history_date.substr(9, 14);
		if(f_name == my_data[i][0] && l_name == my_data[i][1]
		   && val == my_data[i][2] && history_date == my_data[i][5])
		{
			if(d == the)
			{
				temp_vec = my_data[i];
				my_data[i][3] = to_string(200);
				index = i;
			}
		}
	}
	cout << my_data[index][4].append(": ").append(my_data[index][3]);
	cout << "\n\n";
	for(int i = 0; i < temp_vec.size(); i++)
		cout << temp_vec[i] << endl;
}
//----------------------------------------------------------
void print_the_line(int row)
{
	for(int i = 0; i < 7; i++)
		cout << my_data2[row][i] << endl;
}
//----------------------------------------------------------
void get_value_del()
{
	cout << "Enter value for delete: "; cin >> val;
	cout << "Enter first name for delete: "; cin >> f_name;
	cout << "Enter last name for delete: "; cin >> l_name;
	cout << "Enter time for delete: "; cin >> date_delete; cin >> time_delete;
	date_delete.append(" ").append(time_delete);
	find_val_delete();
}
//----------------------------------------------------------
void find_val_delete()
{
	unsigned row = 0;
	getline(file, temp, '¿');
	file_out.open("TEMP.csv", std::ios::app);
	open_file();
	while(row < my_data.size())
	{
		getline(file, temp, '\n');
		if(delete_value(row))
		{
			cout << "\nThe value was deleted\n\n";
			delete_list[row] = true;
			temp_vec = my_data[row];
			file_out << temp << endl;
			for(int i = 0; i < 7; i++)
				my_data[row][i] = "";
			my_data[row].resize(0);
			getline(file, temp, '\n');
		}
		else
			file_out << temp << endl;
		if(temp == ",,,,,,,,,")
			break;
		if(temp == "" || temp == "\n")
			continue;
		row++;
	}
	file.close();
	file_out.close();

}
//----------------------------------------------------------
bool delete_value(int row)
{
	return (date_delete == my_data[row][5] && val == my_data[row][2] &&
			f_name == my_data[row][0] && l_name == my_data[row][1]);
}
