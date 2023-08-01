#include <iostream>
#include <vector>
#include <cmath>

struct ListNode {
	int value;
	ListNode* next;
	ListNode(int value) : value(value), next(nullptr) {}
};

struct DiccionarioInt {
	std::vector<ListNode*> hashTable;
	int size;
	int capacity;

	DiccionarioInt(int capacity) : size(0), capacity(capacity) {
		hashTable.resize(capacity, nullptr);
	}
};

int hashFunction(int value, int capacity) {
	return std::abs(value) % capacity;
}

bool removeFromList(ListNode*& head, int value) {
	ListNode* prev = nullptr;
	ListNode* curr = head;

	while (curr != nullptr) {
		if (curr->value == value) {
			if (prev == nullptr) {
				head = curr->next;
			}
			else {
				prev->next = curr->next;
			}
			delete curr;
			return true;
		}
		prev = curr;
		curr = curr->next;
	}
	return false;
}

void addElement(DiccionarioInt& dict, int value) {
	int index = hashFunction(value, dict.capacity);
	ListNode* newNode = new ListNode(value);
	newNode->next = dict.hashTable[index];
	dict.hashTable[index] = newNode;
	dict.size++;
}

bool removeElement(DiccionarioInt& dict, int value) {
	int index = hashFunction(value, dict.capacity);
	if (removeFromList(dict.hashTable[index], value)) {
		dict.size--;
		return true;
	}
	return false;
}

bool belongsToDict(const DiccionarioInt& dict, int value) {
	int index = hashFunction(value, dict.capacity);
	ListNode* curr = dict.hashTable[index];

	while (curr != nullptr) {
		if (curr->value == value) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

int getElement(const DiccionarioInt& dict, int value) {
	if (belongsToDict(dict, value)) {
		return value;
	}
	return -1;
}

bool isEmpty(const DiccionarioInt& dict) {
	return dict.size == 0;
}

int getSize(const DiccionarioInt& dict) {
	return dict.size;
}

DiccionarioInt cloneDict(const DiccionarioInt& dict) {
	DiccionarioInt newDict(dict.capacity);
	for (int i = 0; i < dict.capacity; i++) {
		ListNode* curr = dict.hashTable[i];
		while (curr != nullptr) {
			addElement(newDict, curr->value);
			curr = curr->next;
		}
	}
	return newDict;
}

void destroyDict(DiccionarioInt& dict) {
	for (int i = 0; i < dict.capacity; i++) {
		ListNode* curr = dict.hashTable[i];
		while (curr != nullptr) {
			ListNode* temp = curr;
			curr = curr->next;
			delete temp;
		}
	}
	dict.hashTable.clear();
	dict.size = 0;
}

int main() {
	DiccionarioInt dict(10);

	addElement(dict, 5);
	addElement(dict, 15);
	addElement(dict, 25);

	std::cout << "Size: " << getSize(dict) << std::endl;
	std::cout << "Element 15: " << getElement(dict, 15) << std::endl;
	std::cout << "Remove 15: " << removeElement(dict, 15) << std::endl;
	std::cout << "Element 15: " << getElement(dict, 15) << std::endl;
	std::cout << "Size: " << getSize(dict) << std::endl;
	DiccionarioInt clonedDict = cloneDict(dict);
	std::cout << "Cloned Size: " << getSize(clonedDict) << std::endl;

	destroyDict(dict);
	std::cout << "Size after destroy: " << getSize(dict) << std::endl;

	return 0;
}
