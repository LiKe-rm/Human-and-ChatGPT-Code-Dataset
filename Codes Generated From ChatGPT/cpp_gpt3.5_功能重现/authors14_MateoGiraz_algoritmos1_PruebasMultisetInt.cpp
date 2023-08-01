#include <iostream>
#include <map>
#include <algorithm>

class MultisetInt {
private:
	std::map<int, int> elements;

public:
	// 添加元素
	void add(int element) {
		elements[element]++;
	}

	// 克隆多重集合
	MultisetInt clone() const {
		return *this;
	}

	// 多重集合的并集
	MultisetInt unionSet(const MultisetInt& other) const {
		MultisetInt result;
		for (const auto& e : elements) {
			result.elements[e.first] = std::max(e.second, other.elements.at(e.first));
		}
		return result;
	}

	// 多重集合的交集
	MultisetInt intersection(const MultisetInt& other) const {
		MultisetInt result;
		for (const auto& e : elements) {
			if (other.elements.count(e.first)) {
				result.elements[e.first] = std::min(e.second, other.elements.at(e.first));
			}
		}
		return result;
	}

	// 多重集合的差集
	MultisetInt difference(const MultisetInt& other) const {
		MultisetInt result;
		for (const auto& e : elements) {
			if (!other.elements.count(e.first)) {
				result.elements[e.first] = e.second;
			}
			else {
				int diff = e.second - other.elements.at(e.first);
				if (diff > 0) {
					result.elements[e.first] = diff;
				}
			}
		}
		return result;
	}

	// 判断一个元素是否属于多重集合
	bool contains(int element) const {
		return elements.count(element) > 0;
	}

	// 判断一个多重集合是否是另一个多重集合的子集
	bool isSubset(const MultisetInt& other) const {
		for (const auto& e : elements) {
			if (!other.elements.count(e.first) || other.elements.at(e.first) < e.second) {
				return false;
			}
		}
		return true;
	}

	// 判断多重集合是否为空
	bool isEmpty() const {
		return elements.empty();
	}

	// 计算多重集合中元素的数量
	int size() const {
		int count = 0;
		for (const auto& e : elements) {
			count += e.second;
		}
		return count;
	}

	// 删除多重集合中的元素
	void remove(int element) {
		if (elements.count(element)) {
			elements[element]--;
			if (elements[element] == 0) {
				elements.erase(element);
			}
		}
	}

	// 销毁多重集合，释放内存
	void clear() {
		elements.clear();
	}
};

class PruebaConcreta {
public:
	int testsPassed = 0;
};

void pruebasMultisetIntNoAcotada(PruebaConcreta& pruebaConcreta) {
	MultisetInt multiset;

	// 测试添加元素和计算多重集合中元素的数量
	multiset.add(1);
	multiset.add(1);
	multiset.add(2);
	multiset.add(3);
	multiset.add(3);
	multiset.add(3);

	if (multiset.size() == 6) {
		pruebaConcreta.testsPassed++;
		std::cout << "测试添加元素和计算多重集合中元素的数量成功!" << std::endl;
	}
	else {
		std::cout << "测试添加元素和计算多重集合中元素的数量失败!" << std::endl;
	}
	// 测试克隆多重集合
	MultisetInt clonedMultiset = multiset.clone();
	if (clonedMultiset.size() == 6 && clonedMultiset.contains(1) && clonedMultiset.contains(3)) {
		pruebaConcreta.testsPassed++;
		std::cout << "测试克隆多重集合成功!" << std::endl;
	}
	else {
		std::cout << "测试克隆多重集合失败!" << std::endl;
	}

	// 测试并集
	MultisetInt multiset2;
	multiset2.add(1);
	multiset2.add(1);
	multiset2.add(2);
	multiset2.add(4);

	MultisetInt unionSet = multiset.unionSet(multiset2);
	if (unionSet.size() == 8 && unionSet.contains(1) && unionSet.contains(4)) {
		pruebaConcreta.testsPassed++;
		std::cout << "测试多重集合的并集成功!" << std::endl;
	}
	else {
		std::cout << "测试多重集合的并集失败!" << std::endl;
	}

	// 测试交集
	MultisetInt intersectionSet = multiset.intersection(multiset2);
	if (intersectionSet.size() == 2 && intersectionSet.contains(1) && intersectionSet.contains(2)) {
		pruebaConcreta.testsPassed++;
		std::cout << "测试多重集合的交集成功!" << std::endl;
	}
	else {
		std::cout << "测试多重集合的交集失败!" << std::endl;
	}

	// 测试差集
	MultisetInt differenceSet = multiset.difference(multiset2);
	if (differenceSet.size() == 4 && differenceSet.contains(3) && !differenceSet.contains(4)) {
		pruebaConcreta.testsPassed++;
		std::cout << "测试多重集合的差集成功!" << std::endl;
	}
	else {
		std::cout << "测试多重集合的差集失败!" << std::endl;
	}

	// 测试判断一个多重集合是否是另一个多重集合的子集
	if (intersectionSet.isSubset(multiset) && !multiset.isSubset(multiset2)) {
		pruebaConcreta.testsPassed++;
		std::cout << "测试判断一个多重集合是否是另一个多重集合的子集成功!" << std::endl;
	}
	else {
		std::cout << "测试判断一个多重集合是否是另一个多重集合的子集失败!" << std::endl;
	}

	// 测试判断多重集合是否为空
	MultisetInt emptySet;
	if (!multiset.isEmpty() && emptySet.isEmpty()) {
		pruebaConcreta.testsPassed++;
		std::cout << "测试判断多重集合是否为空成功!" << std::endl;
	}
	else {
		std::cout << "测试判断多重集合是否为空失败!" << std::endl;
	}

	// 测试删除多重集合中的元素
	multiset.remove(1);
	multiset.remove(3);
	if (multiset.size() == 4 && !multiset.contains(1) && multiset.contains(2) && !multiset.contains(3)) {
		pruebaConcreta.testsPassed++;
		std::cout << "测试删除多重集合中的元素成功!" << std::endl;
	}
	else {
		std::cout << "测试删除多重集合中的元素失败!" << std::endl;
	}
	// 测试销毁多重集合，释放内存
	multiset.clear();
	if (multiset.isEmpty()) {
		pruebaConcreta.testsPassed++;
		std::cout << "测试销毁多重集合，释放内存成功!" << std::endl;
	}
	else {
		std::cout << "测试销毁多重集合，释放内存失败!" << std::endl;
	}
}

int main() {
	PruebaConcreta pruebaConcreta;
	pruebasMultisetIntNoAcotada(pruebaConcreta);
	std::cout << "共通过 " << pruebaConcreta.testsPassed << " 个测试" << std::endl;
	return 0;
}

