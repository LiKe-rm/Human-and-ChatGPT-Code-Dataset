#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <stdexcept>

// 定义单向链表结构
struct NodoListaInt {
	int data;
	NodoListaInt* next;

	NodoListaInt(int data) : data(data), next(nullptr) {}
};

// 类定义
class FrameworkA1 {
public:
	// 构造函数
	FrameworkA1() = default;

	// 将单向链表转换为有序整数列表
	std::list<int> toListaOrdInt(NodoListaInt* head);

	// 将单向链表转换为整数位置列表
	std::list<int> toListaPosInt(NodoListaInt* head);

	// 将单向链表转换为整数栈
	std::stack<int> toPilaInt(NodoListaInt* head);

	// 将单向链表转换为整数队列
	std::queue<int> toColaInt(NodoListaInt* head);

	// 将单向链表转换为整数多重集合
	std::multiset<int> toMultisetInt(NodoListaInt* head);

	// 将单向链表转换为整数集合
	std::set<int> toSetInt(NodoListaInt* head);

	// 将单向链表转换为整数字典
	std::unordered_map<int, int> toDiccionarioInt(NodoListaInt* head);

	// 将两个单向链表转换为整数-整数映射表
	std::map<int, int> toTablaIntInt(NodoListaInt* head1, NodoListaInt* head2);

	// 将两个单向链表转换为整数-字符串映射表
	std::map<int, std::string> toTablaIntString(NodoListaInt* head1, NodoListaInt* head2);

	// 将两个单向链表转换为整数优先级队列
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> toColaPrioridadInt(NodoListaInt* head1, NodoListaInt* head2);

private:
	// 辅助函数：从单向链表中提取数据到一个vector
	std::vector<int> extractDataFromList(NodoListaInt* head);
};

std::list<int> FrameworkA1::toListaOrdInt(NodoListaInt* head) {
	std::list<int> listaOrdInt;
	NodoListaInt* currentNode = head;
	while (currentNode != nullptr) {
		listaOrdInt.push_back(currentNode->data);
		currentNode = currentNode->next;
	}
	listaOrdInt.sort();
	return listaOrdInt;
}

std::list<int> FrameworkA1::toListaPosInt(NodoListaInt* head) {
	return toListaOrdInt(head); // 有序整数列表和整数位置列表是相同的
}

std::stack<int> FrameworkA1::toPilaInt(NodoListaInt* head) {
	std::stack<int> pilaInt;
	NodoListaInt* currentNode = head;
	while (currentNode != nullptr) {
		pilaInt.push(currentNode->data);
		currentNode = currentNode->next;
	}
	return pilaInt;
}

std::queue<int> FrameworkA1::toColaInt(NodoListaInt* head) {
	std::queue<int> colaInt;
	NodoListaInt* currentNode = head;
	while (currentNode != nullptr) {
		colaInt.push(currentNode->data);
		currentNode = currentNode->next;
	}
	return colaInt;
}

std::multiset<int> FrameworkA1::toMultisetInt(NodoListaInt* head) {
	std::multiset<int> multisetInt;
	NodoListaInt* currentNode = head;
	while (currentNode != nullptr) {
		multisetInt.insert(currentNode->data);
		currentNode = currentNode->next;
	}
	return multisetInt;
}

std::set<int> FrameworkA1::toSetInt(NodoListaInt* head) {
	std::set<int> setInt;
	NodoListaInt* currentNode = head;
	while (currentNode != nullptr) {
		setInt.insert(currentNode->data);
		currentNode = currentNode->next;
	}
	return setInt;
}

std::unordered_map<int, int> FrameworkA1::toDiccionarioInt(NodoListaInt* head) {
	std::unordered_map<int, int> diccionarioInt;
	NodoListaInt* currentNode = head;
	while (currentNode != nullptr) {
		diccionarioInt[currentNode->data] = currentNode->data;
		currentNode = currentNode->next;
	}
	return diccionarioInt;
}

std::map<int, int> FrameworkA1::toTablaIntInt(NodoListaInt* head1, NodoListaInt* head2) {
	std::map<int, int> tablaIntInt;
	NodoListaInt* currentNode1 = head1;
	NodoListaInt* currentNode2 = head2;
	while (currentNode1 != nullptr && currentNode2 != nullptr) {
		tablaIntInt[currentNode1->data] = currentNode2->data;
		currentNode1 = currentNode1->next;
		currentNode2 = currentNode2->next;
	}
	return tablaIntInt;
}

std::map<int, std::string> FrameworkA1::toTablaIntString(NodoListaInt* head1, NodoListaInt* head2) {
	std::map<int, std::string> tablaIntString;
	NodoListaInt* currentNode1 = head1;
	NodoListaInt* currentNode2 = head2;
	while (currentNode1 != nullptr && currentNode2 != nullptr) {
		tablaIntString[currentNode1->data] = std::to_string(currentNode2->data);
		currentNode1 = currentNode1->next;
		currentNode2 = currentNode2->next;
	}
	return tablaIntString;
}

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> FrameworkA1::toColaPrioridadInt(NodoListaInt* head1, NodoListaInt* head2) {
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> colaPrioridadInt;
	NodoListaInt* currentNode1 = head1;
	NodoListaInt* currentNode2 = head2;
	while (currentNode1 != nullptr && currentNode2 != nullptr) {
		colaPrioridadInt.emplace(currentNode1->data, currentNode2->data);
		currentNode1 = currentNode1->next;
		currentNode2 = currentNode2->next;
	}
	return colaPrioridadInt;
}

int main() {
	// 测试代码
	NodoListaInt* head = new NodoListaInt(5);
	head->next = new NodoListaInt(3);
	head->next->next = new NodoListaInt(8);
	head->next->next->next = new NodoListaInt(1);
	head->next->next->next->next = new NodoListaInt(4);
	FrameworkA1 framework;
	auto listaOrdInt = framework.toListaOrdInt(head);
	for (int value : listaOrdInt) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	auto pilaInt = framework.toPilaInt(head);
	while (!pilaInt.empty()) {
		std::cout << pilaInt.top() << " ";
		pilaInt.pop();
	}
	std::cout << std::endl;

	auto colaInt = framework.toColaInt(head);
	while (!colaInt.empty()) {
		std::cout << colaInt.front() << " ";
		colaInt.pop();
	}
	std::cout << std::endl;

	auto multisetInt = framework.toMultisetInt(head);
	for (int value : multisetInt) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	auto setInt = framework.toSetInt(head);
	for (int value : setInt) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	// 清理内存
	NodoListaInt* currentNode = head;
	while (currentNode != nullptr) {
		NodoListaInt* toDelete = currentNode;
		currentNode = currentNode->next;
		delete toDelete;
	}

	return 0;
}
