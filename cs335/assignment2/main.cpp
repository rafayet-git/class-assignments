#include "Compare.hpp"
#include "HashInventory.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "ItemAVL.hpp"
#include <list>
#include "TreeInventory.hpp"
#include "ItemGenerator.hpp"
#include <chrono>
#include <iostream>

template <class Container>
double timeContains(const Inventory<CompareItemName, Container> &inv, std::string name){
    auto start_time = std::chrono::high_resolution_clock::now();
    (void)inv.contains(name);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end_time - start_time;
    return duration.count();
}
template <class Container>
void invResultsPartA(Inventory<CompareItemName, Container> &inv, int n){
    std::vector<std::string> contained;
    std::vector<std::string> missing;
    ItemGenerator gen(42);
    for (int i = 0; i < n; i++) inv.pickup(gen.randomItem());
    for (int i = 0; i < 100; i++) contained.push_back(gen.randomUsedName());
    for (int i = 0; i < 100; i++) missing.push_back(gen.randomItem().name_);
    double total = 0;
    for (const auto &name : contained) {
        total += timeContains(inv, name);
    }
    for (const auto &name : missing) {
        total += timeContains(inv, name);
    }
    total /= 200;
    std::cout << " " << total << "us" << std::endl;

}

template <class Comparator, class Container>
double timeQuery(const Inventory<Comparator, Container> &inv, Item start, Item end){
    auto start_time = std::chrono::high_resolution_clock::now();
    auto result = inv.query(start, end);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end_time - start_time;
    return duration.count();
}
template <class Container>
void invResultsPartB(Inventory<CompareItemName, Container> &inv, int n){
    ItemGenerator gen(42);
    for (int i = 0; i < n; i++) inv.pickup(gen.randomItem());

    double totalQueryTime = 0;
    for (int i = 0; i < 10; i++) {
        Item start(gen.randomUsedName());
        Item end(gen.randomUsedName());
        if (CompareItemName::lessThan(end, start)) std::swap(start, end);
        totalQueryTime += timeQuery(inv, start, end);
    }
    totalQueryTime /= 10;
    std::cout << " " << totalQueryTime << "us" << std::endl;
}

template <class Container>
void invResultsPartB(Inventory<CompareItemWeight, Container> &inv, int n){
    ItemGenerator gen(42);
    for (int i = 0; i < n; i++) inv.pickup(gen.randomItem());
    double totalQueryTime = 0;
    for (int i = 0; i < 10; i++) {
        float startWeight = gen.randomFloat(0.1, 30.0);
        Item start("", startWeight);
        Item end("", startWeight + 0.1f);
        totalQueryTime += timeQuery(inv, start, end);
    }
    totalQueryTime /= 10;
    std::cout << " " << totalQueryTime << "us" << std::endl;

}

int main()
{
    std::cout << "part B" << std::endl;
    int nlist[] = { 1000, 2000, 4000, 8000 };
    for (int n : nlist) {
        std::cout << "n = " << n << std::endl;
        Inventory<CompareItemWeight> invVector;
        std::cout << "vector:";
        invResultsPartB(invVector, n);

        Inventory<CompareItemWeight, std::list<Item>> invList;
        std::cout << "list:";
        invResultsPartB(invList, n);
        
        Inventory<CompareItemWeight, std::unordered_set<Item>> invSet;
        std::cout << "set:";
        invResultsPartB(invSet, n);

        Inventory<CompareItemWeight, Tree> invTree;
        std::cout << "tree:";
        invResultsPartB(invTree, n);

        std::cout << std::endl;
        
    }

    return 0;
}
