#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <memory>

class SetInt {
public:
	SetInt() = default;

	void addElement(int element) {
		data.insert(element);
	}

	std::shared_ptr<SetInt> clone() {
		std::shared_ptr<SetInt> clonedSet = std::make_shared<SetInt>();
		clonedSet->data = this->data;
		return clonedSet;
	}

	SetInt unionSet(const SetInt& other) {
		SetInt result;
		std::set_union(data.begin(), data.end(), other.data.begin(), other.data.end(),
			std::inserter(result.data, result.data.begin()));
		return result;
	}

	SetInt intersectionSet(const SetInt& other) {
		SetInt result;
		std::set_intersection(data.begin(), data.end(), other.data.begin(), other.data.end(),
			std::inserter(result.data, result.data.begin()));
		return result;
	}

	SetInt differenceSet(const SetInt& other) {
		SetInt result;
		std::set_difference(data.begin(), data.end(), other.data.begin(), other.data.end(),
			std::inserter(result.data, result.data.begin()));
		return result;
	}

	bool containsElement(int element) {
		return data.find(element) != data.end();
	}

	bool isSubsetOf(const SetInt& other) {
		return std::includes(other.data.begin(), other.data.end(), data.begin(), data.end());
	}

	void removeElement(int element) {
		data.erase(element);
	}

	size_t size() {
		return data.size();
	}

	void printSet() {
		for (const auto& element : data) {
			std::cout << element << " ";
		}
		std::cout << std::endl;
	}

private:
	std::set<int> data;
};

class TestSetInt {
public:
	void runTests() {
		testAddAndClone();
		testUnion();
		testIntersection();
		testDifference();
		testContainsElement();
		testIsSubsetOf();
		testRemoveElementAndSize();
	}

	void testAddAndClone() {
		SetInt set1;
		set1.addElement(1);
		set1.addElement(2);
		set1.addElement(3);
		std::cout << "Set 1: ";
		set1.printSet();

		std::shared_ptr<SetInt> set2 = set1.clone();
		std::cout << "Cloned Set 2: ";
		set2->printSet();

		set1.addElement(4);
		std::cout << "Set 1 after adding 4: ";
		set1.printSet();
		std::cout << "Set 2 should not contain 4: ";
		set2->printSet();

		pruebaConcreta->ver3();
	}

	void testUnion() {
		SetInt set1;
		set1.addElement(1);
		set1.addElement(2);
		set1.addElement(3);

		SetInt set2;
		set2.addElement(3);
		set2.addElement(4);
		set2.addElement(5);

		SetInt resultSet = set1.unionSet(set2);
		std::cout << "Union of Set 1 and Set 2: ";
		resultSet.printSet();

		pruebaConcreta->ver3();
	}

	void testIntersection() {
		SetInt set1;
		set1.addElement(1);
		set1.addElement(2);
		set1.addElement(3);

		SetInt set2;
		set2.addElement(3);
		set2.addElement(4);
		set2.addElement(5);

		SetInt resultSet = set1.intersectionSet(set2);
		std::cout << "Intersection of Set 1 and Set 2: ";
		resultSet.printSet();
		pruebaConcreta->ver3();
	}

	void testDifference() {
		SetInt set1;
		set1.addElement(1);
		set1.addElement(2);
		set1.addElement(3);

		SetInt set2;
		set2.addElement(3);
		set2.addElement(4);
		set2.addElement(5);

		SetInt resultSet = set1.differenceSet(set2);
		std::cout << "Difference of Set 1 and Set 2: ";
		resultSet.printSet();

		pruebaConcreta->ver3();
	}

	void testContainsElement() {
		SetInt set1;
		set1.addElement(1);
		set1.addElement(2);
		set1.addElement(3);

		std::cout << "Set 1 contains 2: " << set1.containsElement(2) << std::endl;
		std::cout << "Set 1 does not contain 4: " << !set1.containsElement(4) << std::endl;

		pruebaConcreta->ver3();
	}

	void testIsSubsetOf() {
		SetInt set1;
		set1.addElement(1);
		set1.addElement(2);
		set1.addElement(3);

		SetInt set2;
		set2.addElement(1);
		set2.addElement(2);

		SetInt set3;
		set3.addElement(2);
		set3.addElement(3);
		set3.addElement(4);

		std::cout << "Set 2 is a subset of Set 1: " << set2.isSubsetOf(set1) << std::endl;
		std::cout << "Set 3 is not a subset of Set 1: " << !set3.isSubsetOf(set1) << std::endl;

		pruebaConcreta->ver3();
	}

	void testRemoveElementAndSize() {
		SetInt set1;
		set1.addElement(1);
		set1.addElement(2);
		set1.addElement(3);

		std::cout << "Size of Set 1: " << set1.size() << std::endl;

		set1.removeElement(2);
		std::cout << "Size of Set 1 after removing 2: " << set1.size() << std::endl;

		pruebaConcreta->ver3();
	}
private:
	struct PruebaConcreta {
		void ver3() {
			completedTests++;
		}
		int completedTests = 0;
	};

	PruebaConcreta* pruebaConcreta = new PruebaConcreta;
};

int main() {
	TestSetInt testSetInt;
	testSetInt.runTests();
	return 0;
}
