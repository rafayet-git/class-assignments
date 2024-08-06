#include "SelectionSort.hpp"

template <class T>
SelectionSort<T>::SelectionSort(const bool& ascending) : SortingAlgo<T>("Selection Sort", false, ascending){
  //  Selection sort Unstable
}

template <class T>
void SelectionSort<T>::sort(std::vector<T>& list){
  this->comparisons_ = 0;
  this->swaps_ = 0;
  int size = list.size();
  // Go through entire list
  for (int i = 0; i < size; i++){
    // Find index of element to be swapped (minimum or maximum)
    int swap_index = findMinMax(list, i);
    // Swap and append to swaps_
    if (swap_index != i){
      std::swap(list[swap_index],list[i]);
      this->swaps_++;
    }
  }
}

template <class T>
size_t SelectionSort<T>::findMinMax(const std::vector<T>& list, size_t start) {
    // Initialize the index of the smallest or largest element as the starting index
    size_t minmax = start;
    // Loop through the elements in the list starting from the given start index
    for (size_t i = start; i < list.size(); i++) {
        // Increment the number of comparisons made by the algorithm
        this->comparisons_++;
        // Check if the element at current index 'i' is smaller or larger than the current smallest or largest
        if (this->comparator(list[i], list[minmax])) {
            // If it is smaller or larger, update the index of the smallest or largest element
            minmax = i;
        }
    }
    // Return the index of the smallest or largest element found
    return minmax;
}
