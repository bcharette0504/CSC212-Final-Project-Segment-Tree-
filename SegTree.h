#include <iostream>
#include <string>

class SegmentTree {
public:
    int num_decks;
    int num_cards;
    int size;
    int initial_array[13];
    int segment_tree[13*4];
    int start;
    int end;
    int current;
    int lSeg;
    int rSeg;
    int segSum;




    void create_segTree(int i, int left, int right);
    int findSegSum(int start, int end, int current, int lSeg, int rSeg);
    void probOfDealerBetter(int usersvalue, int dealersvalue);
    void outputGraph(std::string fname);
    int getDecks();
    void fill_initialA();
    void fill_initialS();
    int sum(int left, int right);

};