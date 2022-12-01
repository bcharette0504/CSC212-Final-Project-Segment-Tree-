// BlackJack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SegTree.h"
#include <string>
#include <random>
#include <vector>



void check_values(int dealersvalue, int usersvalue)
{
if (dealersvalue > 21)
{
 std::cout << "Won \n";
}
else if (dealersvalue > usersvalue)
{
 std::cout << "Lost \n";
}
else if ((dealersvalue == usersvalue))
{
 std::cout << "Pushed \n";

}
else if ((dealersvalue < usersvalue))
{
 std::cout << "Won \n";
}
}

int drawcard(std::vector<std::string>& Yourcards, std::string cards[13], int Cards[13])
{
bool check = false;
for (int i = 0; i < 13; i++)
{
 if (Cards[i] != 0)
 {
     check = true;
     break;
 }
}
if (check == false)
{
 return(999);
}
while (check)
{
 int temp = rand() % 13;
 if (Cards[temp] != 0)
 {
     Cards[temp] = Cards[temp] - 1;
     return(temp);
     check = false;
 }
}
}
int main()
{
SegmentTree myTree;
std::string cards[13] = { "2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace" };
int values[13] = { 2,3,4,5,6,7,8,9,10,10,10,10,11 };
myTree.size = 13;
myTree.start = 0;
myTree.end = 12;
myTree.current = 1;
myTree.fill_initialA();
myTree.fill_initialS();

//myTree.create_segTree(myTree.start, myTree.end, myTree.current);
std::cout << myTree.segment_tree[1] << std::endl;
bool Continue = true;
int ct = 0;
while (Continue)
{
 int dealersvalue = 0;
 std::vector<std::string> Yourcards;
 std::vector<std::string> Dealerscards;
 for (int i = 0; i < 1; i++) {
     int newcard = drawcard(Yourcards, cards, myTree.initial_array);
     if (newcard == 999) {
         std::cout << "QUIT";
         Continue = false;
         break;
     }
     else {
         dealersvalue = dealersvalue + values[newcard];
         Dealerscards.push_back(cards[newcard]);
     }
 }
 int usersvalue = 0;
 std::cout << "The dealers first card is " << Dealerscards[0] << "\n";
 std::cout << "Your Cards are: \n";
 for (int i = 0; i < 2; i++)
 {
     int newcard = drawcard(Yourcards, cards, myTree.initial_array);
     if (newcard == 999) {
         std::cout << "QUIT";
         Continue = false;
         break;
     }
     else
     {
         usersvalue = usersvalue + values[newcard];
         std::cout << cards[newcard] << "\n";
         Yourcards.push_back(cards[newcard]);
     }

 }
 bool newcheck = true;
 std::string userinput;
 std::cout << "Would you like to stand or would you like to hit you have: " << usersvalue << "\n";
 /*bool lowestcardthatbeatsuser = true;
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
 myTree.create_segTree(myTree.start,myTree.end, myTree.current);
 myTree.segSum = myTree.findSegSum(myTree.start,myTree.end, myTree.current,(COUNT) ,12);
 double test1 = double(myTree.segSum);
 double test2 = double(myTree.segment_tree[1]);
 std::cout << myTree.segSum << std::endl;
 std::cout << myTree.segment_tree[1] << std::endl;
 double prob = ((test1/test2) * 100);
 std::cout << "The chances of the dealer having a better card than you on the next turn is " << prob << "%" ;*/
        /*for (int i = 0; i < 13; i++){
            std::cout << myTree.initial_array[i] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < 13*4; i++){
            std::cout << myTree.segment_tree[i] << " ";
        }*/
        myTree.probOfDealerBetter(usersvalue,dealersvalue);
        std::cout << std::endl;
        std::cin >> userinput;
        if (userinput == "stand") {
            bool newnewcheck = true;
            while (newnewcheck)
            {
                int newcard = drawcard(Yourcards, cards, myTree.initial_array);
                if (newcard == 999) {
                    std::cout << "QUIT";
                    Continue = false;
                    break;
                }
                else {
                    dealersvalue = dealersvalue + values[newcard];
                    Dealerscards.push_back(cards[newcard]);
                    if (dealersvalue >= 16)
                    {
                        newnewcheck = false;
                        break;
                    }
                }


            }
            std::cout << "the dealer has: " ;
            for (int x = 0; x < Dealerscards.size(); x++)
            {
                std::cout << Dealerscards[x] << " ";
            }
            std::cout << "  for a value of " << dealersvalue  << ". Therefore, you ";
            check_values(dealersvalue, usersvalue);
        }
        if (userinput == "hit")
        {
            bool continuehit = true;
            while (continuehit)
            {
                int newcard = drawcard(Yourcards, cards, myTree.initial_array);
                if (newcard == 999) {
                    std::cout << "QUIT";
                    Continue = false;
                    break;
                }
                else {
                    usersvalue = usersvalue + values[newcard];
                    Yourcards.push_back(cards[newcard]);
                    std::cout << "Your new card is " << cards[newcard] << ". So your new total is: " << usersvalue << "\n";
                    myTree.probOfDealerBetter(usersvalue,dealersvalue);
                    if (usersvalue > 21)
                    {
                        std::cout << "Sorry but you lost\n";
                        break;
                    }
                    std::cout << "\n Stand or Hit? \n";
                    std::string hitagain;
                    std::cin >> hitagain;
                    if (hitagain == "stand")
                    {
                        continuehit = false;
                        check_values(dealersvalue, usersvalue);
                    }
                    if (hitagain == "Hit")
                    {
                        std::cout << "Ok here we go!\n";
                    }
                }


            }
        }
    }
}
