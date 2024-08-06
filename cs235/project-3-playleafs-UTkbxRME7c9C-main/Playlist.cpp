/**
 * @file Playlist.cpp
 * @author Rafayet Hossain (rafayet.hossain24@myhunter.cuny.edu)
 * @brief This file is the implementation for Playlist class.
 * @date 2024-07-14
 * 
 * @copyright Rafayet Hossain (c) 2024
 * 
 */

#include "Playlist.hpp"

Playlist::Playlist(){
    root_ptr_ = nullptr;
}

Playlist::Playlist(const Playlist& other){
    root_ptr_ = copyTree(other.root_ptr_);
}

Playlist::Playlist(Playlist&& other){
    root_ptr_ = other.root_ptr_;
    other.root_ptr_.reset();
}

Playlist::~Playlist(){
    clear();
}

Playlist& Playlist::operator=(const Playlist& other){
    // Check to see if it isn't calling itself
    if (this != &other){
        clear();
        root_ptr_ = copyTree(other.root_ptr_);
    }
    return *this;
}

Playlist& Playlist::operator=(Playlist&& other){
    if (this != &other){
        clear();
        root_ptr_ = other.root_ptr_;
        other.root_ptr_.reset();
    }
    return *this;
}

bool Playlist::isEmpty() const{
    return root_ptr_ == nullptr;
}

size_t Playlist::getHeight() const{
    return getHeightHelper(root_ptr_);
}

size_t Playlist::getNumberOfSongs() const{
    return getSongsHelper(root_ptr_);
}

bool Playlist::add(const std::string& song, const std::string& artist){
    auto new_node_ptr = std::make_shared<SongNode>(song,artist);
    root_ptr_ = placeNode(root_ptr_, new_node_ptr);
    return true;
}

bool Playlist::remove(const std::string& song, const std::string& artist) {
    bool is_successful = false;
    root_ptr_ = removeValue(root_ptr_, song, artist, is_successful);
    return is_successful;
}

bool Playlist::search(const std::string& name, const std::string& artist) const{
    std::string key = getKey(name, artist);
    return searchHelper(root_ptr_, key);
}

void Playlist::clear(){
    destroyTree(root_ptr_);
    root_ptr_.reset();
}

std::vector<SongNode> Playlist::preorderTraverse() const{
    std::vector<SongNode> result;
    preorderHelper(root_ptr_,result);
    return result;
}

std::vector<SongNode> Playlist::inorderTraverse() const{
    std::vector<SongNode> result;
    inorderHelper(root_ptr_,result);
    return result;
}

std::vector<SongNode> Playlist::postorderTraverse() const{
    std::vector<SongNode> result;
    postorderHelper(root_ptr_,result);
    return result;
}

std::shared_ptr<SongNode> Playlist::removeValue(std::shared_ptr<SongNode> sub_tree, const std::string& song, const std::string& artist, bool& success) {
    // If subtree is empty, set success flag to false and return nullptr
    if (sub_tree == nullptr) {
        success = false;
        return sub_tree;
    }
    // If the current node matches the song and artist, remove the node and set success flag to true
    if (getKey(*sub_tree) == getKey(song,artist)) {
        sub_tree = removeNode(sub_tree);
        success = true;
        return sub_tree;
    }
    // Recursively search in the left subtree if the current node key is greater than the target song and artist
    if (getKey(*sub_tree) > getKey(song,artist)) {
        sub_tree -> left_ = removeValue(sub_tree -> left_, song, artist, success);
    }
    // Recursively search in the right subtree if the current node key is less than the target song and artist
    else {
        sub_tree -> right_ = removeValue(sub_tree -> right_, song, artist, success);
    }
    return sub_tree;
}

std::shared_ptr<SongNode> Playlist::removeNode(std::shared_ptr<SongNode> node_ptr) {
    // If the node is a leaf node, reset it and return nullptr
    if (node_ptr->isLeaf()) {
        node_ptr.reset();
        return node_ptr;
    }
    // If the left child is nullptr, return the right child
    else if (node_ptr -> left_ == nullptr) {
        return node_ptr -> right_;
    }
    // If the right child is nullptr, return the left child
    else if (node_ptr -> right_ == nullptr) {
        return node_ptr -> left_;
    }
    // If there are two children, find the leftmost node in the right subtree and replace the current node
    std::string inorder_song;
    std::string inorder_artist;
    node_ptr -> right_ = removeLeftmostNode(node_ptr -> right_, inorder_song, inorder_artist);
    node_ptr -> song_ = inorder_song;
    node_ptr -> artist_ = inorder_artist;
    return node_ptr;
}

std::shared_ptr<SongNode> Playlist::removeLeftmostNode(std::shared_ptr<SongNode> node_ptr, std::string& inorder_song, std::string& inorder_artist) {
    // If the left child is nullptr, store the song and artist, remove the current node
    if (node_ptr -> left_ == nullptr) {
        inorder_song = node_ptr -> song_;
        inorder_artist = node_ptr -> artist_;
        return removeNode(node_ptr);
    }
    // Recursively search for the leftmost node
    node_ptr -> left_ = removeLeftmostNode(node_ptr -> left_, inorder_song, inorder_artist);
    return node_ptr;
}

void Playlist::preorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const {
    // If node is not nullptr, add the node in the result vector following preorder traversal
    if (node_ptr != nullptr) {
        result.push_back(*node_ptr);
        preorderHelper(node_ptr -> left_, result);
        preorderHelper(node_ptr -> right_, result);
    }
}

void Playlist::inorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const {
    // If node is not nullptr, add the node in the result vector following inorder traversal
    if (node_ptr != nullptr) {
        inorderHelper(node_ptr -> left_, result);
        result.push_back(*node_ptr);
        inorderHelper(node_ptr -> right_, result);
    }
}

void Playlist::postorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const {
    // If node is not nullptr, add the node in the result vector following postorder traversal
    if (node_ptr != nullptr) {
        postorderHelper(node_ptr -> left_, result);
        postorderHelper(node_ptr -> right_, result);
        result.push_back(*node_ptr);
    }
}
std::string Playlist::getKey(const std::string& song, const std::string& artist) const {
    return song+artist;
}

std::string Playlist::getKey(const SongNode& song) const {
    return song.song_+song.artist_;
}

void Playlist::destroyTree(std::shared_ptr<SongNode> sub_tree_ptr){
    // postorder deletion of every node in the tree
    if (sub_tree_ptr != nullptr) {
        destroyTree(sub_tree_ptr->left_);
        destroyTree(sub_tree_ptr->right_);
        sub_tree_ptr.reset();
    }
}

std::shared_ptr<SongNode> Playlist::placeNode(std::shared_ptr<SongNode> subtree_ptr, std::shared_ptr<SongNode> new_node_ptr){
    // root becomes the new_node_ptr if root is nullptr
    if (subtree_ptr == nullptr) {
        return new_node_ptr;
    }
    // place node to the left subtree if node is less than or equal to root item
    if (getKey(*subtree_ptr) > getKey(*new_node_ptr)) {
        subtree_ptr -> left_ = placeNode(subtree_ptr->left_, new_node_ptr);
    }
    // place node to the right subtree if node is greater than root item
    else {
        subtree_ptr -> right_ = placeNode(subtree_ptr->right_, new_node_ptr);
    }
    return subtree_ptr;

}

size_t Playlist::getHeightHelper(std::shared_ptr<SongNode> sub_tree_ptr) const{
    if (sub_tree_ptr == nullptr) {
        return 0;
    }
    return 1 + std::max(getHeightHelper(sub_tree_ptr->left_), getHeightHelper(sub_tree_ptr->right_));
}

size_t Playlist::getSongsHelper(std::shared_ptr<SongNode> sub_tree_ptr) const{
    if (sub_tree_ptr == nullptr){
        return 0;
    }
    // Count every time a node is accessed
    return 1 + getSongsHelper(sub_tree_ptr->left_) + getSongsHelper(sub_tree_ptr->right_);
}


bool Playlist::searchHelper(std::shared_ptr<SongNode> sub_tree_ptr, const std::string& key) const{
    if (sub_tree_ptr == nullptr) return false;
    // True if key matches key of subnode
    if (key == getKey(*sub_tree_ptr)) return true;
    // Go to left subtree if key is less than the subtree key
    if (key < getKey(*sub_tree_ptr)) return searchHelper(sub_tree_ptr->left_, key);
    // Go to right subtree if key is greater
    return searchHelper(sub_tree_ptr->right_, key);
}

std::shared_ptr<SongNode> Playlist::copyTree(const std::shared_ptr<SongNode> old_tree_root_ptr) const{
    std::shared_ptr<SongNode> new_tree_ptr;
    // if node we are copying is not nullptr
    if (old_tree_root_ptr != nullptr) {
        // copy the item of the old_tree_root_ptr into a new node
        new_tree_ptr = std::make_shared<SongNode>(old_tree_root_ptr -> song_, old_tree_root_ptr -> artist_);
        // copy the left and right subtree
        new_tree_ptr -> left_ = copyTree(old_tree_root_ptr -> left_);
        new_tree_ptr -> right_ = copyTree(old_tree_root_ptr -> right_);
    }
    return new_tree_ptr;   
}
