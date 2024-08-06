#pragma once
#include "SortingAlgo.hpp"
template <class T>
class BubbleSort : public SortingAlgo<T>{
    public:
        /**
         * @brief Constructor for BubbleSort class
         *
         * @param ascending: boolean indicating the order of sorting
         */ 
        BubbleSort(const bool& ascending);
        
        /**
         * @brief Override function for sorting list with bubble Sort
         *
         * @param list: reference to a vector of type T
         */ 
        void sort(std::vector<T>& list) override;
};

#include "BubbleSort.cpp"
