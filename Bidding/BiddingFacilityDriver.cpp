//
// Created by MJ on 2019-10-04.
//

#include <iostream>
#include "BiddingFacility.h"

int main() {
    // in game these facilities would be part of each player
    vector<BiddingFacility> bidders;

    // create players
    int *player1Tokens = new int(9);
    int *player1Age = new int(16);
    BiddingFacility biddingFacility1 = BiddingFacility(player1Tokens, player1Age);
    bidders.push_back(biddingFacility1);

    int *player2Tokens = new int(9);
    int *player2Age = new int(12);
    BiddingFacility biddingFacility2 = BiddingFacility(player2Tokens, player2Age);
    bidders.push_back(biddingFacility2);

    int *player3Tokens = new int(9);
    int *player3Age = new int(12);
    BiddingFacility biddingFacility3 = BiddingFacility(player3Tokens, player3Age);
    bidders.push_back(biddingFacility3);

    printf("|%-10s|%-5s|%-5s|%-5s|\n", "Player", "Bid", "Coin", "Age");
    printf("|%-10s|%5d|%5d|%5d|\n", "Player1", 0, *player1Tokens, *player1Age);
    printf("|%-10s|%5d|%5d|%5d|\n", "Player2", 0, *player2Tokens, *player2Age);
    printf("|%-10s|%5d|%5d|%5d|\n", "Player3", 0, *player3Tokens, *player3Age);
    cout << endl;

    // perform bids
    for (int i = 0; i < 3; i++) {
        cout << "Player" << i+1 << ": " << endl;
        bidders[i].bid();
        cout << endl;
    }

    cout << "State After Bid:" << endl;
    printf("|%-10s|%-5s|%-5s|%-5s|\n", "Player", "Bid", "Coin", "Age");
    printf("|%-10s|%5d|%5d|%5d|\n", "Player1", *biddingFacility1.getAmountBid(), *player1Tokens, *player1Age);
    printf("|%-10s|%5d|%5d|%5d|\n", "Player2", *biddingFacility2.getAmountBid(), *player2Tokens, *player2Age);
    printf("|%-10s|%5d|%5d|%5d|\n", "Player3", *biddingFacility3.getAmountBid(), *player3Tokens, *player3Age);
    cout << endl;

    // get winner
    string winner = "temp"; // this will not be required in actual game, only here because not linked to a real player
    BiddingFacility *winningBidder = nullptr;
    for (int i = 0; i < 3; i++) {
        if (bidders[i].largerBidThan(winningBidder)) {
            winner = "Player"+ to_string(i+1);
            winningBidder = &bidders[i];
        }
    }

    // pay the man
    winningBidder->payBid();
    cout << "Winner is: " << winner << endl;
    cout << "State After Paying Bid:" << endl;
    printf("|%-10s|%-5s|%-5s|%-5s|\n", "Player", "Bid", "Coin", "Age");
    printf("|%-10s|%5d|%5d|%5d|\n", "Player1", *biddingFacility1.getAmountBid(), *player1Tokens, *player1Age);
    printf("|%-10s|%5d|%5d|%5d|\n", "Player2", *biddingFacility2.getAmountBid(), *player2Tokens, *player2Age);
    printf("|%-10s|%5d|%5d|%5d|\n", "Player3", *biddingFacility3.getAmountBid(), *player3Tokens, *player3Age);
    cout << endl;

    cout << "fin" << endl;
    cout << "press any key to exit";

    return 0;
}