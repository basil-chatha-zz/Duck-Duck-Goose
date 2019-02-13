#include "circular_list_int.h"

// not sure if I even need a constructor here
CircularListInt::CircularListInt() {}

CircularListInt::~CircularListInt() {
	if(count == 0) return;
	Item *temp = head->prev;
	Item *prevPtr;
	while(temp != head) {
		prevPtr = temp->prev;
		delete temp;
		temp = prevPtr;
	} if(temp == head) delete temp;
}
CircularListInt::Item* CircularListInt::findItem(size_t index) const {
	int length = (int) size();

	CircularListInt::Item *returnPtr = nullptr;

	if(length == 0) return nullptr;

	Item *temp = head;
	int curIndex = 0;

	while(temp->next != head) {
		if(curIndex == ((int) index % length)) {
			returnPtr = temp;
		}
		temp = temp->next;
		curIndex++;
	}
	if(temp->next == head && (curIndex == ((int) index % length))) returnPtr = temp;
	return returnPtr;
}

int CircularListInt::get(size_t index) const {
	int length = (int) size();

	int returnVal = 0;

	if(length == 0) return 0;

	Item *temp = head;
	int curIndex = 0;

	while(temp->next != head) {
		if(curIndex == ((int) index % length)) {
			returnVal = temp->value;
		}
		temp = temp->next;
		curIndex++;
	}
	if(temp->next == head && (curIndex == ((int) index % length))) returnVal = temp->value;
	return returnVal;
}

size_t CircularListInt::size() const {
	return count;
}

bool CircularListInt::empty() const {
	int length = (int) size();
	if(length == 0) return true;
	return false;
}

void CircularListInt::push_back(int value) {
	Item *newItem = new Item(value);

	if(empty()) { // if first element being added
		newItem->next = newItem;
		newItem->prev = newItem;
		head = newItem;
	} else { // otherwise
		Item *lastElement = head->prev;
		newItem->next = head;
		newItem->prev = lastElement;
		lastElement->next = newItem;
		head->prev = newItem;
	}

	//increase the list's size by one
	count++;
}

void CircularListInt::set(size_t index, int value) {
	int length = (int) size();

	if(length == 0) return;

	Item *temp = head;
	int curIndex = 0;

	while(temp->next != head) {
		if(curIndex == ((int) index % length)) temp->value = value;
		temp = temp->next;
		curIndex++;
	}
	//need because otherwise it won't check the last element
	if(temp->next == head && (curIndex == ((int) index % length))) temp->value = value;
}

void CircularListInt::remove(size_t index) {
	int length = (int) size();

	if(length == 0) return;

	Item *temp = head;
	int curIndex = 0;
	while(temp->next != head) {
		if(curIndex == ((int) index % length)) {
			if(curIndex == 0) { //if we remove the head
				Item *nextPtr = temp->next;
				Item *prevPtr = temp->prev;
				delete temp;
				head = nextPtr;
				prevPtr->next = nextPtr;
				nextPtr->prev = prevPtr;
			} else { //if we don't remove the head
				Item *nextPtr = temp->next;
				Item *prevPtr = temp->prev;
				delete temp;
				prevPtr->next = nextPtr;
				nextPtr->prev = prevPtr;
			}
			count--;
			return;
		}
		temp = temp->next;
		curIndex++;
	}
	if(temp->next == head) {
		if(curIndex == 0) {
			delete head;
			head = nullptr;
			//will be the only element because otherwise it would'nt
			//have gotten to this point
		} else { //if last element
			Item *nextPtr = temp->next;
			Item *prevPtr = temp->prev;
			delete temp;
			prevPtr->next = nextPtr;
			nextPtr->prev = prevPtr;
		} count--;
	} return;
}