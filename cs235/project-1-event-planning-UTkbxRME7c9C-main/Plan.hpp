/**
 * @file Plan.hpp
 * @author Rafayet Hossain (rafayet.hossain24@myhunter.cuny.edu)
 * @brief This file is the interface for Plan class.
 * @date 2024-06-15
 * 
 * @copyright Rafayet Hossain (c) 2024
 * 
 */

#pragma once

template<class T>
class Plan{
    public:
        /** 
        * @brief Default constructor to construct the Plan object.
        *  
        * @post Plan object is created with the capacity of 2.
        */
        Plan();
        /** 
        * @brief Copy assignment constructor with another Plan object
        *  
        * @param other The Plan object to be copied from
        * @post A new Plan object copied from the other Plan object.
        */
        Plan(const Plan& other);
        /** 
        * @brief Move assignment constructor with another Plan object
        *  
        * @param other The Plan object to be moved from
        * @post The other Plan object will be moved to the current Plan object.
        */
        Plan(Plan&& other) noexcept;
        /** 
        * @brief Default destructor to destruct the Plan object.
        *  
        * @post Plan object is deleted by deallocating dynamic memory.
        */
        ~Plan();
        /** 
        * @brief Copy assignment operator with another Plan object
        *  
        * @param other The Plan object to be copied from
        * @return The current Plan object after copying
        * @post The Plan object will be copied from the other Plan object.
        */
        Plan& operator=(const Plan& other);
        /** 
        * @brief Move assignment operator with another Plan object
        *  
        * @param other The Plan object to be moved from
        * @return The current Plan object after moving
        * @post The other Plan object will be moved to the current Plan object.
        */
        Plan& operator=(Plan&& other) noexcept;
        /**
        * @brief Add an event to the Plan
        *
        * @param event The event to be added to the Plan
        * @post If the array is full , the capacity of the array will be
        doubled and the event will be added
        */
        void addEvent(const T& event);
        /**
        * @brief Remove an event from the plan
        *
        * @param event The event to be removed
        * @return true if the event is in the array and is successfully
        removed
        * @return false if the event is not in the array and can ’t be
        removed
        * @post If the event exists in the Plan , it will be removed while
        retaining the order
        */
        bool removeEvent(const T& event);
        /**
        * @brief Get the pointer to the Plan array
        *
        * @return T * Pointer to the dynamically allocated array where Plan
        is stored
        */
        T* getEvents() const;
        /**
        * @brief Get the size of the Plan
        *
        * @return int Number of events in the plan
        5
        */
        int getSize() const;
        /**
        * @brief Get the capacity of the Plan array
        *
        * @return int The maximum number of items that can be stored in the
        currently allocated Plan array
        */
        int getCapacity() const;
        /**
        * @brief Get the index of the object
        *
        * @param event Object whose index is being queried
        * @return int Index of the object if it exists , -1 otherwise
        */
        int getIndexOf(const T& event);
    private:
        int capacity_;
        int item_count_;
        T* events_;
};
#include "Plan.cpp"