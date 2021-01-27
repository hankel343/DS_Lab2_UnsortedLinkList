#include "UnsortedList.h"
#include "ItemType.h"
#include <iostream>

UnsortedList::UnsortedList() {
	length = 0; //New empty list so empty.
	//Both front and position are initialized to point nowhere.
	front = nullptr;
	currentPos = nullptr;
}

Node *UnsortedList::Search(ItemType inputItem) {
	//Allocating memory for a ptr to iterate over the list.
	Node* iterator = front;

	while (iterator != NULL) {
		if (iterator->data.ComparedTo(inputItem) == EQUAL) {
			return iterator;
		} else {
			iterator = iterator->next;
		}
		
	}
	return NULL;
}

void UnsortedList::InsertItem(ItemType inputItem) {
	Node *temp = front;
	Node* tempTrailer = NULL;

	if (front == NULL) {
		temp = new Node;
		temp->data = inputItem;
		temp->next = NULL;

		front = temp;
	} else {

		//Moves the temporary pointer to the end of the list.
		while (temp != NULL) {
			tempTrailer = temp;
			temp = temp->next;
		}

		//Allocates mem. for new node at end of the list
		temp = new Node;
		temp->data = inputItem;
		temp->next = NULL;

		//Creating link between previous last node and newly inserted last node.
		tempTrailer->next = temp;
	}

	length++;
	currentPos = temp;
}

void UnsortedList::DeleteItem(ItemType item, bool& found) {
	Node *temp = front;
	Node *tempTrailer = NULL;
	found = false;

	if (front == NULL) {
		std::cout << "The list is currently empty, so you cannot delete anything from it.\n\n";
		return;
	}

	if (temp->data.ComparedTo(item) == EQUAL) { //if node to delete is at the front of the list
		found = true;
		if (front->next != NULL) {
			tempTrailer = front->next;
			front = tempTrailer;
			delete temp;
		} else {
			delete temp;
			front = NULL;
		}
		
	} else {
		while (temp != NULL && !found) {
			if (temp->data.ComparedTo(item) == EQUAL) {
				found = true;
				//Rearranging pointers for deallocation of node.
				tempTrailer->next = temp->next; //Preserving link to subsequent nodes after deleted node.
				if (tempTrailer->next == NULL) { //Reassigning currentPos if deleted node is the last node in the list.
					currentPos = tempTrailer;
				}
				delete temp;
			}
			else {
				//Advancing iterator pointers if deleted node not found.
				tempTrailer = temp;
				temp = temp->next;
			}
		}
	}

	if (found) {
		std::cout << "Item successfully deleted from the list.\n\n";
		length--;
	} else {
		std::cout << "Requested item not found in the list.\n\n";
	}
}

void UnsortedList::GetNextItem() {
	if (front == NULL) { //if the list is empty.
		std::cout << "\nThe list is currently empty.\n";
		return;
	}
	else if (currentPos->next == NULL) { //currentPos will cycle to front of list if it reaches the end
		currentPos = front;
		std::cout << currentPos->data.Get() << std::endl;
	} else {
		currentPos = currentPos->next;
		std::cout << currentPos->data.Get() << std::endl;
	}
}

void UnsortedList::MakeEmpty() {
	Node *temp = front;
	Node *tempTrailer = NULL;

	//While loop deallocates memory from each node in the list.
	while (temp != NULL) {
		tempTrailer = temp;
		temp = temp->next;
		delete tempTrailer;
	}
}

bool UnsortedList::IsFull() {
	if (length >= MAX_ITEMS) {
		return true;
	} else {
		return false;
	}
}

void UnsortedList::ResetList() {
	currentPos = front;
}

int UnsortedList::GetLength() {
	return length;
}

void UnsortedList::Union(UnsortedList list1, UnsortedList list2) {



}

void UnsortedList::PrintList() {
	Node *temp = front;

	if (temp == NULL) {
		std::cout << "List is empty.\n";
	} else {
		while (temp != NULL) {
			std::cout << temp->data.Get() << " ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}
}

