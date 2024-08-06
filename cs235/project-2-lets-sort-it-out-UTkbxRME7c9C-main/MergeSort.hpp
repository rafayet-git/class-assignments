#pragma once
#include "SortingAlgo.hpp"
template <class T>
class MergeSort : public SortingAlgo<T> {
    public:
        /**
         * @brief Constructor for MergeSort class
         * 
         * @param ascending: boolean indicating the order of sorting
         */
        MergeSort(const bool& ascending);
        
        /**
         * @brief Override function for sorting list with mergeSort 
         * 
         * @param list: reference to a vector of type T
         */
        void sort(std::vector<T>& list) override;
    private:

        /**
         * @brief Helper function to merge and sort two vectors into one
         *
         * @param left: reference to leftmost vector
         * @param right: reference to rightmost vector
         * @return vector of type T after merging
         */ 
        std::vector<T> merge(std::vector<T>& left, std::vector<T>& right);

        /**
         * @brief Function to sort list using Merge sort
         *
         * @param list: reference to a vector to be sorted
         * @return vector of type T containing sorted list
         */ 
        std::vector<T> mergeSort(std::vector<T>& list);
};

#include "MergeSort.cpp"
