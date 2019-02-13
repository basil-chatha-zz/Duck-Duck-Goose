#include "selection_sort.h"
#include <iostream>

Item* findMin(Item *head) {
	if(head == nullptr) return nullptr;
	//return null only if the linkedlist is empty

	int curMin = head->getValue();
	Item *curMinPtr = head;

	Item *temp = head;

	while(temp->next != nullptr) {
		//std::cout << "first: " << temp->getValue() << " third: " << temp->next->getValue() << std::endl;
		int curVal = temp->getValue();

		if(curVal < curMin) {
			curMin = curVal;
			curMinPtr = temp;
		}

		temp = temp->next;
	}

	//the below if is used because the above while loop will
	//not check the last item since the conditional will evaluate
	//to false when we get to it
	if(temp->next == nullptr) {
		int curVal = temp->getValue();

		if(curVal < curMin) {
			curMinPtr = temp;
		}
	}

	return curMinPtr;
	//if multiple min values, return the first one
}

Item* LLSelectionSort(Item *head) {
	if(head == nullptr) return nullptr;
	//return NULL only if head is the nullptr

	Item *comparePtr = head;
	Item *newPtr;
	Item *newHead = head;

	int count = 0;

	while(comparePtr->next != nullptr) {
		newPtr = findMin(comparePtr);
		
		Item *newNext = newPtr->next;
		Item *newPrev = newPtr->prev;
		Item *compareNext = comparePtr->next;
		Item *comparePrev = comparePtr->prev;
		
		comparePtr->next = newNext;

		comparePtr->prev = newPtr != compareNext ? newPrev : newPtr;


		newPtr->next = newPtr != compareNext ? compareNext : comparePtr;

		newPtr->prev = comparePrev;

		if(newNext != nullptr) newNext->prev = comparePtr;
		if(newPrev != nullptr && newPtr != compareNext) newPrev->next = comparePtr;

		if(comparePrev != nullptr) comparePrev->next = newPtr;
		if(compareNext != nullptr && newPtr != compareNext) compareNext->prev = newPtr;

		if(count == 0) newHead = newPtr;
		count++;

		//go to next pointer
		comparePtr = comparePtr != newPtr ? newPtr->next : comparePtr->next;
	}
	return newHead;
}