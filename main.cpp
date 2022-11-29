#include <iostream>
#include "SegTree.h"

int main() {

    SegmentTree myTree;
    std::cout << "How many decks are you playing with?" << std::endl;
    myTree.num_decks = myTree.getDecks();
    std::cout << std::endl;
    myTree.fill_initial();
    myTree.start = 0;
    myTree.end = 12;
    myTree.current = 1;
    myTree.create_segTree(myTree.start, myTree.end, myTree.current);

    for(int i = 0; i < 13; i++){
        std::cout << myTree.initial_array[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < 26; i++){
        std::cout << myTree.segment_tree[i] << " ";
    }


}
