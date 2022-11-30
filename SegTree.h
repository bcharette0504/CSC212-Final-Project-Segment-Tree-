#include <iostream>

class SegmentTree {
public:
    int num_decks;
    int num_cards;
    int initial_array[13];
    int segment_tree[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0, 0, 0, 0,0};
    int start;
    int end;
    int current;




    void create_segTree(int start, int end, int current);
    int getDecks();
    void fill_initial();

};
