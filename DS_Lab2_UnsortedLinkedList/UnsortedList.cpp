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
			currentPos = tempTrailer = front->next; //moves both currentPos and tempTrailer to the address of front's next node.
			front = tempTrailer;
			delete temp;
		} else {
			delete temp;
			front = NULL;
			currentPos = NULL;
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
		std::cout << "The list is currently empty.\n";
		return;
	}
	else if (currentPos->next == NULL) { //currentPos will cycle to front of list if it reaches the end
		currentPos = front;
	} else {
		currentPos = currentPos->next;
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

	front = NULL;
	currentPos = NULL;
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

UnsortedList UnsortedList::Union(UnsortedList list1, UnsortedList list2) {

	UnsortedList unionList;
	Node *temp1 = list1.front, *temp2 = list2.front; //These are iterators for list 1, 2, and unionList respectively.
	bool match;

	//Runner iterators scan ahead through the list to find duplicates.
	Node* temp1Runner = temp1->next;
	while (temp1 != NULL) {
		match = false;
		temp1Runner = temp1->next;
		while (temp1Runner != NULL) {
			if (temp1->data.ComparedTo(temp1Runner->data) == EQUAL) {
				match = true;
			}
			temp1Runner = temp1Runner->next;
		}

		if (match == false) { //adds unique elements from list1 to the unionList.
			unionList.InsertItem(temp1->data);
		}
		
		temp1 = temp1->next;
	}

	Node* temp3 = unionList.front;
	while (temp2 != NULL) {
		match = false;
		temp3 = unionList.front;
		while (temp3 != NULL) {
			if (temp2->data.ComparedTo(temp3->data)) {
				match = true;
			}

			if (match == true) {
				break;
			} else {
				temp3 = temp3->next;
			}
			
		}

		if (match == false) {
			unionList.InsertItem(temp2->data);
		}

		temp2 = temp2->next;
	}
	
	return unionList;
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

Node *UnsortedList::GetCurrentPos() {
	if (currentPos != NULL) {
		return currentPos;
	} else {
		return NULL;
	}
}