/*Hankel Haldin
 *Data Structures Lab 2: Unsorted Link List
 *Due: 2/3/2021
 *Main.cpp is basic client software that allows the user to perform basic list operations on a unsorted list implemented as a linked list.
 *Method headers for the UnsortedList class are found in UnsortedList.h and their implementations in UnsortedList.cpp.
 *This program also makes use of a class called ItemType that allows for client software to use UnsortedList regardless of data that will be in the list.*/

#include "UnsortedList.h"
#include "ItemType.h"
#include <iostream>
#include <string>

using namespace std;

void ListOperationsMenu(UnsortedList &activeList, UnsortedList &passiveList);
//Pre: Memory should be allocated for two UnsortedList types and their locations should be passed as arguments.
//Post: The memory address of the list to have operations performed on it is set to activeList.

void ProcessListOperation(char selection, UnsortedList &activeList, UnsortedList &passiveList);
//Pre: Memory is allocated for two UnsortedList types and user input has been read into char identifier selection.
//Post: Function will perform the specified operation on the activeList UnsortedList.

string ConvertToUpperCase(string &userInput);
//Pre: Memory has been allocated for a string identifier called userInput and user has entered information from keyboard.
//Post: User keyboard input is converted to uppercase.

void ClientInputValidation(int &input);
//Pre: Memory has been allocated for an integer identifier called input.
//Post: User is prompted for input until valid input is provided.

int main()
{
	UnsortedList list1, list2;
	string input;

	do
	{
		cout << "This program has allocated memory for two empty unsorted linked lists.\n";
		cout << "Their names are list1 and list2.\n";
		cout << "Enter the name of the list (\"list1\" or \"list2\") that you would like to perform operations on or press 'Q' to quit.\n";
		cout << "Enter the list name: ";
		cin >> input;
		ConvertToUpperCase(input);
		system("cls");

		//Determines which list will have operations performed on it.
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

		cout << "\nEnter your selection from the menu below: \n\n";
		cout << "1 - Insert an item into the list.\n";
		cout << "2 - Search for an item in the list.\n";
		cout << "3 - Delete an item from the list.\n";
		cout << "4 - Get the next item in the list.\n";
		cout << "5 - Make the list empty.\n";
		cout << "6 - Reset the list to the first value.\n";
		cout << "7 - Get the length of the list.\n";
		cout << "8 - Union with a second list.\n";
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
		if (activeList.GetLength() == 0) { //If the list is empty the GetNextItem() method is not called.
			cout << "The list is currently empty.\n";
		} else {
			cout << "The next item in the list is: " << activeList.GetNextItem().Get() << endl;;
		}
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
		//Following pointers are declared for the union operation so the destructor is not called on the active or passive list at the end of the method.
		UnsortedList *unionListPtr = new UnsortedList;
		UnsortedList *activeListPtr = &activeList;
		UnsortedList* passiveListPtr = &passiveList;

		if (activeList.GetLength() == 0 || passiveList.GetLength() == 0) {
			cout << "One of the lists is empty.\n";
		} else {
			cout << "Union of these lists: ";
			//Union returns a pointer, so this simply calls the PrintList() method on the returned pointer to an UnsortedList type.
			activeList.Union(unionListPtr, activeListPtr, passiveListPtr)->PrintList();
			cout << endl;
		}
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