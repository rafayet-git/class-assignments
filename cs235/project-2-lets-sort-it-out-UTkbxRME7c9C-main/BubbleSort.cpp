#include "BubbleSort.hpp"

template<class T>
BubbleSort<T>::BubbleSort(const bool& ascending) : SortingAlgo<T>("Bubble Sort", true, ascending){
  // Bubble sort is stable
}

template <class T>
void BubbleSort<T>::sort(std::vector<T>& list){
  this->comparisons_ = 0;
  this->swaps_ = 0;
  int size = list.size();
  bool swapped = true;
  int pass = 1;
  // While loop stops when entire list is sorted
  // (entire list passes or if no swaps occured during last pass)
  while (swapped && (pass < size)){
    swapped = false;
    for(int i = 0; i < size - pass; i++){
      // Compare and swap whenever a higher/lower element is found
      if (this->comparator(list[i+1], list[i])){
        std::swap(list[i], list[i+1]);
        swapped = true;
        this->swaps_++;
      }
      this->comparisons_++;
    }
    pass++;
  }
}
