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
    int *player2Age = new int(18);
    BiddingFacility biddingFacility2 = BiddingFacility(player2Tokens, player2Age);
    bidders.push_back(biddingFacility2);

    int *player3Tokens = new int(9);
    int *player3Age = new int(7);
    BiddingFacility biddingFacility3 = BiddingFacility(player3Tokens, player3Age);
    bidders.push_back(biddingFacility3);

    // perform bids
    for (int i = 0; i < 3; i++) {
        cout << "Player" << i+1 << ": " << endl;
        bidders[i].bid();
        cout << endl;
    }

    // get winner
    BiddingFacility *winningBidder = nullptr;
    for (auto bidder : bidders) {
        if (bidder.largerBidThan(winningBidder)) {
            winningBidder = &bidder;
        }
    }

    // pay the man
    winningBidder->payBid();

    cout << "tada!" << endl;

    return 0;
}