#include <iostream>
#include <fstream>
#include <string>

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

void SegmentTree::create_segTree(int i, int left, int right) {
    int iSum;
    int leftSum;
    int rightSum;

    if (i > 32){
        return ;
    }
    if (left == right){
        return;
    }
    if (i == 1) {
        iSum = sum(left, right);
        segment_tree[i] = iSum;
        leftSum = sum(left, (left+right)/2);
        //std::cout << "LeftSum:" << leftSum;
        rightSum = sum((left+right)/2 + 1, right );
        //std::cout << "RightSum:" << rightSum;
        segment_tree[i*2] = leftSum;
        segment_tree[2*i+1] = rightSum;
    }
    else{
        leftSum = sum(left, (left+right)/2);
        //std::cout << "LeftSum:" << leftSum;
        rightSum = sum((left+right)/2 + 1, right );
        //std::cout << "RightSum:" << rightSum;
        segment_tree[i*2] = leftSum;
        segment_tree[2*i+1] = rightSum;
    }

    create_segTree(i*2, left, ((left+right)/2) );
    create_segTree(2*i+1, ((left+right)/2)+1, right);



}


int SegmentTree::sum(int left, int right) {
    int iSum = 0;
    for (int i = left; i <= right; i++){
        iSum += initial_array[i];
    }
    return iSum;
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
    //std::cout << "count: " << COUNT << std::endl;
    create_segTree(1, 0, 12);
    segSum = findSegSum(start,end, current,(COUNT) ,12);
    double test1 = double(segSum);
    double test2 = double(segment_tree[1]);
    std::cout << "The dealer has " << segSum << " cards that are better than yours out of " << segment_tree[1] << std::endl;
    //std::cout << segment_tree[1] << std::endl;
    double prob = ((test1/test2) * 100);
    outputGraph("outfile");
    std::cout << "The chances of the dealer having a better card than you on the next turn is " << prob << "%" << std::endl ;
}

void SegmentTree::outputGraph(std::string fname){
    std::ofstream of(fname +"_default.dot");

    of << "digraph G {\n" << std::endl;
    for(int i = 1; i < 32; i++){
        std::string total;
        std::string totalLNext;
        std::string node;
        std::string nodeLNext;
        std::string nodeRNext;
        std::string totalRNext;

        if ((i*2) > 32 || (2*i)+1 > 32){
            break;
        }

        if (i == 1){
            node = std::to_string(i) + ": ";
        }
        else if (i%2 == 0){
            node = std::to_string(i) + ": ";
        }

        else {
            node = std::to_string(i) + ": ";
        }

        if ((i*2)%2 == 0){
            nodeLNext = std::to_string(i*2) + ": " ;
        }

        else {
            nodeRNext = std::to_string(i*2) + ": ";
        }
        if ((2*i+1)%2 == 0){
            nodeLNext = std::to_string(2*i+1) + ": ";
        }

        else {
            nodeRNext = std::to_string(2*i+1) + ": ";
        }



        total += node;
        total += std::to_string(segment_tree[i]);

        totalLNext += nodeLNext;
        totalLNext += std::to_string(segment_tree[2*i]);

        totalRNext += nodeRNext;
        totalRNext += std::to_string(segment_tree[2*i+1]);


        of  << "\""<< total << "\"" <<  " -> " << "\"" << totalLNext << "\"" << ";" << std::endl;
        of << "\"" << total << "\"" << " -> " << "\"" << totalRNext << "\"" << ";" << std::endl;

    }

    of << "\n}";
}

















