/**
 * @file main.cpp
 * @author Sadab Hafiz (sh3646@hunter.cuny.edu)
 * @brief 
 * @date 2024-06-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <vector>
#include "SortingAlgo.hpp"
#include "SelectionSort.hpp"
#include "BubbleSort.hpp"
#include "InsertionSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"

/**
 * @brief Prints the elements in a vector. 
 * 
 * This function takes a vector and a boolean indicating if the elements are sorted, 
 * and prints the elements in the vector. If the elements are sorted, the color 
 * used to print will be green, otherwise it will be red.
 * 
 * @param list The vector to be printed
 * @param sorted Indicates if the elements in the vector are sorted
 * DO NOT MODIFY THIS FUNCTION
 */
template <class T>
void printVector(std::vector<T> list,const bool& sorted) {
    std::cout << (sorted ? "\033[1;32m" : "\033[91m");
    for(T x: list){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    std::cout << (sorted ? "\033[1;32m" : "\033[91m");
}

/**
 * @brief Prints the results of sorting algorithms on a vector.
 * 
 * This function takes a vector and parameters to specify which sorting algorithms to apply. 
 * It then applies the selected algorithms to the vector and prints the original vector, 
 * the sorted vector in ascending order, the number of comparisons and swaps, and the sorted 
 * vector in descending order for each algorithm selected.
 * 
 * @param list The vector to be sorted and printed
 * @param selection Indicates if Selection Sort should be used
 * @param bubble Indicates if Bubble Sort should be used
 * @param insertion Indicates if Insertion Sort should be used
 * @param merge Indicates if Merge Sort should be used
 * @param quick Indicates if Quick Sort should be used
 * DO NOT MODIFY THIS FUNCTION. YOU CAN CHANGE THE PARAMETERS TO TEST SPECIFIC ALGORITHMS.
 */
template <class T>
void printAlgorithms(std::vector<T>& list, bool selection=true, bool bubble=true, bool insertion=true, bool merge=true, bool quick=true) {
    std::vector<SortingAlgo<T>*> algorithms;
    if (selection) { algorithms.push_back(new SelectionSort<T>(true)); }
    if (bubble) { algorithms.push_back(new BubbleSort<T>(true)); }
    if (insertion) { algorithms.push_back(new InsertionSort<T>(true)); }
    if (merge) { algorithms.push_back(new MergeSort<T>(true)); }
    if (quick) { algorithms.push_back(new QuickSort<T>(true)); }
    for (auto a: algorithms) {
        std::vector<T> ascending = list;
        std::vector<T> descending = list;
        std::cout << "\033[1;34m=================================\033[0m" << std::endl;
        std::cout << "\033[1;34mAlgorithm: \033[0m" << a -> getName() << std::endl;
        std::cout << "\033[1;34mStable: \033[0m" << (a -> isStable() ? "\033[1;32mYes\033[1;32m":"\033[91mNo\033[91m") << std::endl;
        std::cout << "\033[1;34mOriginal: \033[0m"; 
        printVector(list,false);
        a -> sort(ascending);
        std::cout << "\033[1;34mAscending: \033[0m";
        printVector(ascending,a -> isSorted(ascending));
        std::cout << "\033[1;34mComparisons: \033[0m" << a -> getComparisons() << " | \033[1;34mSwaps: \033[0m" << a -> getSwaps() << std::endl;
        a -> setAscending(false);
        a -> sort(descending);
        std::cout << "\033[1;34mDescending: \033[0m"; 
        printVector(descending,a -> isSorted(descending));
        std::cout << "\033[1;34mComparisons: \033[0m" << a -> getComparisons() << " | \033[1;34mSwaps: \033[0m" << a -> getSwaps() << std::endl;
        std::cout << "\033[1;34m=================================\033[0m" << std::endl;
        delete a;
        a = nullptr;
    }
}

int main(){
    std::vector<int> list_0;
    std::vector<int> list_1 = {1};
    std::vector<int> list_2 = {1,2,3,4,5,6,7,8,9,10};
    std::vector<int> list_3 = {10,9,8,7,6,5,4,3,2,1};
    std::vector<int> list_4 = {1,1,1,1,1,1,1,1,1,1};
    std::vector<int> list_5 = {10,20,30,40,50,10,20,30,40,50};
    std::vector<int> list_6 = {78, 101, 118, 101, 114, 32, 70, 97, 100, 101, 32, 65, 119, 97, 121}; // hmmmmm... what could these numbers mean?
    printAlgorithms<int>(list_0); // expected output in `/expected_output/list_0.txt`
    printAlgorithms<int>(list_1); // expected output in `/expected_output/list_1.txt`
    printAlgorithms<int>(list_2); // expected output in `/expected_output/list_2.txt`
    printAlgorithms<int>(list_3); // expected output in `/expected_output/list_3.txt`
    printAlgorithms<int>(list_4); // expected output in `/expected_output/list_4.txt`
    printAlgorithms<int>(list_5); // expected output in `/expected_output/list_5.txt`
    printAlgorithms<int>(list_6); // expected output in `/expected_output/list_6.txt`
}
