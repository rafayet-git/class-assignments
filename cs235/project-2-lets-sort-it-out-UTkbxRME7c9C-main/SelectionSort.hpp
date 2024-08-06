#pragma once
#include "SortingAlgo.hpp"
template <class T>
class SelectionSort : public SortingAlgo<T> {
    public:
        /**
         * @brief Constructor for SelectionSort class
         *
         * @param ascending: boolean indicating the order of sorting
         */ 
        SelectionSort(const bool& ascending);
        
        /**
         * @brief Override function for sorting list with Selection sort
         *
         * @param list: reference to a vector of type T
         */ 
        void sort(std::vector<T>& list) override;
    private:
        
        /**
         * @brief Helper function to return the smallest/biggest number in list
         *
         * @param list: reference to a vector to be searched
         * @param start: the starting index of list
         * @return index of smallest/biggest element >= start
         */ 
        size_t findMinMax(const std::vector<T>& list,size_t start);
};

#include "SelectionSort.cpp"
