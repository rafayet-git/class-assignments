#include "InsertionSort.hpp"

template<class T>
InsertionSort<T>::InsertionSort(const bool& ascending) : SortingAlgo<T>("Insertion Sort", true, ascending){
  // insertion sort is stable
}

template <class T>
void InsertionSort<T>::sort(std::vector<T>& list){
  this->comparisons_ = 0;
  this->swaps_ = 0;

  int size = list.size();
  // Go through entire unsorted list
  for(int i = 1; i < size; i++){
    int current = i;
    // Go through entire left region from i
    // Compare and swap when a higher/lower element is found
    while((current > 0) && (this->comparator(list[current],list[current-1]))){
      std::swap(list[current],list[current-1]);
      current--;
      this->swaps_++;
      this->comparisons_++;
    }
    this->comparisons_++;
  }
}

