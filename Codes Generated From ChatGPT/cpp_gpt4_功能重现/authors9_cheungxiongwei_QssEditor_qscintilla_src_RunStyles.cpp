#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class SparseStyle {
public:
    struct Partition {
        int position;
        int style;
        Partition(int pos, int st) : position(pos), style(st) {}
    };

    SparseStyle(int defaultStyle = 0) : defaultStyle_(defaultStyle) {}

    int findPartition(int position) {
        for (size_t i = 0; i < partitions_.size(); ++i) {
            if (partitions_[i].position >= position) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void insertPartition(int position, int style) {
        int index = findPartition(position);
        if (index == -1 || partitions_[index].position != position) {
            partitions_.insert(partitions_.begin() + index, Partition(position, style));
        }
    }

    void removePartition(int index) {
        if (index >= 0 && index < static_cast<int>(partitions_.size())) {
            partitions_.erase(partitions_.begin() + index);
        }
    }

    void updateStyle(int position, int style) {
        int index = findPartition(position);
        if (index != -1) {
            partitions_[index].style = style;
        } else {
            insertPartition(position, style);
        }
    }

    void insertSpace(int position, int count) {
        int index = findPartition(position);
        for (size_t i = index; i < partitions_.size(); ++i) {
            partitions_[i].position += count;
        }
    }

    void removeSpace(int position, int count) {
        int index = findPartition(position);
        while (index < static_cast<int>(partitions_.size()) && partitions_[index].position < position + count) {
            partitions_.erase(partitions_.begin() + index);
        }
        for (size_t i = index; i < partitions_.size(); ++i) {
            partitions_[i].position -= count;
        }
    }

    int findFirstStyle(int style) {
        for (size_t i = 0; i < partitions_.size(); ++i) {
            if (partitions_[i].style == style) {
                return partitions_[i].position;
            }
        }
        return -1;
    }

    bool isUniform() {
        if (partitions_.empty()) {
            return true;
        }
        int style = partitions_[0].style;
        for (const auto &partition : partitions_) {
            if (partition.style != style) {
                return false;
            }
        }
        return true;
    }

    bool isUniform(int style) {
        for (const auto &partition : partitions_) {
            if (partition.style != style) {
                return false;
            }
        }
        return true;
    }

    void check() {
        checkPartitionsOrder();
        checkNoAdjacentSameStyle();
    }

private:
    std::vector<Partition> partitions_;
    int defaultStyle_;

    void checkPartitionsOrder() {
        for (size_t i = 1; i < partitions_.size(); ++i) {
            if (partitions_[i].position <= partitions_[i - 1].position) {
                throw std::runtime_error("Partitions are not ordered.");
            }
        }
    }

    void checkNoAdjacentSameStyle() {
        for (size_t i = 1; i < partitions_.size(); ++i) {
            if (partitions_[i].style == partitions_[i - 1].style) {
                throw std::runtime_error("Adjacent partitions have the same style.");
            }
        }
    }
};

int main() {
    SparseStyle sparseStyle;

    sparseStyle.insertPartition(3, 1);
    sparseStyle.insertPartition(5, 2);
    sparseStyle.insertPartition(7, 3);

    std::cout << "Initial partitions:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "Partition " << i << ": position = " << sparseStyle.partitions_[i].position << ", style = " << sparseStyle.partitions_[i].style << std::endl;
    }

    sparseStyle.insertSpace(5, 2);
    std::cout << "After inserting space at position 5:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "Partition " << i << ": position = " << sparseStyle.partitions_[i].position << ", style = " << sparseStyle.partitions_[i].style << std::endl;
    }

    sparseStyle.removeSpace(4, 2);
    std::cout << "After removing space at position 4:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "Partition " << i << ": position = " << sparseStyle.partitions_[i].position << ", style = " << sparseStyle.partitions_[i].style << std::endl;
    }

    int firstStyle2 = sparseStyle.findFirstStyle(2);
    std::cout << "First occurrence of style 2: position = " << firstStyle2 << std::endl;

    bool uniform = sparseStyle.isUniform();
    std::cout << "Is uniform? " << (uniform ? "Yes" : "No") << std::endl;

    bool uniformStyle2 = sparseStyle.isUniform(2);
    std::cout << "Is uniform with style 2? " << (uniformStyle2 ? "Yes" : "No") << std::endl;

    try {
        sparseStyle.check();
        std::cout << "Data consistency check: OK" << std::endl;
    } catch (const std::runtime_error &e) {
        std::cout << "Data consistency check: FAILED" << std::endl;
        std::cout << e.what() << std::endl;
    }

    return 0;
}
