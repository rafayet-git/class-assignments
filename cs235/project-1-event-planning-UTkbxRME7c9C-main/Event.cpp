/**
 * @file Event.cpp
 * @author Rafayet Hossain (rafayet.hossain24@myhunter.cuny.edu)
 * @brief This file is the implementation for Event class
 * @date 2024-06-15
 * 
 * @copyright Rafayet Hossain (c) 2024
 * 
 */

#include "Event.hpp"


Event::Event(){
  name_ = "Not Set Yet";
  timestamp_ = -1;
}


Event::Event(const std::string& name, const long& timestamp){
  name_ = name;
  timestamp_ = timestamp;
}



std::string Event::getName() const{
  return name_;
}

long Event::getTimestamp() const{
  return timestamp_;
}

std::vector<std::string> Event::getGuests() const{
  return guests_;
}

void Event::setName(const std::string& name){
  name_ = name;
}

bool Event::setTimestamp(const long& timestamp){
  if (timestamp < 0) return false; // timestamp must be greater than 0
  timestamp_ = timestamp;
  return true;
}

bool Event::setGuests(const std::vector<std::string>& guests){
  // Iterate through given guests list to check for empty strings.
  for (const auto& guest_name : guests){
    if (guest_name.empty()) return false;
  }
  guests_ = guests;
  return true;
}

std::ostream& operator<<(std::ostream& os, const Event& event){
  os << "Name: " << event.name_ << "\n";
  os << "Time: " << event.timeToString() << "\n";
  os << "Guests:";
  int step = 0;
  // Print all guest names 
  for (const auto& guest_name : event.guests_){
    os << "\n" << step << ": " << guest_name;
    step++;
  }
  return os;
}

std::istream& operator>>(std::istream& is, Event& event){
  std::string guest_name;
  std::getline(is, guest_name);
  event.addGuest(guest_name);
  return is;
}

bool operator==(const Event& event1, const Event& event2){
  // Compare if values of both events are equal
  return (event1.getName() == event2.getName() &&
          event1.getTimestamp() == event2.getTimestamp() &&
          event1.getGuests() == event2.getGuests());
}

bool Event::addGuest(const std::string& name){
  if (name.empty()) return false;
  guests_.push_back(name);
  return true;
}

bool Event::addGuest(const std::vector<std::string>& names){
  // Check if provided list doesnt contain an empty string
  for (const auto& guest_name : names){
    if (guest_name.empty()) return false;
  }
  // Add each guest onto guest list
  for (const auto& guest_name : names){
    guests_.push_back(guest_name);
  }
  return true;
}

bool Event::removeGuest(const std::string& name){
  int count = 0;
  for (const auto& guest_name : guests_){
    if (guest_name == name){
      guests_.erase(guests_.begin()+count);
      return true;
    }
    count++;
  }
  return false;
}

bool Event::removeGuest(const size_t& id){
  // Check if id is valid
  if (id < 0 || id >= guests_.size()) return false;
  guests_.erase(guests_.begin() + id);
  return true;
}


std::string Event::timeToString() const {
    // if timestamp is -1, it is not valid and is the result of default constructor
    if (timestamp_ == -1) {
        return "Not Set Yet";
    }
    struct tm* dt = localtime(&timestamp_);
    std::string time = asctime(dt);
    time.pop_back();
    return time;
}
