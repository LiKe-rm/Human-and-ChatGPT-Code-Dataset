#include <iostream>
#include <vector>
#include <algorithm>

class Sort {
public:
    static void bubblesort(std::vector<int>& arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size() - 1;
        for (int i = begin; i <= end; i++) {
            for (int j = end; j > i; j--) {
                if (arr[j] < arr[j - 1]) {
                    std::swap(arr[j], arr[j - 1]);
                }
            }
        }
    }

    static void selectionsort(std::vector<int>& arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size() - 1;
        for (int i = begin; i <= end; i++) {
            int minIndex = i;
            for (int j = i + 1; j <= end; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            std::swap(arr[i], arr[minIndex]);
        }
    }

    static void insertionsort(std::vector<int>& arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size() - 1;
        for (int i = begin + 1; i <= end; i++) {
            int temp = arr[i];
            int j = i - 1;
            while (j >= begin && arr[j] > temp) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
    }

    static void countingsort(std::vector<int>& arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size() - 1;
        int maxVal = *std::max_element(arr.begin() + begin, arr.begin() + end + 1);
        std::vector<int> count(maxVal + 1);
        for (int i = begin; i <= end; i++) {
            count[arr[i]]++;
        }
        int idx = begin;
        for (int i = 0; i <= maxVal; i++) {
            while (count[i]-- > 0) {
                arr[idx++] = i;
            }
        }
    }

    static void mergesort(std::vector<int>& arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size() - 1;
        if (begin >= end) return;
        int mid = begin + (end - begin) / 2;
        mergesort(arr, begin, mid);
        mergesort(arr, mid + 1, end);
        std::vector<int> temp(end - begin + 1);
        int i = begin, j = mid + 1, k = 0;
        while (i <= mid && j <= end) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= end) temp[k++] = arr[j++];
        std::copy(temp.begin(), temp.end(), arr.begin() + begin);
    }
    static void quicksort(std::vector<int>& arr, int begin = 0, int end = -1) {
        if (end == -1) end = arr.size() - 1;
        if (begin >= end) return;
        int pivot = partition(arr, begin, end);
        quicksort(arr, begin, pivot - 1);
        quicksort(arr, pivot + 1, end);
    }

    static int binarysearch(const std::vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    static int upperlim(const std::vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        int res = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > target) {
                res = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return res;
    }

    static int lowerlim(const std::vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        int res = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] >= target) {
                res = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return res;
    }
private:
    static int partition(std::vector<int>& arr, int begin, int end) {
        int pivot = arr[end];
        int i = begin;
        for (int j = begin; j < end; j++) {
            if (arr[j] < pivot) {
                std::swap(arr[i], arr[j]);
                i++;
            }
        }
        std::swap(arr[i], arr[end]);
        return i;
    }
}
