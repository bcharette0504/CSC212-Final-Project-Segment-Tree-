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
    std::cout << "[" << start << ":" << end << "]" <<  " " << current << std::endl;


    if (start == end){
        segment_tree[current] = initial_array[start];
        return;
    }


    else{
        int left_current;
        int right_current;
        int left_end = (start + end)/2;
        int right_start = ((start + end)/2) + 1;

        if (current*2 >= 24){
            if(current*2 == 24){
                left_current = (2*current - 2);
                right_current = (2*current - 2)  + 1;
            }
            else{
                left_current = (2*current - (2*current - 24));
                right_current = (2*current - (2*current - 24)) + 1;
            }

        }
        else {
            left_current = (current*2) ;
            right_current = (current*2) + 1;
        }
        create_segTree(start, left_end, left_current);
        create_segTree(right_start, end, right_current);
        segment_tree[current] = segment_tree[left_current] + segment_tree[right_current];

    }

}










