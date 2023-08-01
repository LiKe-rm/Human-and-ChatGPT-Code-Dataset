#include <iostream>
#include <memory>

class NodoABIntDobleDato {
public:
	int dato1;
	int dato2;
	std::shared_ptr<NodoABIntDobleDato> left;
	std::shared_ptr<NodoABIntDobleDato> right;

	NodoABIntDobleDato(int d1) : dato1(d1), dato2(1), left(nullptr), right(nullptr) {}
};

class ListaOrdInt {
private:
	std::shared_ptr<NodoABIntDobleDato> root;

	std::shared_ptr<NodoABIntDobleDato> insertHelper(std::shared_ptr<NodoABIntDobleDato> node, int val) {
		if (!node) {
			return std::make_shared<NodoABIntDobleDato>(val);
		}

		if (val == node->dato1) {
			node->dato2++;
		}
		else if (val < node->dato1) {
			node->left = insertHelper(node->left, val);
		}
		else {
			node->right = insertHelper(node->right, val);
		}

		return node;
	}

	std::shared_ptr<NodoABIntDobleDato> findMin(std::shared_ptr<NodoABIntDobleDato> node) {
		while (node->left) {
			node = node->left;
		}
		return node;
	}

	std::shared_ptr<NodoABIntDobleDato> removeMin(std::shared_ptr<NodoABIntDobleDato> node) {
		if (!node->left) {
			return node->right;
		}
		node->left = removeMin(node->left);
		return node;
	}

	std::shared_ptr<NodoABIntDobleDato> removeMax(std::shared_ptr<NodoABIntDobleDato> node) {
		if (!node->right) {
			return node->left;
		}
		node->right = removeMax(node->right);
		return node;
	}

	std::shared_ptr<NodoABIntDobleDato> removeHelper(std::shared_ptr<NodoABIntDobleDato> node, int val) {
		if (!node) {
			return node;
		}

		if (val < node->dato1) {
			node->left = removeHelper(node->left, val);
		}
		else if (val > node->dato1) {
			node->right = removeHelper(node->right, val);
		}
		else {
			if (node->dato2 > 1) {
				node->dato2--;
			}
			else {
				if (!node->left) {
					return node->right;
				}
				else if (!node->right) {
					return node->left;
				}
				else {
					std::shared_ptr<NodoABIntDobleDato> minRight = findMin(node->right);
					node->dato1 = minRight->dato1;
					node->dato2 = minRight->dato2;
					node->right = removeMin(node->right);
				}
			}
		}
		return node;
	}

	bool containsHelper(std::shared_ptr<NodoABIntDobleDato> node, int val) {
		if (!node) {
			return false;
		}

		if (val == node->dato1) {
			return true;
		}
		else if (val < node->dato1) {
			return containsHelper(node->left, val);
		}
		else {
			return containsHelper(node->right, val);
		}
	}

	int sizeHelper(std::shared_ptr<NodoABIntDobleDato> node) {
		if (!node) {
			return 0;
		}
		return node->dato2 + sizeHelper(node->left) + sizeHelper(node->right);
	}

	std::shared_ptr<NodoABIntDobleDato> cloneHelper(std::shared_ptr<NodoABIntDobleDato> node) {
		if (!node) {
			return nullptr;
		}

		std::shared_ptr<NodoABIntDobleDato> newNode = std::make_shared<NodoABIntDobleDato>(node->dato1);
		newNode->dato2 = node->dato2;
		newNode->left = cloneHelper(node->left);
		newNode->right = cloneHelper(node->right);
		return newNode;
	}

	void destroyHelper(std::shared_ptr<NodoABIntDobleDato>& node) {
		if (!node) {
			return;
		}
		destroyHelper(node->left);
		destroyHelper(node->right);
		node.reset();
	}
public:
	ListaOrdInt() : root(nullptr) {}
	void insert(int val) {
		root = insertHelper(root, val);
	}

	void removeMin() {
		if (root) {
			root = removeMin(root);
		}
	}

	void removeMax() {
		if (root) {
			root = removeMax(root);
		}
	}

	void remove(int val) {
		root = removeHelper(root, val);
	}

	int getMin() {
		if (!root) {
			return -1;
		}

		return findMin(root)->dato1;
	}

	int getMax() {
		if (!root) {
			return -1;
		}

		std::shared_ptr<NodoABIntDobleDato> node = root;
		while (node->right) {
			node = node->right;
		}
		return node->dato1;
	}

	bool contains(int val) {
		return containsHelper(root, val);
	}

	bool isEmpty() {
		return !root;
	}

	int size() {
		return sizeHelper(root);
	}

	ListaOrdInt clone() {
		ListaOrdInt clonedList;
		clonedList.root = cloneHelper(root);
		return clonedList;
	}

	void destroy() {
		destroyHelper(root);
	}
};

int main() {
	ListaOrdInt list;
	list.insert(5);
	list.insert(3);
	list.insert(7);
	list.insert(3);
	std::cout << "Size: " << list.size() << std::endl;
	std::cout << "Min: " << list.getMin() << std::endl;
	std::cout << "Max: " << list.getMax() << std::endl;

	list.remove(3);
	std::cout << "After remove(3), Size: " << list.size() << std::endl;
	std::cout << "After remove(3), Min: " << list.getMin() << std::endl;

	list.removeMin();
	std::cout << "After removeMin, Size: " << list.size() << std::endl;
	std::cout << "After removeMin, Min: " << list.getMin() << std::endl;

	list.removeMax();
	std::cout << "After removeMax, Size: " << list.size() << std::endl;
	std::cout << "After removeMax, Max: " << list.getMax() << std::endl;

	list.destroy();
	std::cout << "After destroy, Size: " << list.size() << std::endl;

	return 0;
}
