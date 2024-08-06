/**
 * @file main.cpp
 * @author Sadab Hafiz (sh3646@hunter.cuny.edu)
 * @brief An example main file testing the functions from the `Event` class. Output is stored in `example_output.txt`.
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Event.hpp"
#include "Plan.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(){
    // Test Default Constuctor
    Event undecided;
    // Test Parameterized Constructor
    Event s1_midterm("CS235-01 MIDTERM", 1718718600);
    Event s2_midterm("CS235-02 MIDTERM", 1718738400);
    // Create a string vector to use as a parameter
    std::vector<std::string> names = {
        "Sadab Hafiz",
        "Yoomin Song",
        "Ryan Vaz",
        "Tiziana Ligorio",
        "Khant Ko Naing"
    };
    // Test adding string guests
    for (std::string name : names){
        s1_midterm.addGuest(name);
    }
    // Test adding vector of guests
    s2_midterm.addGuest(names);
    // Test `setGuests` (note that the existing names are removed)
    undecided.addGuest("Pavel Shostak");
    undecided.setGuests(names);
    // Test removing guest by index or name
    undecided.removeGuest(4);
    undecided.removeGuest(15);
    undecided.removeGuest("Pavel Shostak");
    undecided.removeGuest("Tiziana Ligorio");
    // Add guest using input stream. Uncomment it to try
    // std::cin >> undecided;
    // Print out the three Events using output stream
    std::cout << undecided << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << s1_midterm << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << s2_midterm << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    // TODO: ADD MORE CODE TO TEST THE OTHER FUNCTIONS AND EDGE CASES!!!
    s2_midterm.setName("CS235 FINAL");
    s2_midterm.setTimestamp(0);
    std::cout << s2_midterm << std::endl;
    std::cout << "------------------------------------------- \n Input:" << std::endl;
    std::cin >> s2_midterm;
    std::cout << s2_midterm << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    Event s4(s1_midterm.getName(), s1_midterm.getTimestamp());
    s4.setGuests(s1_midterm.getGuests());
    if ((s4 == s1_midterm)) std::cout << "Matches" << std::endl;
    // TODO: ADD CODE TO TEST PLAN CLASS AFTER IMPLEMENTING IT
    Plan<Event> Plan1;
    std::cout << "Plan 1: " << Plan1.getSize() << " " << Plan1.getCapacity() << std::endl;
    Plan1.addEvent(undecided);
    Plan1.addEvent(s1_midterm);
    Plan1.addEvent(s2_midterm);
    Plan1.addEvent(s4);
    std::cout << "Plan 1 after add: " << Plan1.getSize() << " " << Plan1.getCapacity() << std::endl;
    Plan<Event> Plan2;
    Plan2 = Plan1;
    std::cout << "Plan 2 after copy: " << Plan2.getSize() << " " << Plan2.getCapacity() << std::endl;
    Plan2.removeEvent(s4);
    Plan2.removeEvent(s2_midterm);
    Plan2.removeEvent(s1_midterm);
    std::cout << "Plan 2 after delete: " << Plan2.getSize() << " " << Plan2.getCapacity() << std::endl;
    Plan1 = std::move(Plan2);
    std::cout << "Plan 2 after move: " << Plan2.getSize() << " " << Plan2.getCapacity() << std::endl;
    std::cout << "Plan 1 after move: " << Plan1.getSize() << " " << Plan1.getCapacity() << std::endl;

}
