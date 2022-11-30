#include <iostream>

#include "SegTree.h"

int SegmentTree::getDecks() {
    std::cin >> num_decks;
    return num_decks;
}

void SegmentTree::fill_initialA() {
    num_cards = num_decks * 4;
    for(int i = 0; i < 13; i++){
        initial_array[i] = num_cards;
    }
}

void SegmentTree::fill_initialS() {
    for(int i = 0; i < 32; i++){
        segment_tree[i] = 0;
    }
}

void SegmentTree::create_segTree(int start, int end, int current) {
    //std::cout << "[" << start << ":" << end << "]" <<  " " << current << std::endl;

    if (start == end){
        segment_tree[current] = initial_array[start];
        return;
    }

    else{
        int left_end = (start + end)/2;
        int right_start = ((start + end)/2) + 1;
        int leftNext_current = (current*2) ;
        int rightNext_current = (current*2) + 1;
        create_segTree(start, left_end, leftNext_current);
        create_segTree(right_start, end, rightNext_current);
        segment_tree[current] = segment_tree[leftNext_current] + segment_tree[rightNext_current];

    }

}

int SegmentTree::findSegSum(int start, int end, int current, int lSeg, int rSeg){
    //std::cout << "[" << start << ":" << end << "]" <<  " " << current << std::endl;


    if (lSeg <= start && end <= rSeg){
        return segment_tree[current];
    }
    else if (rSeg < start || end < lSeg){
        return 0;
    }
    else {
        int left_end = (start + end) / 2;
        int right_start = ((start + end) / 2) + 1;
        int leftNext_current = (current * 2);
        int rightNext_current = (current * 2) + 1;
        return findSegSum(start, left_end, leftNext_current, lSeg, rSeg) +
               findSegSum(right_start, end, rightNext_current, lSeg, rSeg);
    }
}












