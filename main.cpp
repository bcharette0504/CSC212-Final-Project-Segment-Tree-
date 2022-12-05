#include <iostream>
#include "SegTree.h"
#include <string>
#include <random>
#include <vector>


void IfAce()
{


}
void check_values(int dealersvalue, int usersvalue)
{
    if (dealersvalue > 21)
    {
        std::cout << "The dealer has gone over 21: ";
        std::cout << "Won \n";
    }
    else if (dealersvalue > usersvalue)
    {
        std::cout << "The dealer's cards are higher than yours: ";
        std::cout << "Lost \n";
    }
    else if ((dealersvalue == usersvalue))
    {
        std::cout << "You and the dealer have the same cards: ";
        std::cout << "Pushed \n";

    }
    else if ((dealersvalue < usersvalue))
    {
        std::cout << "Your cards are higher than the dealers: ";
        std::cout << "Won \n";
    }
}

int drawcard(std::vector<std::string>& Yourcards, std::string cards[13], int Cards[13])
{
    int temp;
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
         temp = rand() % 13;
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
    srand(time(NULL));

    //myTree.create_segTree(myTree.start, myTree.end, myTree.current);
        //std::cout << myTree.segment_tree[1] << std::endl;
    bool Continue = true;
    int ct = 0;
    while (Continue)
    {
        int aces = 0;
        bool User_aces/*?*/ = false;
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
                if (newcard == 12) {
                    aces = aces + 1;
                    User_aces = true;
                }
                usersvalue = usersvalue + values[newcard];
                if (usersvalue > 21)
                {
                    if (aces == 2)
                    {
                        aces = aces - 1;
                        usersvalue = usersvalue - 10;
                    }
                }
                std::cout << cards[newcard] << "\n";
                Yourcards.push_back(cards[newcard]);
            }

        }
        bool newcheck = true;
        std::string userinput;

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
            std::cout << myTree.initial_array[i] << ",";
        }
        std::cout << std::endl;

        for (int i = 0; i < 13*4; i++){
            std::cout << myTree.segment_tree[i] << " ";
        }*/
        myTree.probOfDealerBetter(usersvalue, dealersvalue);
        myTree.probOfNotGoingOver21(usersvalue);
        std::cout << "Would you like to stand or would you like to hit you have: " << usersvalue << "\n";
        std::cout << std::endl;
        std::cin >> userinput;
        if (userinput == "stand") {
            bool newnewcheck = true;
            bool initiallyace = false;
            if (dealersvalue == 11) {
                initiallyace = true;
            }
            while (newnewcheck)
            {
                bool IfAce = false;
                int newcard = drawcard(Yourcards, cards, myTree.initial_array);
                if (newcard == 999) {
                    std::cout << "QUIT";
                    Continue = false;
                    break;
                }
                if (newcard == 12)
                {
                    IfAce = true;
                }

                else {
                    dealersvalue = dealersvalue + values[newcard];
                    Dealerscards.push_back(cards[newcard]);
                    if (dealersvalue > 21 && (IfAce || initiallyace) )
                    {
                        if (IfAce || initiallyace)
                        {
                            dealersvalue = dealersvalue - 10;
                            if (initiallyace) {
                                initiallyace = false;
                            }
                            else {
                                IfAce = false;
                            }
                        }
                    }
                    if (dealersvalue > 16 )
                    {
                        newnewcheck = false;
                        break;
                    }
                }


            }
            std::cout << "the dealer has: ";
            for (int x = 0; x < Dealerscards.size(); x++)
            {
                std::cout << Dealerscards[x] << " ";
            }
            std::cout << "  for a value of " << dealersvalue << std::endl;
            check_values(dealersvalue, usersvalue);
        }
        if (userinput == "hit")
        {
            bool continuehit = true;
            while (continuehit)
            {
                int newcard = drawcard(Yourcards, cards, myTree.initial_array);
                if (newcard == 12)
                {
                    User_aces = true;
                    aces = aces + 1;
                }
                if (newcard == 999) {
                    std::cout << "QUIT";
                    Continue = false;
                    break;
                }
                else {
                    usersvalue = usersvalue + values[newcard];
                    Yourcards.push_back(cards[newcard]);
                    if (User_aces == true)
                    {
                        if (usersvalue > 21) {
                            usersvalue = usersvalue - 10;
                            aces = aces - 1;
                            if (aces == 0) {
                                (User_aces = false);
                            }
                        }
                    }
                    std::cout << "Your new card is " << cards[newcard] << ". So your new total is: " << usersvalue << "\n";

                    if (usersvalue > 21)
                    {
                        std::cout << "Sorry but you lost\n";
                        break;
                    }


                    myTree.probOfDealerBetter(usersvalue, dealersvalue);
                    myTree.probOfNotGoingOver21(usersvalue);
                    std::cout << "\n Stand or Hit? \n";
                    std::string hitagain;
                    std::cin >> hitagain;
                    if (hitagain == "stand")
                    {
                        continuehit = false;
                        check_values(dealersvalue, usersvalue);
                    }
                    if (hitagain == "hit")
                    {
                        std::cout << "Ok here we go!\n";
                    }
                }


            }
        }

        std::string playAgain;
        std::cout << "Would you like to play again? (Y/N)" << std::endl;
        std::cin >> playAgain;
        if (playAgain == "no" || playAgain == "No" || playAgain == "N" || playAgain == "n") {
            break;
        }
        std::cout << std::endl;
    }
}
