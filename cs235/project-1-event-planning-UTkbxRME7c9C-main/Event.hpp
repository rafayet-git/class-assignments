/**
 * @file Event.hpp
 * @author your name (your student email)
 * @brief This file is the interface for Event class
 * @date 2024-06-15
 * 
 * @copyright Rafayet Hossain (c) 2024
 * 
 */

#pragma once

#include <vector>
#include <iostream>
#include <string>

class Event{
    public:
        /**
         * @brief Default constructor to construct a new Event object
         * 
         * @post Event object created with "Not Set Yet" as name and -1 timestamp
         */
        Event();
        /**
         * @brief Parameterized constructor to construct a new Event object
         * 
         * @param name Name of the event
         * @param timestamp Timestamp of the event
         * @post Event object created with specified name and timestamp
         */
        Event(const std::string& name, const long& timestamp);
        /**
         * @brief Get the name of the event
         * 
         * @return std::string Name of the event
         */
        std::string getName() const;
        /**
         * @brief Get the timestamp of the event
         * 
         * @return long Timestamp of the event
         */
        long getTimestamp() const;
        /**
         * @brief Get the list of guests for the event
         * 
         * @return std::vector<std::string> List of guests for the event
         */
        std::vector<std::string> getGuests() const;
        /**
         * @brief Set the event name
         * 
         * @param name New name for the event
         * @post Name of the event set to specified name
         */
        void setName(const std::string& name);
        /**
         * @brief Set the event timestamp
         * 
         * @param timestamp New timestamp for the event
         * @return true If the timestamp parameter is positive and can be successfully set
         * @return false If the timestamp parameter is negative and is not a valid timestamp
         */
        bool setTimestamp(const long& timestamp);
        /**
         * @brief Set the guests list
         * 
         * @param guests New list of guests for the event
         * @return true If the list contains non-empty string names and can be successfully set
         * @return false If the list contains any empty string invalid names
         */
        bool setGuests(const std::vector<std::string>& guests);
        /**
         * @brief Overloaded stream insertion operator for Event
         * 
         * @param os Output stream
         * @param event Event object to output. Example output is provided in `example_output.txt`.
         * @return std::ostream& Output stream with event details
         */
        friend std::ostream& operator<<(std::ostream& os, const Event& event);
        /**
         * @brief Overloaded stream extraction operator for Event
         * 
         * @param is Input stream where users can enter the non-empty name of a new guest
         * @param event Event object to input to
         * @return std::istream& Input stream with event details
         * @post The guest name is entered at the end of guest list
         */
        friend std::istream& operator>>(std::istream& is, Event& event);
        /**
         * @brief Overloaded equal operator for Event
         * 
         * @param event1 Event object to be compared to event2
         * @param event2 Event object to by compared to event1
         * @return true if both events are equal
         * @return false if events are not equal to one another/
         */
        friend bool operator==(const Event& event1, const Event& event2);
        /**
         * @brief Add a single guest to the guests list
         * 
         * @param name Name of the guest to add
         * @return true If the name is not empty and guest is successfully added
         * @return false If the name is empty and guest can't be added
         * @post Guest added to the end of guests list if name is not empty
         */
        bool addGuest(const std::string& name);
        /**
         * @brief Add multiple guests to the guests list
         * 
         * @param names List of names of guests to add
         * @return true If the list doesn't contain an empty string and the guests can be added
         * @return false If the list contains an empty string and none of the guests are added
         * @post Guests added to the end of guests list if none of the names are empty
         */
        bool addGuest(const std::vector<std::string>& names);
        /**
         * @brief Remove a guest from the event by name
         * 
         * @param name Name of the guest to remove
         * @return true If the guest is in the guests list and is removed
         * @return false If the guest is not in the guests list and can't be removed
         * @post Guest removed from the event if found and the order of guests is maintained
         */
        bool removeGuest(const std::string& name);
        /**
         * @brief Remove a guest from the event by index
         * 
         * @param id Index of the guest to remove
         * @return true If the index is within the size of the guests list and is removed
         * @return false If the index is not within the guests list and can't be removed
         * @post Guest removed from the event if index is within the size of the list and the order of guests is maintained
         */
        bool removeGuest(const size_t& id);
    private:    
        std::string name_;
        long timestamp_;
        std::vector<std::string> guests_;
        /**
         * @brief Convert the event unix timestamp to string format
         * 
         * @return std::string String representation of event time or "Not Set Yet" if time is not set
         */
        std::string timeToString() const;
};
