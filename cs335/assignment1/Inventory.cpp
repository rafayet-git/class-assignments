#include "Inventory.hpp"

Inventory::Inventory(const std::vector<std::vector<Item>>& items, Item* equipped){

}

Item* Inventory::getEquipped() const{

}

void Inventory::equip(Item* itemToEquip){

}

void Inventory::discardEquipped(){

}

std::vector<std::vector<Item>> Inventory::getItems() const{

}

float Inventory::getWeight() const{

}
size_t Inventory::getCount() const{
  
}


Item Inventory::at(const size_t& row, const size_t& col) const{

}

bool Inventory::store(const size_t& row, const size_t& col, const Item& pickup){

}


Inventory::Inventory(const Inventory& rhs){

}

Inventory::Inventory(Inventory&& rhs){

}


Inventory& Inventory::operator=(const Inventory& rhs){

}


Inventory& Inventory::operator=(Inventory&& rhs){

}

Inventory::~Inventory(){

}

