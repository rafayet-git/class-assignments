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
    std::swap(equipped_, itemToEquip);
}

void Inventory::discardEquipped(){
    delete equipped_;
    equipped_ = nullptr;
}

std::vector<std::vector<Item>> Inventory::getItems() const{
    return inventory_grid_;
}

float Inventory::getWeight() const{
    return weight_;
}
size_t Inventory::getCount() const{
    return item_count_; 
}


Item Inventory::at(const size_t& row, const size_t& col) const{
    if (row < 0 || row >= inventory_grid_.size() || col < 0 || col >= inventory_grid_[0].size())
        throw std::out_of_range("at() Out of bounds");
    return inventory_grid_[row][col];
}

bool Inventory::store(const size_t& row, const size_t& col, const Item& pickup){
    if (row < 0 || row >= inventory_grid_.size() || col < 0 || col >= inventory_grid_[0].size())
        throw std::out_of_range("store() Out of bounds");
    if (inventory_grid_[row][col].type_ != NONE) return false;
    inventory_grid_[row][col] = pickup;
    weight_ += pickup.weight_;
    item_count_++;
    return true;
}


Inventory::Inventory(const Inventory& rhs) : 
    inventory_grid_(rhs.inventory_grid_), equipped_(nullptr), weight_(rhs.weight_), item_count_(rhs.item_count_) {
    if (rhs.equipped_ != nullptr)
        equipped_ = new Item(*rhs.equipped_);
}

Inventory::Inventory(Inventory&& rhs) :
    inventory_grid_(std::move(rhs.inventory_grid_)), equipped_(rhs.equipped_), weight_(rhs.weight_), item_count_(rhs.item_count_){
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0;
    rhs.item_count_ = 0;
}


Inventory& Inventory::operator=(const Inventory& rhs){
    if (this != &rhs) {
        delete equipped_;

        inventory_grid_ = rhs.inventory_grid_;
        equipped_ = (rhs.equipped_ != nullptr) ? new Item(*rhs.equipped_) : nullptr;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
    }
    return *this;
}


Inventory& Inventory::operator=(Inventory&& rhs){
    if (this != &rhs) {
        delete equipped_;

        inventory_grid_ = std::move(rhs.inventory_grid_);
        equipped_ = rhs.equipped_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        rhs.equipped_ = nullptr;
        rhs.weight_ = 0;
        rhs.item_count_ = 0;
    }
    return *this;
}

Inventory::~Inventory(){
    delete equipped_;
}

