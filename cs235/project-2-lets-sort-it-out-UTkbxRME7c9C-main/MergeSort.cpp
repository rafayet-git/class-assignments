#include "MergeSort.hpp"

template <class T>
MergeSort<T>::MergeSort(const bool& ascending) : SortingAlgo<T>("Merge Sort", true, ascending){
  //Merge sort is stable
} 

template<class T>
void MergeSort<T>::sort(std::vector<T>& list){\
    this->comparisons_ = 0;
    this->swaps_ = 0;
    if (!list.empty()) list = mergeSort(list);
}

template <class T>
std::vector<T> MergeSort<T>::merge(std::vector<T>& left, std::vector<T>& right) {
    // Vector to store the merged result
    std::vector<T> result;
    // Index for left and right vectors
    size_t l = 0;  
    size_t r = 0;
    // Merge the elements from left and right vectors into the result vector
    while (l < left.size() && r < right.size()) {
        // Compare elements using comparator and also check for equality to add equal elements from left first (<=)
        if (this->comparator(left[l], right[r]) or (left[l] == right[r])) {
            // Add element from left vector to result and move to the next element in left vector
            result.push_back(left[l]);  
            l++;
        } else {
            // Add element from right vector to result and move to the next element in right vector
            result.push_back(right[r]);  
            r++;
            // Increment swap count as adding an element from right half before left is to be counted as a swap operation
            this -> swaps_++;
        }
        // Increment comparison count
        this -> comparisons_++;  
    }
    // Add remaining elements from left vector to result
    while (l < left.size()) {
        result.push_back(left[l]);
        l++;
    }
    // Add remaining elements from right vector to result
    while (r < right.size()) {
        result.push_back(right[r]);
        r++;
    }
    // Return the merged and sorted result vector
    return result;
}

template <class T>
std::vector<T> MergeSort<T>::mergeSort(std::vector<T>& list){
    int size = list.size();
    // Base case
    if (size <= 1) return list;
    // Get middle pivot to split list into
    int pivot = size/2;
    // Split list into left_vector and right_vector
    std::vector<T> left_vector = {list.begin(), list.begin() + pivot};
    std::vector<T> right_vector = {list.begin() + pivot, list.end()};
    // Split and sort/merge vectors recursively
    left_vector = mergeSort(left_vector);
    right_vector = mergeSort(right_vector);
    list = merge(left_vector, right_vector);
    return list;
}
