#include <iostream>
#include <memory>

struct Node {
	int data;
	std::shared_ptr<Node> next;
};

struct _cabezalListaOrdInt {
	std::shared_ptr<Node> head;
	int length;
};

using ListaOrdInt = _cabezalListaOrdInt;

void insertElementRec(std::shared_ptr<Node>& currentNode, int value) {
	if (!currentNode || value <= currentNode->data) {
		auto newNode = std::make_shared<Node>();
		newNode->data = value;
		newNode->next = currentNode;
		currentNode = newNode;
	}
	else {
		insertElementRec(currentNode->next, value);
	}
}

void removeMaxElementRec(std::shared_ptr<Node>& currentNode) {
	if (currentNode && currentNode->next) {
		if (currentNode->next->next) {
			removeMaxElementRec(currentNode->next);
		}
		else {
			currentNode->next.reset();
		}
	}
}

void removeElementRec(std::shared_ptr<Node>& currentNode, int value) {
	if (currentNode) {
		if (currentNode->data == value) {
			currentNode = currentNode->next;
		}
		else {
			removeElementRec(currentNode->next, value);
		}
	}
}

void clearListRec(std::shared_ptr<Node>& currentNode) {
	if (currentNode) {
		clearListRec(currentNode->next);
		currentNode.reset();
	}
}

std::shared_ptr<Node> cloneListRec(const std::shared_ptr<Node>& currentNode) {
	if (!currentNode) {
		return nullptr;
	}
	auto newNode = std::make_shared<Node>();
	newNode->data = currentNode->data;
	newNode->next = cloneListRec(currentNode->next);
	return newNode;
}

bool elementExistsRec(const std::shared_ptr<Node>& currentNode, int value) {
	if (!currentNode) {
		return false;
	}
	if (currentNode->data == value) {
		return true;
	}
	return elementExistsRec(currentNode->next, value);
}

ListaOrdInt createList() {
	ListaOrdInt list;
	list.head = nullptr;
	list.length = 0;
	return list;
}

void addElement(ListaOrdInt& list, int value) {
	insertElementRec(list.head, value);
	list.length++;
}

void removeMinElement(ListaOrdInt& list) {
	if (list.head) {
		list.head = list.head->next;
		list.length--;
	}
}

void removeMaxElement(ListaOrdInt& list) {
	removeMaxElementRec(list.head);
	list.length--;
}

void removeElement(ListaOrdInt& list, int value) {
	removeElementRec(list.head, value);
	list.length--;
}

int getMinElement(const ListaOrdInt& list) {
	if (list.head) {
		return list.head->data;
	}
	throw std::runtime_error("List is empty.");
}

int getMaxElement(const ListaOrdInt& list) {
	if (!list.head) {
		throw std::runtime_error("List is empty.");
	}
	auto currentNode = list.head;
	while (currentNode->next) {
		currentNode = currentNode->next;
	}
	return currentNode->data;
}

bool elementExists(const ListaOrdInt& list, int value) {
	return elementExistsRec(list.head, value);
}

bool isEmpty(const ListaOrdInt& list) {
	return list.length == 0;
}

int getElementCount(const ListaOrdInt& list) {
	return list.length;
}

ListaOrdInt cloneList(const ListaOrdInt& sourceList) {
	ListaOrdInt newList;
	newList.head = cloneListRec(sourceList.head);
	newList.length = sourceList.length;
	return newList;
}

void destroyList(ListaOrdInt& list) {
	clearListRec(list.head);
	list.length = 0;
}

int main() {
	ListaOrdInt list = createList();
	addElement(list, 5);
	addElement(list, 1);
	addElement(list, 9);
	addElement(list, 3);
	std::cout << "Min element: " << getMinElement(list) << std::endl;
	std::cout << "Max element: " << getMaxElement(list) << std::endl;

	ListaOrdInt clonedList = cloneList(list);
	removeMinElement(clonedList);
	removeMaxElement(clonedList);

	std::cout << "Cloned list after removing min and max elements:" << std::endl;
	for (int i = 0; i < clonedList.length; i++) {
		std::cout << getMinElement(clonedList) << " ";
		removeMinElement(clonedList);
	}
	std::cout << std::endl;

	destroyList(list);
	destroyList(clonedList);

	return 0;
}
