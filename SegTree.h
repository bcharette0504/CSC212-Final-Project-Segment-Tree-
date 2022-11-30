#include <iostream>

class SegmentTree {
public:
    int num_decks;
    int num_cards;
    int initial_array[13];
    int segment_tree[32];
    int start;
    int end;
    int current;
    int lSeg;
    int rSeg;
    int segSum;




    void create_segTree(int start, int end, int current);
    int findSegSum(int start, int end, int current, int lSeg, int rSeg);
    int getDecks();
    void fill_initialA();
    void fill_initialS();

};
