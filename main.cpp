#include <iostream>
#include "SegTree.h"

int main() {

    SegmentTree myTree;
    myTree.size = 13;
    std::cout << "How many decks are you playing with?" << std::endl;
    myTree.num_decks = myTree.getDecks();
    std::cout << std::endl;
    myTree.fill_initialA();
    myTree.fill_initialS();
    myTree.start = 0;
    myTree.end = 12;
    myTree.current = 1;

    myTree.create_segTree(myTree.start, myTree.end, myTree.current);
    /*for(int i = 0; i < 13; i++){
        std::cout << myTree.initial_array[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < 32; i++){
        std::cout << myTree.segment_tree[i] << " ";
    }*/
    std::cout << "Input range you would like to find: " << std::endl;
    std::cin >> myTree.lSeg >> myTree.rSeg;
    myTree.segSum = myTree.findSegSum(myTree.start, myTree.end, myTree.current, myTree.lSeg, myTree.rSeg);

    std::cout << std::endl;
    std::cout << "Sum = " << myTree.segSum ;

}
