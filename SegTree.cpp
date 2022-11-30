#include <iostream>

#include "SegTree.h"

int SegmentTree::getDecks() {
    std::cin >> num_decks;
    return num_decks;
}

void SegmentTree::fill_initial() {
    num_cards = num_decks * 4;
    for(int i = 0; i < 13; i++){
        initial_array[i] = num_cards;
    }




}

void SegmentTree::create_segTree(int start, int end, int current) {

    /*std::cout << std::endl;
    std::cout << "[" << start << ":" << end << "]" <<  " " << current << std::endl;*/
    //std::cout << std::endl;

    if (start == end){
        segment_tree[current] = initial_array[start];
        return;
    }


    else{
        int left_end = (start + end)/2;
        int right_start = ((start + end)/2) + 1;
        int left_current = (current*2) + 1;
        int right_current = (current*2) + 2;
        create_segTree(start, left_end, left_current);
        create_segTree(right_start, end, right_current);
        segment_tree[current] = segment_tree[left_current] + segment_tree[right_current];

    }

}






