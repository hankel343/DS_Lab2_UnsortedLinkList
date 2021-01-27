#include "UnsortedList.h"
#include "ItemType.h"
#include <iostream>
#include <string>

using namespace std;

void ListOperationsMenu(UnsortedList &list);
void ProcessListOperation(char selection, UnsortedList &list);
string ConvertToUpperCase(string &userInput);

int main()
{
	UnsortedList list1, list2;
	string input;

	do
	{
		cout << "This program has allocated memory for two empty unsorted lists.\n";
		cout << "Their names are list1 and list2.\n";
		cout << "Enter the name of the list that you would like to perform operations on or press 'Q' to quit.\n";
		cout << "Enter the list name: ";
		cin >> input;
		ConvertToUpperCase(input);
		system("cls");

		if (input == "LIST1") {
			ListOperationsMenu(list1);
		} else if (input == "LIST2") {
			ListOperationsMenu(list2);
		} else {
			cout << "Invalid input - Please try again.\n";
		}
		
	} while (input != "Q");
	
	system("cls");
	cout << "Goodbye...\n";
	

	return 0;
}

void ListOperationsMenu(UnsortedList &list) {
	char selection = NULL;

	do 
	{
		cout << "Enter your selection from the menu below: \n\n";
		cout << "1 - Insert an item into the list.\n";
		cout << "2 - Search for an item in the list.\n";
		cout << "3 - Delete an item from the list.\n";
		cout << "4 - Get the next item in the list.\n";
		cout << "5 - Make the list empty.\n";
		cout << "6 - Reset the list to the first value.\n";
		cout << "7 - Get the length of the list.\n";
		cout << "8 - Union with a second list.\n";
		cout << "9 - Print the list.\n";
		cout << "B - Back.\n\n";
		cout << "Enter your selection: ";
		cin >> selection;
		system("cls");
		ProcessListOperation(selection, list);

	} while (toupper(selection) != 'B');
}

void ProcessListOperation(char selection, UnsortedList& list) {
	switch (toupper(selection)) {
	case '1': {
		ItemType item;
		int inputItem;
		cout << "Enter the information you would like to insert into the list: ";
		cin >> inputItem;

		item.Set(inputItem);
		list.InsertItem(item);

		break;
	} case '2': {
		ItemType item;
		Node *returnValue; //Stores the returned node address from the search.
		int inputItem;
		cout << "Enter the item that you would like to search the list for: ";
		cin >> inputItem;

		item.Set(inputItem); 
		returnValue = list.Search(item); //Search method called (returns an address if found, null if not found)

		if (returnValue == NULL) {
			cout << inputItem << " was not found in the list\n";
		} else {
			cout << returnValue->data.Get() << " was found in the list\n";
		}

		break;
	} case '3': {
		ItemType item;
		int inputItem;
		bool found;
		cout << "Enter the item that you would like to delete from the list: ";
		cin >> inputItem;
		item.Set(inputItem);

		list.DeleteItem(item, found);
		break;

	} case '9': {
		list.PrintList();
		break;
	} case 'B': {
		break;
	} default: {
		cout << "Unknown input - Please try again.\n";
	}
	
	}
}

string ConvertToUpperCase(string& userInput) {
	
	for (int i = 0; i < userInput.length(); i++) {
		userInput[i] = toupper(userInput[i]);
	}

	return userInput;
}