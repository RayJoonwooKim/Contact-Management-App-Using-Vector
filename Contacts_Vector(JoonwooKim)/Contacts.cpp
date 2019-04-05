#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

/*
Author : Joonwoo Kim
Project : Project 2
Objective : To create Contact Management Application using Vector
Date : 2018 April 11
*/
struct Contact
{
	int ID;
	string fn;
	string ln;
	string address;
	string phone;
};
struct SortID
{
	bool operator()(Contact c1, Contact c2)
	{
		return c1.ID < c2.ID;
	}
};
struct SortName
{
	bool operator()(Contact c1, Contact c2)
	{
		return c1.fn < c2.fn;
	}
};
struct SearchID
{
	int key;
	SearchID() {}
	SearchID(int _key)
	{
		key = _key;
	}
	bool operator () (Contact &c)
	{
		return c.ID == key;
	}
};
struct SearchName
{
	string key;
	SearchName() {}
	SearchName(string _key)
	{
		key = _key;
	}
	bool operator () (Contact &c)
	{
		return c.fn + " " +c.ln == key;
	}
};
int MainMenu();
void add_contact(vector<Contact> &, int);
void display_contact(vector<Contact> &);
void sort_ID(vector<Contact> &);
void sort_name(vector<Contact> &);
void search_ID(vector<Contact> &, vector<Contact> ::iterator);
void search_contact_name(vector<Contact> &, vector<Contact> ::iterator);
void remove_contact(vector<Contact> &, vector<Contact> ::iterator);
int main()
{
	int howMany;
	int choice;
	char ans;
	cout << "\n\n\t\tHow many contacts do you want to add?  ";
	cin >> howMany;
	system("cls");
	
	
	Contact *cont;
	cont = new Contact[howMany];
	vector<Contact> vect_contact;
	vector<Contact> ::iterator p = vect_contact.begin();
	
	do
	{
		system("cls");

		choice = MainMenu();
		switch (choice)
		{
		case 1:
			system("cls");
			add_contact(vect_contact, howMany);
			break;
		case 2:
			system("cls");
			display_contact(vect_contact);
			break;
		case 3:
			system("cls");
			sort_ID(vect_contact);
			display_contact(vect_contact);
			break;
		case 4:
			system("cls");
			sort_name(vect_contact);
			display_contact(vect_contact);
			break;
		case 5:
			system("cls");
			search_ID(vect_contact, p);
			break;
		case 6:
			system("cls");
			search_contact_name(vect_contact, p);
			break;
		case 7:
			system("cls");
			remove_contact(vect_contact, p);
			break;
		case 8:
			cout << endl << endl;
			system("pause");
			return 0;
		}
		cout << "\n\n\t\tDo you want to go back to main menu? (Y/N)";
		cin >> ans;
	} while (toupper(ans) =='Y');
	
	

	system("pause");
	return 0;
}

int MainMenu()
{
	int choice;

	cout << "\n\t\t\t\tContact Management" << endl;
	cout << "\n\t\t\t\t==================";
	cout << "\n\n\t1. Add Contact";
	cout << "\n\t2. Display Contact";
	cout << "\n\t3. Sort Contact By ID";
	cout << "\n\t4. Sort Contact By Name";
	cout << "\n\t5. Search By ID";
	cout << "\n\t6. Search By Name";
	cout << "\n\t7. Remove Contact";
	cout << "\n\t8. Exit the application";
	cout << "\n\n\tChoose your option : ";
	cin >> choice;

	return choice;
}
void add_contact(vector<Contact> &vect_contact, int howMany)
{
	Contact c;
	bool error = false;
	bool empty = false;
	for (int i = 0; i < howMany; i++)
	{
		do
		{
			error = false;
			cout << "Enter ID : ";
			cin >> c.ID;
			cin.ignore();
			if (cin.fail())
			{
				cout << "ID must be integer value!";
				error = true;
				cin.clear();
				cin.ignore(257, '\n');
				system("pause");
			}
		} while (error);

		do
		{
			error = false;
			cout << "Enter First Name : ";
			getline(cin, c.fn);
			if (cin.fail())
			{
				cout << "You have entered invalid first name! Please try again!";
				error = true;
				cin.clear();
				cin.ignore();
				system("pause");
			}
			
		} while (error);

		do
		{
			error = false;
			cout << "Enter Last Name: ";
			getline(cin, c.ln);
			if (cin.fail())
			{
				cout << "You have entered invalid last name! Please try again!";
				error = true;
				cin.clear();
				cin.ignore();
				system("pause");
			}
		} while (error);

		cout << "Enter address: ";
		getline(cin, c.address);

		do
		{
			error = false;
			cout << "Enter Phone Number : ";
			cin >> c.phone;
			if (cin.fail())
			{
				error = true;
				cout << "You have entered invalid phone number! Please try again!";
				cin.clear();
				cin.ignore();
				system("pause");
			}
		} while (error);
		cout << endl;

		vect_contact.push_back(c);
	}
	
}
void display_contact(vector<Contact> &vect_contact)
{
	vector<Contact> ::iterator p = vect_contact.begin();
	system("cls");
	cout << "\t\t\nCONTACT LIST";
	cout << "\t\t\n================";
	for (p; p < vect_contact.end(); p++)
	{
		cout << "\nID : " << p->ID;
		cout << "\nName : " << p->fn << " " << p->ln;
		cout << "\nAddress : "<<p->address;
		cout << "\nPhone : " << p->phone;
		cout << endl;
	}
}

void sort_ID(vector<Contact> &vect_contact)
{
	sort(vect_contact.begin(), vect_contact.end(), SortID());
}

void sort_name(vector<Contact> &vect_contact)
{
	sort(vect_contact.begin(), vect_contact.end(), SortName());
}

void search_ID(vector<Contact> &vect_contact, vector<Contact> ::iterator p)
{
	int ID;
	cout << "Enter ID to search : ";
	cin >> ID;

	p = find_if(vect_contact.begin(), vect_contact.end(), SearchID(ID));

	if (p->ID == ID)
	{
		cout << "\nID : " << p->ID;
		cout << "\nName : " << p->fn << " " << p->ln;
		cout << "\nAddress : " << p->address;
		cout << "\nPhone : " << p->phone;
		cout << endl;
	}
	else
	{
		cout << "\n\nID does not exist!";
	}
}
void search_contact_name(vector<Contact> &vect_contact, vector<Contact> ::iterator p)
{
	bool found = false;
	string search_name;
	cout << "Please enter the full name to search : ";
	cin.ignore();
	getline(cin, search_name);

	p = find_if(vect_contact.begin(), vect_contact.end(), SearchName(search_name));

	if (p->fn + " " +p->ln == search_name)
	{
		cout << "\nID : " << p->ID;
		cout << "\nName : " << p->fn << " " << p->ln;
		cout << "\nAddress : " << p->address;
		cout << "\nPhone : " << p->phone;
		cout << endl;
	}
	else
	{
		cout << "\n\nName does not exist!";
	}
	
}
void remove_contact(vector<Contact> &vect_contact, vector<Contact> ::iterator p)
{
	int ID;
	cout << "Enter the ID to remove from the vector : ";
	cin >> ID;
	p = find_if(vect_contact.begin(), vect_contact.end(), SearchID(ID));

	if (p->ID == ID)
	{
		vect_contact.erase(p);
		cout << "\n\nData removed successfully!" << endl;

	}
	else
	{
		cout << "\n\nData Not Found!" << endl;
	}

}
