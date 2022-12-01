#include <iostream>

#include "SegTree.h"

int SegmentTree::getDecks() {
    std::cin >> num_decks;
    return num_decks;
}

void SegmentTree::fill_initialA() {
    num_cards = 32;
    for(int i = 0; i < 13; i++){
        initial_array[i] = num_cards;
    }
}

void SegmentTree::fill_initialS() {
    for(int i = 0; i < (13*4); i++){
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
    //std::cout << std::endl;
    //std::cout << "[" << start << ":" << end << "]" <<  " node:" << current << " value:" << segment_tree[current];

    //check if the current node contains
    if (lSeg <= start && rSeg >= end) {
        //std::cout << " returns";
        return segment_tree[current];
    }

    else if (rSeg < start || lSeg > end) {
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

void SegmentTree :: probOfDealerBetter(int usersvalue, int dealersvalue){
    int values[13] = { 2,3,4,5,6,7,8,9,10,10,10,10,11 };
    bool lowestcardthatbeatsuser = true;
    int COUNT = 0;
    int differencebetweendealeranduser = usersvalue - dealersvalue;
    while (lowestcardthatbeatsuser)
    {
        if (values[COUNT] == differencebetweendealeranduser)
            lowestcardthatbeatsuser = false;
        else
            COUNT++;
    }
    std::cout << "count: " << COUNT << std::endl;
    create_segTree(start,end, current);
    segSum = findSegSum(start,end, current,(COUNT) ,12);
    double test1 = double(segSum);
    double test2 = double(segment_tree[1]);
    std::cout << segSum << std::endl;
    std::cout << segment_tree[1] << std::endl;
    double prob = ((test1/test2) * 100);
    std::cout << "The chances of the dealer having a better card than you on the next turn is " << prob << "%" ;
}














