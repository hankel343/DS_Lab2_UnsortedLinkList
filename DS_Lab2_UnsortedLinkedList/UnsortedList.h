#ifndef UNSORTEDLIST_H
#define UNSORTEDLIST_H
#include "ItemType.h"

struct Node {
	ItemType data;
	Node* next;
};

class UnsortedList {
public:
	UnsortedList();

	Node *Search(ItemType item);
	//Pre: Given an item to search for and object has been created
	//Post: A pointer to the location of the searched for item is returned
	//or NULL if not found.

	void InsertItem(ItemType item);
	//Pre: Given an item to search for and the object exists.
	//Post: The item passed as an argument is added to the list.

	void DeleteItem(ItemType item, bool& found);
	//Pre: Given an item to search for and delete and the object exists.
	//Post: The item passed as an argument is deleted from the list.
	//If not found, the item passed into the function is returned.

	ItemType GetNextItem();
	//Pre: Object exists
	//Post: The next item in the unsorted list is returned from the function.

	void MakeEmpty();
	//Pre: Object exists
	//Post: The unsorted list type is reset to be empty.

	bool IsFull();
	//Pre: Object exists.
	//Post: A boolean value is returned to represent if the list is full or not

	void ResetList();
	//Pre: Object exists
	//Post: Position pointer is returned to the front of the list

	int GetLength();
	//Pre: Object exists
	//Post: Length of the unsorted list is returned.

	void Union(UnsortedList list1, UnsortedList list2);
	//Pre: Two unsorted list objects exist.
	//Post: The mathematical operation union is performed on the two lists -
	//as if they were two sets. (All elements, if repeated elements, do not include)

	void PrintList();
	//Pre: List object exists.
	//Post: The list is printed to the console.

private:
	int length;
	Node* front; //Head ptr that contains mem. address of front of list
	Node* currentPos; //Traveling ptr that iterates over the unsorted list.
};


#endif UNSORTEDLIST_H