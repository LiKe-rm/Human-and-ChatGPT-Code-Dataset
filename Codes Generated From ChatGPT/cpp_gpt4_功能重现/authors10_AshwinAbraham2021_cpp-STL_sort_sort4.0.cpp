#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class Sort {
public:
    // 冒泡排序
    void bubblesort(std::vector<int> &arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size();
        for (int i = begin; i < end - 1; ++i) {
            for (int j = begin; j < end - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // 选择排序
    void selectionsort(std::vector<int> &arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size();
        for (int i = begin; i < end - 1; ++i) {
            int min_index = i;
            for (int j = i + 1; j < end; ++j) {
                if (arr[j] < arr[min_index]) {
                    min_index = j;
                }
            }
            if (min_index != i) {
                std::swap(arr[min_index], arr[i]);
            }
        }
    }

    // 插入排序
    void insertionsort(std::vector<int> &arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size();
        for (int i = begin + 1; i < end; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= begin && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // 计数排序
    void countingsort(std::vector<int> &arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size();
        int max_value = *std::max_element(arr.begin() + begin, arr.begin() + end);
        int min_value = *std::min_element(arr.begin() + begin, arr.begin() + end);
        std::vector<int> count(max_value - min_value + 1, 0);

        for (int i = begin; i < end; ++i) {
            count[arr[i] - min_value]++;
        }

        int index = begin;
        for (int i = 0; i < count.size(); ++i) {
            while (count[i] > 0) {
                arr[index++] = i + min_value;
                count[i]--;
            }
        }
    }
    // 归并排序
    void mergesort(std::vector<int> &arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size();
        if (end - begin <= 1) return;

        int mid = begin + (end - begin) / 2;
        mergesort(arr, begin, mid);
        mergesort(arr, mid, end);
        merge(arr, begin, mid, end);
    }

    // 快速排序
    void quicksort(std::vector<int> &arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size();
        if (end - begin <= 1) return;

        int pivot_index = partition(arr, begin, end);
        quicksort(arr, begin, pivot_index);
        quicksort(arr, pivot_index + 1, end);
    }

    // 二分查找
    int binarysearch(const std::vector<int> &arr, int target, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size();
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                begin = mid + 1;
            } else {
                end = mid;
            }
        }
        return -1; // target not found
    }

    // 查找元素的上界
    int upperlim(const std::vector<int> &arr, int target, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size();
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            if (arr[mid] <= target) {
                begin = mid + 1;
            } else {
                end = mid;
            }
        }
        return begin;
    }

    // 查找元素的下界
    int lowerlim(const std::vector<int> &arr, int target, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size();
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            if (arr[mid] < target) {
                begin = mid + 1;
            } else {
                end = mid;
            }
        }
        return begin;
    }

private:
    // 合并两个有序区间
    void merge(std::vector<int> &arr, int begin, int mid, int end) {
        std::vector<int> left(arr.begin() + begin, arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.begin() + end);
        int i = 0, j = 0, k = begin;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }

        while (i < left.size()) {
            arr[k++] = left[i++];
        }

        while (j < right.size()) {
            arr[k++] = right[j++];
        }
    }

    // 快速排序分区函数
    int partition(std::vector<int> &arr, int begin, int end) {
        int pivot = arr[begin];
        int i = begin + 1;
        int j = end - 1;

        while (true) {
            while (i <= j && arr[i] <= pivot) {
                i++;
            }

            while (i <= j && arr[j] > pivot) {
                j--;
            }

            if (i <= j) {
                std::swap(arr[i], arr[j]);
            } else {
                break;
            }
        }
        std::swap(arr[begin], arr[j]);
        return j;
    }
}
