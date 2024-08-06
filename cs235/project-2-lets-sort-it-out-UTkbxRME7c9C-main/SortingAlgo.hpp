#pragma once
#include <iostream>
#include <vector>
template <class T>
class SortingAlgo{
    public:
        /**
         * @brief Constructor for SortingAlgo class
         * 
         * @param name: name of the sorting algorithm
         * @param stable: boolean indicating if the algorithm is stable
         * @param ascending: boolean indicating the order of sorting
         */
        SortingAlgo(const std::string& name, const bool& stable, const bool& ascending);
        
        /**
         * @brief Setter for name
         * 
         * @param name: name of the sorting algorithm
         */
        void setName(const std::string& name);
        
        /**
         * @brief Setter for stable
         * 
         * @param stable: boolean indicating if the algorithm is stable
         */
        void setStable(const bool& stable);
        
        /**
         * @brief Setter for ascending
         * 
         * @param ascending: boolean indicating the order of sorting
         */
        void setAscending(const bool& ascending);
        
        /**
         * @brief Getter for name
         * 
         * @return name of the sorting algorithm
         */
        std::string getName() const;
        
        /**
         * @brief Getter for stable
         * 
         * @return boolean indicating if the algorithm is stable
         */
        bool isStable() const;
        
        /**
         * @brief Getter for swaps
         * 
         * @return number of swaps made during sorting
         */
        size_t getSwaps() const;
        
        /**
         * @brief Getter for comparisons
         * 
         * @return number of comparisons made during sorting
         */
        size_t getComparisons() const;
        
        /**
         * @brief Getter for ascending
         * 
         * @return boolean indicating the order of sorting
         */
        bool isAscending() const;
        
        /**
         * @brief Check if list is sorted in ascending or descending order
         * 
         * @pre if (ascending_ == true), check if the given parameter is sorted in ascending order
         * @pre if (ascending_ == false), check if the given parameter is sorted in descending order
         * @param list: reference to a vector of type T
         * @return boolean indicating if the list is sorted
         */
        bool isSorted(std::vector<T>& list) const;
        
        /**
         * @brief Virtual function for sorting the list
         * 
         * @param list: reference to a vector of type T
         */
        virtual void sort(std::vector<T>& list) = 0;
    protected:
        std::string name_; 
        size_t swaps_;
        size_t comparisons_;
        bool stable_;
        bool ascending_;
        /**
        * @brief Comparator function to compare two elements for sorting
        * 
        * @param a: first element to compare
        * @param b: second element to compare
        * @return if (ascending_ == true), return true if (a < b)
        *         if (ascending_ == false), return true if (a > b)
        */
        bool comparator(const T& a, const T& b) const;
};

#include "SortingAlgo.cpp"
