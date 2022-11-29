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

    if (start == end){
        segment_tree[current] = initial_array[start];
    }

    else{
        create_segTree(start, ((start + end)/2), current*2);
        create_segTree((((start + end)/2)+1), end, 2*current+1);
        segment_tree[current] = segment_tree[current*2] + segment_tree[2*current+1];
    }


}

