// BlackJack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*   int COUNT = 0;
        int differencebetweendealeranduser = usersvalue - dealersvalue;

        while (lowestcardthatbeatsuser)
        {
            if (values[COUNT] == differencebetweendealeranduser)
                lowestcardthatbeatsuser == false;
            else
                COUNT++;
        }
*/
#include <iostream>
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
    std::string cards[13] = { "2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace" };
    int values[13] = { 2,3,4,5,6,7,8,9,10,10,10,10,11 };
    int Cards[13] = { 32,32,32,32,32,32,32,32,32,32,32,32,32 };
    bool Continue = true;
    int ct = 0;
    while (Continue)
    {
        int dealersvalue = 0;
        std::vector<std::string> Yourcards;
        std::vector<std::string> Dealerscards;
        for (int i = 0; i < 1; i++) {
            int newcard = drawcard(Yourcards, cards, Cards);
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
            int newcard = drawcard(Yourcards, cards, Cards);
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
        std::cin >> userinput;
        if (userinput == "stand") {
            bool newnewcheck = true;
            while (newnewcheck)
            {
                int newcard = drawcard(Yourcards, cards, Cards);
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
                int newcard = drawcard(Yourcards, cards, Cards);
                if (newcard == 999) {
                    std::cout << "QUIT";
                    Continue = false;
                    break;
                }
                else {
                    usersvalue = usersvalue + values[newcard];
                    Yourcards.push_back(cards[newcard]);
                    std::cout << "Your new card is " << cards[newcard] << ". So your new total is: " << usersvalue << "\n";
                    if (usersvalue > 21)
                    {
                        std::cout << "Sorry but you lost\n";
                        break;
                    }
                    std::cout << "Stand or Hit? \n";
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
 
