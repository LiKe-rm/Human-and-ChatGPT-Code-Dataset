#include <iostream>
#include <cstring>

class HashTable {
private:
	struct HashNode {
		int key;
		const char* value;
		HashNode* next;

		HashNode(int k, const char* v, HashNode* n) : key(k), value(v), next(n) {}
	};

	HashNode** table;
	int capacity;
	int size;

	int hash(int key) const {
		return key % capacity;
	}

public:
	HashTable(int expectedSize) : capacity(expectedSize), size(0) {
		table = new HashNode * [capacity];
		for (int i = 0; i < capacity; ++i) {
			table[i] = nullptr;
		}
	}

	~HashTable() {
		for (int i = 0; i < capacity; ++i) {
			HashNode* node = table[i];
			while (node) {
				HashNode* temp = node;
				node = node->next;
				delete temp;
			}
		}
		delete[] table;
	}

	void put(int key, const char* value) {
		int index = hash(key);
		HashNode* node = table[index];
		while (node) {
			if (node->key == key) {
				node->value = value;
				return;
			}
			node = node->next;
		}
		table[index] = new HashNode(key, value, table[index]);
		++size;
	}

	bool contains(int key) const {
		int index = hash(key);
		HashNode* node = table[index];
		while (node) {
			if (node->key == key) {
				return true;
			}
			node = node->next;
		}
		return false;
	}

	const char* get(int key) const {
		int index = hash(key);
		HashNode* node = table[index];
		while (node) {
			if (node->key == key) {
				return node->value;
			}
			node = node->next;
		}
		return "";
	}

	void remove(int key) {
		int index = hash(key);
		HashNode*& head = table[index];
		HashNode* prev = nullptr;
		HashNode* node = head;
		while (node) {
			if (node->key == key) {
				if (prev) {
					prev->next = node->next;
				}
				else {
					head = node->next;
				}
				delete node;
				--size;
				return;
			}
			prev = node;
			node = node->next;
		}
	}

	int randomKey() const {
		if (isEmpty()) {
			return -1;
		}
		int index;
		do {
			index = rand() % capacity;
		} while (!table[index]);
		return table[index]->key;
	}

	bool isEmpty() const {
		return size == 0;
	}

	int getSize() const {
		return size;
	}

	HashTable* clone() const {
		HashTable* newHashTable = new HashTable(capacity);
		for (int i = 0; i < capacity; ++i) {
			HashNode* node = table[i];
			while (node) {
				newHashTable->put(node->key, node->value);
				node = node->next;
			}
		}
		return newHashTable;
	}
};

int main() {
	HashTable ht(10);
	ht.put(1, "one");
	ht.put(2, "two");
	ht.put(3, "three");

	std::cout << "Size: " << ht.getSize() << std::endl;
	std::cout << "Contains key 1: " << ht.contains(1) << std::endl;
	std::cout << "Value of key 1: " << ht.get(1) << std::endl;
	ht.remove(2);
	std::cout << "Size after removing key 2: " << ht.getSize() << std::endl;
	std::cout << "Contains key 2: " << ht.contains(2) << std::endl;

	int randomKey = ht.randomKey();
	std::cout << "Random key: " << randomKey << std::endl;

	std::cout << "Is empty: " << ht.isEmpty() << std::endl;

	HashTable* clonedHt = ht.clone();
	std::cout << "Cloned hash table size: " << clonedHt->getSize() << std::endl;
	std::cout << "Cloned hash table value of key 1: " << clonedHt->get(1) << std::endl;

	delete clonedHt;
	return 0;
}
