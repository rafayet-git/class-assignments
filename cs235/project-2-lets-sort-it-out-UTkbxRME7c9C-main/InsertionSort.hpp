#pragma once
#include "SortingAlgo.hpp"
template <class T>
class InsertionSort : public SortingAlgo<T>{
    public:
        /**
         * @brief Constructor for InsertionSort class
         *
         * @param ascending: boolean indicating the order of sorting
         */ 
        InsertionSort(const bool& ascending);
        
        /**
         * @brief Override function for sorting list with InsertionSort
         *
         * @param list: reference to a vector of type T
         */ 
        void sort(std::vector<T>& list) override;
};

#include "InsertionSort.cpp"
