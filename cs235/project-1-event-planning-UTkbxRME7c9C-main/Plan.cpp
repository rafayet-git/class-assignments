/**
 * @file Plan.cpp
 * @author Rafayet Hossain (rafayet.hossain24@myhunter.cuny.edu)
 * @brief This file is the implementation for Plan class.
 * @date 2024-06-15
 * 
 * @copyright Rafayet Hossain (c) 2024
 * 
 */
#include "Plan.hpp"

template<class T>
Plan<T>::Plan(){
    capacity_ = 2;
    item_count_ = 0;
    events_ = new T[capacity_];
}

template<class T>
Plan<T>::Plan(const Plan& other){
    // copy all of other into the new plan
    capacity_ = other.capacity_;
    item_count_ = other.item_count_;
    events_ = new T[capacity_];
    for (int i = 0; i < item_count_; i++){
        events_[i] = other.events_[i];
    }
}

template<class T>
Plan<T>::Plan(Plan&& other) noexcept{
    // move all of other into the new plan
    capacity_ = other.capacity_;
    item_count_ = other.item_count_;
    events_ = other.events_;
    // clear other plan
    other.events_ = nullptr;
    other.item_count_ = 0;
    other.capacity_ = 0;
}

template<class T>
Plan<T>::~Plan(){
    delete[] events_;
    events_ = nullptr;
}

template<class T>
Plan<T>& Plan<T>::operator=(const Plan& other) {
    // clear plan and copy other plan into this plan
    if (this != &other) {
        delete[] events_;
        capacity_ = other.capacity_;
        item_count_ = other.item_count_;
        events_ = new T[capacity_];
        for (int i = 0; i < item_count_; i++){
            events_[i] = other.events_[i];
        }

    }
    return *this;
}

template<class T>
Plan<T>& Plan<T>::operator=(Plan&& other) noexcept{
    // clear plan and move other plan into this plan
    if (this != &other) {
        delete[] events_;
        capacity_ = other.capacity_;
        item_count_ = other.item_count_;
        events_ = other.events_;
        // clear other plan
        other.events_ = nullptr;
        other.item_count_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template<class T>
void Plan<T>::addEvent(const T& event){
    if (capacity_ == item_count_){
        // double capacity and make new array to make room for new event
        capacity_ *= 2;
        T* tmp = new T[capacity_];
        for (int i = 0; i < item_count_; i++){
            tmp[i] = events_[i];
        }
        delete[] events_;
        events_ = tmp;
        tmp = nullptr;
    }
    events_[item_count_] = event;
    item_count_++;
}

template<class T>
bool Plan<T>::removeEvent(const T& event){
    int index = getIndexOf(event);
    if (index == -1) return false;
    item_count_--;
    // move events on the right of event down one index
    for (int i = index; i < item_count_; i++){
        events_[i] = events_[i+1];
    }
    return true;
}

template<class T>
T* Plan<T>::getEvents() const{
    return events_;
}

template<class T>
int Plan<T>::getSize() const{
    return item_count_;
}

template<class T>
int Plan<T>::getCapacity() const{
    return capacity_;
}

template<class T>
int Plan<T>::getIndexOf(const T& event) {
    for (int i = 0; i < item_count_; i++){
        if (event == events_[i]) return i;
    }
    // return -1 if event does not exist in the list.
    return -1;
}
