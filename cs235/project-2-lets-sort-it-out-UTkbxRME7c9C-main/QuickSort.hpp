#pragma once
#include "SortingAlgo.hpp"
template <class T>
class QuickSort : public SortingAlgo<T>{
    public:
        /**
         * @brief Constructor for Quick Sort class
         *
         * @param ascending: boolean indicating the order of sorting
         */ 
        QuickSort(const bool& ascending);
        
        /**
         * @brief Override function for sorting list with quick Sort
         *
         * @param list: reference to a vector of type T
         */ 
        void sort(std::vector<T>& list) override;
    private:
        
        /**
         * @brief Function to sort list using Quick sort
         *
         * @param list: reference to a vector to be sorted
         * @param low: starting index of list (0)
         * @oaran high: ending index of list
         */ 
        void quickSort(std::vector<T>& list, int low, int high);
        
        /**
         * @brief Helper function to partition and sort lists
         *
         * @param list: reference to a vector to be sorted
         * @param low: starting index of partitioned list
         * @param high: ending index of partitioned list
         * @return pivot index of partitioned list
         */ 
        int partition(std::vector<T>& list, int low, int high);
};

#include "QuickSort.cpp"
