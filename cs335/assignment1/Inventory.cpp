#include "Inventory.hpp"

Inventory::Inventory(const std::vector<std::vector<Item>>& items, Item* equipped) : 
    inventory_grid_(items), equipped_(equipped), weight_(0), item_count_(0) {
    for (const auto& row : items){
        for (const auto& item : row){
            if (item.type_ != NONE){
                weight_ += item.weight_;
                item_count_++;
            }
        }
    }
}

Item* Inventory::getEquipped() const{
    return equipped_;
}

void Inventory::equip(Item* itemToEquip){
    equipped_ = itemToEquip;
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
    delete equipped_;
}

