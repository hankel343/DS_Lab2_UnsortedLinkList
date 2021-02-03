/*Hankel Haldin
 *Data Structures Lab 2: Unsorted Link List
 *Due: 2/3/2021
 *Main.cpp is basic client software that allows the user to perform basic list operations on a unsorted list implemented as a linked list.
 *Method headers for the UnsortedList class are found in UnsortedList.h and their implementations in UnsortedList.cpp.
 *This program also makes use of a class called ItemType that allows for client software to use UnsortedList regardless of data that will be in the list.*/

#include "ItemType.h"
#include "UnsortedList.h"
#include <iostream>

using namespace std;

void ListOperationsMenu(UnsortedList *list);
//Pre: Memory should be allocated for two UnsortedList types and their locations should be passed as arguments.
//Post: The memory address of the list to have operations performed on it is set to activeList.

void ProcessListOperation(UnsortedList *list, char selection);
//Pre: Memory is allocated for two UnsortedList types and user input has been read into char identifier selection.
//Post: Function will perform the specified operation on the activeList UnsortedList.

void MakeUnion(UnsortedList *list1, UnsortedList *list2, UnsortedList *unionList);
//Pre: Memory has been allocated for three unsorted list objects and the source lists are not empty.
//Post: The target list has been populated with the unique elements of the two source lists.

void ClientInputValidation(int &input);
//Pre: Memory has been allocated for an integer identifier called input.
//Post: User is prompted for input until valid input is provided.

string ConvertToUpperCase(string& userInput);
//Pre: Memory has been allocated for a string identifier called userInput and user has entered information from keyboard.
//Post: User keyboard input is converted to uppercase.

int main()
{
	//Creating pointers to three lists.
	UnsortedList *list1, *list2, *unionList;
	//Populating each pointer with addresses of UnsortedLists from heap memory.
	list1 = new UnsortedList;
	list2 = new UnsortedList;
	unionList = new UnsortedList;
	string input;

	do
	{
		cout << "Memory has been allocated for two unsorted linked lists.\n";
		cout << "Enter either \"list1\" or \"list2\" to access either list to perform operations on it.\n";
		cout << "Once each list contains data, enter \"union\" to create a third list that is the union of list1 and list2.\n";
		cout << "Enter 'Q' to quit.\n";
		cin >> input;

		system("cls");

		ConvertToUpperCase(input);

		if (input == "LIST1") {
			ListOperationsMenu(list1);
		} else if (input == "LIST2") {
			ListOperationsMenu(list2);
		} else if (input == "UNION" && (list1->GetLength() == 0 || list2->GetLength() == 0)) {
			cout << "Atleast one of the lists to perform the union on is empty.\nAdd elements to both before performing a union.\n";
			cout << "**************************************************\n\n";
		} else if (input == "UNION" && list1->GetLength() != 0 && list2->GetLength() != 0) {
			MakeUnion(list1, list2, unionList);
		} else if (input == "Q") {
			cout << "Goodbye...\n";
			break;
		}
		else {
			cout << "Unrecognized input - Try again.\n";
			cout << "*******************************\n";
		}
	} while (input != "Q");
	
	//Deallocating memory for each node in the lists.
	list1->MakeEmpty();
	list2->MakeEmpty();

	//Deallocating memory for lists themselves.
	delete list1, list2, unionList;

	return 0;
}

void ListOperationsMenu(UnsortedList* list)
{
	char selection;
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
		cout << "B - Back.\n\n";
		cout << "Enter your selection: ";
		cin >> selection;
		system("cls");
		ProcessListOperation(list, selection);
	} while (toupper(selection) != 'B');
}

void ProcessListOperation(UnsortedList* list, char selection)
{
	switch (toupper(selection)) {
	case '1': {
		ItemType item;
		int inputItem;
		cout << "Enter the information you would like to insert into the list: ";
		if (!(cin >> inputItem)) {
			ClientInputValidation(inputItem);
		}

		item.Set(inputItem);
		list->InsertItem(item);

		break;
	} case '2': {
		ItemType item;
		Node* returnValue; //Stores the returned node address from the search.
		int inputItem;
		cout << "Enter the item that you would like to search the list for: ";
		if (!(cin >> inputItem)) {
			ClientInputValidation(inputItem);
		}

		item.Set(inputItem);
		returnValue = list->Search(item); //Search method called (returns an address if found, null if not found)

		if (returnValue == NULL) {
			cout << inputItem << " was not found in the list\n\n";
		}
		else {
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

		list->DeleteItem(item, found);
		break;

	} case '4': {
		if (list->GetLength() == 0) { //If the list is empty the GetNextItem() method is not called.
			cout << "The list is currently empty.\n";
		}
		else {
			cout << "The next item in the list is: " << list->GetNextItem().Get() << endl;;
		}
		break;
	} case '5': {
		list->MakeEmpty();
		break;
	} case '6': {
		list->ResetList();
		break;
	} case '7': {
		cout << "The current length of the list is: " << list->GetLength() << endl;
		break;
	}  case 'B': {
		break;
	} default: {
		cout << "Unrecognized input - please try again.\n";
	} //default case bracket

	}//End of switch block bracket
}

void MakeUnion(UnsortedList* list1, UnsortedList* list2, UnsortedList *unionList)
{
	unionList = list1->Union(unionList, list1, list2);
	cout << "The unique elements of list1 and list2 have been combined to create a third union list.\n";
	cout << "The menu below allows you to perform list operations on this new list.\n";
	cout << "**********************************************************************\n";
	ListOperationsMenu(unionList);
	unionList->MakeEmpty(); //Deallocates memory from nodes of the unionList when user is done with it.
}

void ClientInputValidation(int& input) {
	while (!cin) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\aInput for this program should an integer - please try again: ";
		cin >> input;
	}
}

string ConvertToUpperCase(string& userInput) {

	for (int i = 0; i < userInput.length(); i++) {
		userInput[i] = toupper(userInput[i]);
	}

	return userInput;
}