#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SegTree.h"

//function that fills the initial array that contains the amount of cards there are in 8 decks (the standard for Blackjack)
void SegmentTree::fill_initialA() {

    num_cards = 32;

    for (int i = 0; i < 13; i++) {
        initial_array[i] = num_cards;
    }
}

//Function that fills the initial segment tree array with all zeros, the size is 4 times the card value array
void SegmentTree::fill_initialS() {
    for (int i = 0; i < (13 * 4); i++) {
        segment_tree[i] = 0;
    }
}

//This function fills in the segment tree array recursively using i as a node counter, left as the left most index in the initial array and right as the right
//most index in the initial array
void SegmentTree::create_segTree(int i, int left, int right) {
    int iSum;
    int leftSum;
    int rightSum;

    //checks if the node is out of bounds of the segment tree and returns nothing
    if (i > 32) {
        return;
    }

    //if the left most and right most index equal each other the function returns nothing because the sum at the current node is the number at that index
    if (left == right) {
        return;
    }

    //if the node is one, the sum at the node one is the sum of the whole initial array

    if (i == 1) {
        iSum = sum(left, right);
        segment_tree[i] = iSum;

        //After node one is filled, the code breaks into left and right children and fills in sums
        //using updated left most and right most indexes
        leftSum = sum(left, (left + right) / 2);
        rightSum = sum((left + right) / 2 + 1, right);

        //Node one's children then get filled in with new sums
        segment_tree[i * 2] = leftSum;
        segment_tree[2 * i + 1] = rightSum;
    }

    //if the node is not 1, just the 2 child node's gets filled in with their respective sums
    else {
        leftSum = sum(left, (left + right) / 2);
        rightSum = sum((left + right) / 2 + 1, right);

        segment_tree[i * 2] = leftSum;
        segment_tree[2 * i + 1] = rightSum;
    }

    //recursive call that continuously splits array using equations that update nodes and left and right most index until base case is reached
    create_segTree(i * 2, left, ((left + right) / 2));
    create_segTree(2 * i + 1, ((left + right) / 2) + 1, right);



}

//function that gets sum of ranges from initial array used in create_SegTree function
int SegmentTree::sum(int left, int right) {
    int iSum = 0;
    for (int i = left; i <= right; i++) {
        iSum += initial_array[i];
    }
    return iSum;
}

int SegmentTree::findSegSum(int start, int end, int current, int lSeg, int rSeg) {
    //std::cout << std::endl;
    //std::cout << "[" << start << ":" << end << "]" <<  " node:" << current << " value:" << segment_tree[current];

    //check if the given index range from lSeg to rSeg is contained within the start and end indexes
    if (lSeg <= start && rSeg >= end) {

        //returns the value at the current node
        return segment_tree[current];
    }

    //if base case does not go through, check to see if the given index range is out of bounds of the start and end indexes
    else if (rSeg < start || lSeg > end) {
        return 0;
    }

    //
    else {

        //defines new parameters using equations from create_SegTree
        int left_end = (start + end) / 2;
        int right_start = ((start + end) / 2) + 1;
        int leftNext_current = (current * 2);
        int rightNext_current = (current * 2) + 1;

        //recursive call that splits tree into left and right using new definitions
        //returns when base cases are met and the left and right are added together
        return findSegSum(start, left_end, leftNext_current, lSeg, rSeg) +
            findSegSum(right_start, end, rightNext_current, lSeg, rSeg);
    }

}

//function to find the probability of the dealer having a better hand than you
void SegmentTree::probOfDealerBetter(int usersvalue, int dealersvalue) {
    int values[13] = { 2,3,4,5,6,7,8,9,10,10,10,10,11 };
    bool lowestcardthatbeatsuser = true;
    int COUNT = 0;
    //finds how much higher your count is than the dealers count
    int differencebetweendealeranduser = usersvalue - dealersvalue;
    //creates the starting point of the segment tree sum
    if (differencebetweendealeranduser < 2)
    {
        differencebetweendealeranduser = 2;
    }
    //finds the starting index of the cards in range
    while (lowestcardthatbeatsuser)
    {
        if (values[COUNT] >= differencebetweendealeranduser)
            lowestcardthatbeatsuser = false;
        else
            COUNT++;
    }
    create_segTree(1, 0, 12);
    //finds the sum of cards in the range needed for the dealer to beat your count
    segSum = findSegSum(start, end, current, (COUNT), 12);
    double test1 = double(segSum);
    double test2 = double(segment_tree[1]);
    //finds the probability of the dealer having a card to beat your count
    double prob = ((test1 / test2) * 100);
    outputGraph("outfile");
    std::cout << "The chances of the dealer having a better card than you on the next turn is " << prob << "%" << std::endl;
}

//function to find the probability of the you not going over 21
void SegmentTree::probOfNotGoingOver21(int usersvalue){


    int difference;
    int sum;
    double test1;
    double test2;
    double prob;

    //finds the highest card value that wouldn't bust
    difference = 21 - usersvalue;
    create_segTree(1, 0, 12);

    //if 1 is the only count then ace is the only card to not bust your count
    if(difference == 1){
        sum = findSegSum(start, end, current, 12, 12);
        test1 = double(sum);
        test2 = double(segment_tree[1]);
        prob = ((test1 / test2) * 100);
    }
    //if your difference is higher than 11 then all of the cards would make you not bust
    else if(difference >= 10){
        sum = findSegSum(start, end, current, 0, 12);
        test1 = double(sum);
        test2 = double(segment_tree[1]);
        prob = ((test1 / test2) * 100);
    }
    //if your cards are between 1 and 11 then this will call our findSegSum function to find the sum of cards that won't bust
    else {
        sum = findSegSum(start, end, current, 0, difference-2) + findSegSum(start, end, current, 12, 12) ;
        test1 = double(sum);
        test2 = double(segment_tree[1]);
        prob = ((test1 / test2) * 100);
    }

    std::cout << "The chances of not going over 21 are: " << prob << "%" << std::endl;


}

void SegmentTree::proboffavor_hand(int uservalue){
    std::vector<int> tempval;
    int values[13] = { 2,3,4,5,6,7,8,9,10,10,10,10,11 };
    int sum;
    double test1;
    double test2;
    double prob;

    //for loop to find cards that are valid
    for(int i = 0; i < 13; i ++){
        int test_score = 0;
        test_score = values[i];
        if((test_score + uservalue) == 17 or (test_score + uservalue) == 18 or (test_score + uservalue) == 19 or (test_score + uservalue) == 20 or (test_score + uservalue) == 21){
            tempval.push_back(test_score);
        }

    }

    //scenario where no cards are valid
    int size = tempval.size();
    if(size == 0){
        sum = 0;
        test1 = 0;

    }
    //traveses the segment tree
    if(size != 0){
        int tempstart = tempval[0];
        int tempend = tempval[size - 1];
        create_segTree(1,0,12);
        sum = findSegSum(start , end, current,tempstart, tempend);
    }

    test1 = double(sum);
    test2 = double(segment_tree[1]);
    prob = ((test1/test2) * 100);

    //print statements
    std::cout << "The chances of having a favorable hand are ";
    std::cout << prob;
    std::cout << "%" << std::endl;
}

//Function that creates DOT visualization file
void SegmentTree::outputGraph(std::string fname) {
    std::ofstream of(fname + "_default.dot");

    of << "digraph G {\n" << std::endl;

    //loop through segment tree array
    for (int i = 1; i < 32; i++) {
        std::string total;
        std::string totalLNext;
        std::string node;
        std::string nodeLNext;
        std::string nodeRNext;
        std::string totalRNext;

        //checks if node's children (i) are out of segment tree and breaks
        if ((i * 2) > 32 || (2 * i) + 1 > 32) {
            break;
        }

        //checks if node is 1, 2 or 3 and converts node number to string
        if (i == 1) {
            node = std::to_string(i) + ": ";
        }

        else if (i % 2 == 0) {
            node = std::to_string(i) + ": ";
        }

        else {
            node = std::to_string(i) + ": ";
        }

        //checks if the current left node's (i) children are even or odd, if it is even the next node is left
        //if not the next node goes to the right
        if ((i * 2) % 2 == 0) {
            nodeLNext = std::to_string(i * 2) + ": ";
        }

        else {
            nodeRNext = std::to_string(i * 2) + ": ";
        }

        //checks if the current right node's (i) children are even or odd, if it is even the next node is left
        //if not the next node goes to the right
        if ((2 * i + 1) % 2 == 0) {
            nodeLNext = std::to_string(2 * i + 1) + ": ";
        }

        else {
            nodeRNext = std::to_string(2 * i + 1) + ": ";
        }


        //adds the node number and value at that node to the current total string
        total += node;
        total += std::to_string(segment_tree[i]);

        //adds the node number of the left node and the value at that left node to the next node string
        totalLNext += nodeLNext;
        totalLNext += std::to_string(segment_tree[2 * i]);

        //adds the node number of the right node and the value at that right node to the next node string
        totalRNext += nodeRNext;
        totalRNext += std::to_string(segment_tree[2 * i + 1]);

        //prints the total string twice with both of it's children into the outfile
        of << "\"" << total << "\"" << " -> " << "\"" << totalLNext << "\"" << ";" << std::endl;
        of << "\"" << total << "\"" << " -> " << "\"" << totalRNext << "\"" << ";" << std::endl;

    }

    of << "\n}";
}