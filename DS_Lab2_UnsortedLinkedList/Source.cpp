#include "UnsortedList.h"
#include "ItemType.h"
#include <iostream>
#include <string>

using namespace std;

void ListOperationsMenu(UnsortedList &activeList, UnsortedList &passiveList);
void ProcessListOperation(char selection, UnsortedList &activeList, UnsortedList &passiveList);
string ConvertToUpperCase(string &userInput);
void ClientInputValidation(int &input);

int main()
{
	UnsortedList list1, list2;
	string input;

	do
	{
		cout << "This program has allocated memory for two empty unsorted linked lists.\n";
		cout << "Their names are list1 and list2.\n";
		cout << "Enter the name of the list that you would like to perform operations on or press 'Q' to quit.\n";
		cout << "Enter the list name: ";
		cin >> input;
		ConvertToUpperCase(input);
		system("cls");

		if (input == "LIST1") {
			ListOperationsMenu(list1, list2);
		} else if (input == "LIST2") {
			ListOperationsMenu(list2, list1);
		} else {
			cout << "Invalid input - Please try again.\n";
		}
		
	} while (input != "Q");
	
	system("cls");
	cout << "Goodbye...\n";
	

	return 0;
}

void ListOperationsMenu(UnsortedList &activeList, UnsortedList &passiveList) {
	char selection = NULL;

	do 
	{
		cout << "Contents of the current list: \n";
		activeList.PrintList();

		if (activeList.GetCurrentPos() != NULL) {
			cout << "\nCurrent position: \n";
			cout << activeList.GetCurrentPos()->data.Get() << endl;
		}

		cout << "\nEnter your selection from the menu below: \n\n";
		cout << "1 - Insert an item into the list.\n";
		cout << "2 - Search for an item in the list.\n";
		cout << "3 - Delete an item from the list.\n";
		cout << "4 - Get the next item in the list.\n";
		cout << "5 - Make the list empty.\n";
		cout << "6 - Reset the list to the first value.\n";
		cout << "7 - Get the length of the list.\n";
		cout << "8 - Union with a second list.\n";
		cout << "9 - Print contents of other list.\n";
		cout << "B - Back.\n\n";
		cout << "Enter your selection: ";
		cin >> selection;
		system("cls");
		ProcessListOperation(selection, activeList, passiveList);

	} while (toupper(selection) != 'B');
}

void ProcessListOperation(char selection, UnsortedList& activeList, UnsortedList& passiveList) {
	switch (toupper(selection)) {
	case '1': {
		ItemType item;
		int inputItem;
		cout << "Enter the information you would like to insert into the list: ";
		if (!(cin >> inputItem)) {
			ClientInputValidation(inputItem);
		}

		item.Set(inputItem);
		activeList.InsertItem(item);

		break;
	} case '2': {
		ItemType item;
		Node *returnValue; //Stores the returned node address from the search.
		int inputItem;
		cout << "Enter the item that you would like to search the list for: ";
		if (!(cin >> inputItem)) {
			ClientInputValidation(inputItem);
		}

		item.Set(inputItem); 
		returnValue = activeList.Search(item); //Search method called (returns an address if found, null if not found)

		if (returnValue == NULL) {
			cout << inputItem << " was not found in the list\n\n";
		} else {
			cout << returnValue->data.Get() << " was found in the list\n\n";
		}

		break;
	} case '3': {
		ItemType item;
		int inputItem;
		bool found;
		cout << "Enter the item that you would like to delete from the list: ";
		if (!(cin >> inputItem)) {
			ClientInputValidation(inputItem);
		}
		item.Set(inputItem);

		activeList.DeleteItem(item, found);
		break;

	} case '4': {
		activeList.GetNextItem();
		break;
	} case '5': {
		activeList.MakeEmpty();
		break;
	} case '6': {
		activeList.ResetList();
		break;
	} case '7': {
		cout << "The current length of the list is: " << activeList.GetLength() << endl;
		break;
	} case '8': {
		//Pointers are declared for the union operation so the destructor is not called on the active or passive list at the end of the method.
		UnsortedList *unionListPtr = new UnsortedList;
		UnsortedList *activeListPtr = &activeList;
		UnsortedList* passiveListPtr = &passiveList;

		cout << "Current list: ";
		activeList.PrintList();
		cout << "Other list: "; 
		passiveList.PrintList();
		cout << "Union of these lists: ";
		//Union returns a pointer, so this simply calls the PrintList() method on the returned pointer to an UnsortedList type.
		activeList.Union(unionListPtr, activeListPtr, passiveListPtr)->PrintList();
		cout << endl;
		break;
	} case '9': {
		cout << "Contents of the other list: \n";
		passiveList.PrintList();
		break;
	} case 'B': {
		break;
	} default: {
		cout << "Unrecognized input - please try again.\n";
	}
	
	}
}

string ConvertToUpperCase(string& userInput) {
	
	for (int i = 0; i < userInput.length(); i++) {
		userInput[i] = toupper(userInput[i]);
	}

	return userInput;
}

void ClientInputValidation(int& input) {
	while (!cin) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\aInput for this program should an integer - please try again: ";
		cin >> input;
	}
}