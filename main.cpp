#include <iostream>
#include "SegTree.h"
#include <string>
#include <random>
#include <vector>

void check_values(int dealersvalue, int usersvalue, std::vector<std::string> Dealerscards, bool blackjack);
int drawcard(std::vector<std::string>& Yourcards, std::string cards[13], int Cards[13]);

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
    bool Continue = true; // using this bool statement to check if there are still cards left in the deck
    while (Continue)
    {
        bool blackjack = false; //uses this to check if user has a blackjack
        int aces = 0; //uses this to check how many Aces the user has
        bool User_aces/*?*/ = false; //uses this  to see how many aces the user has!
        int dealersvalue = 0; //this is the total card value that the dealer has.
        std::vector<std::string> Yourcards; //holds what cards the user has
        std::vector<std::string> Dealerscards; //holds what cards the Dealer has
        for (int i = 0; i < 1; i++) {
            int newcard = drawcard(Yourcards, cards, myTree.initial_array); //This is used to get the first card the dealer has.
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
        int usersvalue = 0; //this is used to hold the users value of cards
        std::cout << "The dealers first card is " << Dealerscards[0] << "\n";
        std::cout << "Your Cards are: \n";
        for (int i = 0; i < 2; i++)//this for loop is used to draw the first 2 cards the user has
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
        std::string userinput; //this is used to take the user input.


        if (usersvalue == 21) //this checks to see if the user initially has blackjack and if it beats the dealer.
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
            }
            if (dealersvalue != 21)
            {
                blackjack = true;
                check_values(dealersvalue, usersvalue, Dealerscards, blackjack);
            }
        }
        else { //if the user doesnt have blackjack then continue.
            myTree.probOfDealerBetter(usersvalue, dealersvalue);
            myTree.probOfNotGoingOver21(usersvalue);
            myTree.proboffavor_hand(usersvalue);
            std::cout << "Would you like to stand or would you like to hit you have: " << usersvalue << "\n";
            std::cout << std::endl;
            std::cin >> userinput; //takes the users input for if they want to hit or if they want to stand
            if (userinput == "stand") {
                bool newnewcheck = true;
                bool initiallyace = false; //this is used to see if the dealers first card is an ace!
                if (dealersvalue == 11) {
                    initiallyace = true;
                }
                while (newnewcheck)// this is used to continue the loop until the user stands or goes over 21!
                {
                    bool IfAce = false; //this is used to see if the user has an ace!
                    int newcard = drawcard(Yourcards, cards, myTree.initial_array); //drawcards!
                    if (newcard == 999) {
                        std::cout << "QUIT";
                        Continue = false;
                        break;
                    }
                    if (newcard == 12) //if theres an ace then make boolean value as true.
                    {
                        IfAce = true;
                    }

                    else { //if theres no ace! then allow the dealer to continue drawing cards.
                        dealersvalue = dealersvalue + values[newcard];
                        Dealerscards.push_back(cards[newcard]);
                        if (dealersvalue > 21 && (IfAce || initiallyace)) //if theres an ace and values over 21 then subrract 10 from the total:
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
                        if (dealersvalue > 16) // breaks the loop if dealers value is greater than 16
                        {
                            newnewcheck = false;
                            break;
                        }
                    }


                }
                check_values(dealersvalue, usersvalue, Dealerscards, blackjack); // uses this value to check who one
            }
            if (userinput == "hit") //if user hits then do this:
            {
                bool continuehit = true;
                while (continuehit) //makes a loop to allow the user to continue to hit until they dont want to anymore!
                {
                    int newcard = drawcard(Yourcards, cards, myTree.initial_array); //draws a new card for user
                    if (newcard == 12) //if its an ace then add ace to user aces value count.
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
                        usersvalue = usersvalue + values[newcard]; //if no ace, pushback the new card
                        Yourcards.push_back(cards[newcard]);//this pushes back the users card to keep track
                        if (User_aces == true)
                        {
                            if (usersvalue > 21) {
                                usersvalue = usersvalue - 10; //if theres an ace and the value is over 21 then subtract 10 from the total count
                                aces = aces - 1;
                                if (aces == 0) {
                                    (User_aces = false);
                                }
                            }
                        }
                        std::cout << "Your new card is " << cards[newcard] << ". So your new total is: " << usersvalue << "\n";

                        if (usersvalue > 21) //if users value is  greater then 21
                        {
                            bool newnewcheck = true; //break the loop
                            bool initiallyace = false; // make inital ace false;
                            if (dealersvalue == 11) {
                                initiallyace = true;
                            }
                            while (newnewcheck)
                            {
                                bool IfAce = false;
                                int newcard = drawcard(Yourcards, cards, myTree.initial_array); //uses this to draw a new card
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
                                    dealersvalue = dealersvalue + values[newcard]; //this is used to make the dealers value until 21
                                    Dealerscards.push_back(cards[newcard]);
                                    if (dealersvalue > 21 && (IfAce || initiallyace))
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
                                    if (dealersvalue > 16)
                                    {
                                        newnewcheck = false;
                                        break;
                                    }
                                }


                            }
                            check_values(dealersvalue, usersvalue, Dealerscards, blackjack); //check to see who won
                        }


                        myTree.probOfDealerBetter(usersvalue, dealersvalue);
                        myTree.probOfNotGoingOver21(usersvalue);
                        myTree.proboffavor_hand(usersvalue);
                        std::cout << "\n Stand or Hit? \n";
                        std::string hitagain;
                        std::cin >> hitagain;
                        if (hitagain == "stand") //if users input = stand then see who won.
                        {
                            continuehit = false; //stop the loop for continuing hit
                            bool newnewcheck = true;
                            bool initiallyace = false;
                            if (dealersvalue == 11) { //if dealer has an ace make then there is an ace!
                                initiallyace = true;
                            }
                            while (newnewcheck)
                            {
                                bool IfAce = false;
                                int newcard = drawcard(Yourcards, cards, myTree.initial_array); //draws a new card for dealer
                                if (newcard == 999) {
                                    std::cout << "QUIT";
                                    Continue = false;
                                    break;
                                }
                                if (newcard == 12) //if theres an ace then theres an Ace!
                                {
                                    IfAce = true;
                                }

                                else {
                                    dealersvalue = dealersvalue + values[newcard]; //This is used to add values to dealers card value
                                    Dealerscards.push_back(cards[newcard]);
                                    if (dealersvalue > 21 && (IfAce || initiallyace))
                                    {
                                        if (IfAce || initiallyace)
                                        {
                                            dealersvalue = dealersvalue - 10; //if theres an ace and over 21 then dealers value subtracts 10 from total.
                                            if (initiallyace) {
                                                initiallyace = false;
                                            }
                                            else {
                                                IfAce = false;
                                            }
                                        }
                                    }
                                    if (dealersvalue > 16)
                                    {
                                        newnewcheck = false;
                                        break;
                                    }
                                }


                            }
                            check_values(dealersvalue, usersvalue, Dealerscards, blackjack); // checks to see who won!
                        }
                        if (hitagain == "hit") //checks to see if user wants to continue!
                        {
                            std::cout << "I wouldnt have done that\n";
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
}







void check_values(int dealersvalue, int usersvalue, std::vector<std::string> Dealerscards, bool blackjack)
{
    if (blackjack == true) //Checks to see if user has a blackjack!
    {
        std::cout << "The dealers cards are: ";
        for (int i = 0; i < Dealerscards.size(); i++)
        {
            std::cout << Dealerscards[i] << " ";
        }
        std::cout << "for a count of: " << dealersvalue << std::endl;
        std::cout << "You got BlackJack ";
        std::cout << "Won \n";
    }
    if (usersvalue > 21) //user has over 21
    {
        std::cout << "The dealers cards are: ";
        for (int i = 0; i < Dealerscards.size(); i++)
        {
            std::cout << Dealerscards[i] << " ";
        }
        std::cout << "for a count of: " << dealersvalue << std::endl;
        std::cout << "Therefore you lost\n";

    }
    else { //if user doesnt have blackjack or over 21
        if (dealersvalue > 21 && usersvalue <= 21) // checks to see who won
        {
            std::cout << "The dealers cards are: ";
            for (int i = 0; i < Dealerscards.size(); i++)
            {
                std::cout << Dealerscards[i] << " ";
            }
            std::cout << "for a count of: " << dealersvalue << std::endl;
            std::cout << "The dealer has gone over 21: ";
            std::cout << "Won \n";
        }
        else if (dealersvalue > usersvalue)
        {
            std::cout << "The dealers cards are: ";
            for (int i = 0; i < Dealerscards.size(); i++)
            {
                std::cout << Dealerscards[i] << " ";
            }
            std::cout << "for a count of: " << dealersvalue << std::endl;
            std::cout << "The dealer's cards are higher than yours: ";
            std::cout << "Lost \n";
        }
        else if ((dealersvalue == usersvalue))
        {
            std::cout << "The dealers cards are: ";
            for (int i = 0; i < Dealerscards.size(); i++)
            {
                std::cout << Dealerscards[i] << " ";
            }
            std::cout << "for a count of: " << dealersvalue << std::endl;
            std::cout << "You and the dealer have the same cards: ";
            std::cout << "Pushed \n";

        }
        else if ((dealersvalue < usersvalue))
        {
            std::cout << "The dealers cards are: ";
            for (int i = 0; i < Dealerscards.size(); i++)
            {
                std::cout << Dealerscards[i] << " ";
            }
            std::cout << "for a count of: " << dealersvalue << std::endl;
            std::cout << "Your cards are higher than the dealers: ";
            std::cout << "Won \n";
        }
    }
}

int drawcard(std::vector<std::string>& Yourcards, std::string cards[13], int Cards[13]) // this is the function to draw a new randomcard!;
{
    int temp;
    bool check = false;
    for (int i = 0; i < 13; i++) //checks to see if all cards are drawn!
    {
        if (Cards[i] != 0)
        {
            check = true;
            break;
        }
    }
    if (check == false) // if there are no cards left break out of main!
    {
        return(999);
    }
    while (check)// if not then draw a random card!
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
