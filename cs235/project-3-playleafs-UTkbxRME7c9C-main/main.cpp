#include "Playlist.hpp"

void printVector(const std::vector<SongNode>& list) {
    int i = 0;
    for (const auto& item : list) {
        std::cout << i << ": " << item.song_ << " by " << item.artist_ << std::endl;
        i++;
    }
}

int main() {
    // Init list
    Playlist list;
    
    std::string sname[5] = {"The Party Line", "casino night", "Perfect Circle", "Pillar of Anomalies", "Force majeure"};
    std::string aname[5] = {"SAINT PEPSI" , "pilotredsun", "Nujabes", "Brandon McKagan", "Gaspard Auge"}; 
    //  Add 5 songs to the list
    list.add(sname[0],aname[0]);
    list.add(sname[1],aname[1]);
    list.add(sname[2],aname[2]);
    list.add(sname[3],aname[3]);
    list.add(sname[4],aname[4]);

    // Test getters
    std::cout << "Number of songs: " << list.getNumberOfSongs() << std::endl;
    std::cout << "Height of playlist tree: " << list.getHeight() << std::endl;
    std::cout << "Is playlist empty? " << (list.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << std::endl;

    // Test if all songs can be searched
    if (list.search(sname[0],aname[0])) std::cout << "Song 1 found" << std::endl;
    if (list.search(sname[1],aname[1])) std::cout << "Song 2 found" << std::endl;
    if (list.search(sname[2],aname[2])) std::cout << "Song 3 found" << std::endl;
    if (list.search(sname[3],aname[3])) std::cout << "Song 4 found" << std::endl;
    if (list.search(sname[4],aname[4])) std::cout << "Song 5 found" << std::endl;
    if (list.search("asdasd","asdasda")) std::cout << "Nonexistant song found??" << std::endl;
    std::cout << std::endl;
    
    // Traversals
    std::cout << "Preorder traversal:" << std::endl;
    printVector(list.preorderTraverse());
    std::cout << "Ineorder traversal:" << std::endl;
    printVector(list.inorderTraverse());
    std::cout << "Postorder traversal:" << std::endl;
    printVector(list.postorderTraverse());
    std::cout << std::endl;

    // Remove a song
    list.remove(sname[3],aname[3]);
    std::cout << "Number of songs after removal: " << list.getNumberOfSongs() << std::endl;
    std::cout << "Preorder traversal after removal:" << std::endl;
    printVector(list.preorderTraverse());
    std::cout << std::endl;

    // Testing copy
    Playlist listcpy(list);
    std::cout << "Number of songs in copy constructor: " << listcpy.getNumberOfSongs() << std::endl;
    std::cout << "Preorder traversal of copy constructor:" << std::endl;
    printVector(listcpy.preorderTraverse());
    Playlist listcpy2;
    listcpy2.add("If u see this", "It aint workin");
    listcpy2 = list;
    std::cout << "Number of songs in copy assignment: " << listcpy2.getNumberOfSongs() << std::endl;
    std::cout << "Preorder traversal of copy assignment:" << std::endl;
    printVector(listcpy2.preorderTraverse());
    std::cout << std::endl;

    // Testing clear
    list.clear();
    std::cout << "Number of songs after clearing: " << list.getNumberOfSongs() << std::endl;
    std::cout << "Is playlist empty after clearing? " << (list.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << std::endl;

    // Testing move
    Playlist listmv(std::move(listcpy2));
    std::cout << "Number of songs of moved list: " << listcpy2.getNumberOfSongs() << std::endl;
    std::cout << "Number of songs in move constructor: " << listmv.getNumberOfSongs() << std::endl;
    std::cout << "Preorder traversal of move constructor:" << std::endl;
    printVector(listmv.preorderTraverse());
    listcpy.add("If u see this", "It aint workin");
    listcpy = std::move(listmv);
    std::cout << "Number of songs of moved list: " << listmv.getNumberOfSongs() << std::endl;
    std::cout << "Number of songs in move assignment: " << listcpy.getNumberOfSongs() << std::endl;
    std::cout << "Preorder traversal of move assignment:" << std::endl;
    printVector(listcpy.preorderTraverse());
    return 0;
}

