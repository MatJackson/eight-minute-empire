//
// Created by MJ on 2019-10-04.
//

#include <vector>
#include "../Players/Player.h"

#ifndef EIGHT_MINUTE_EMPIRE_BIDDINGFACILITY_H
#define EIGHT_MINUTE_EMPIRE_BIDDINGFACILITY_H

using namespace std;

class BiddingFacility {
public:
    int *amountBid;
    int *availableCoin;
    int *playerAge;

    BiddingFacility(int *availableCoin, int *playerAge);
    BiddingFacility(int* tokens);
    void bid();
    bool largerBidThan(BiddingFacility *biddingFacility);
    int* getAmountBid();
    int* getPlayerAge();
    void payBid();

};

#endif //EIGHT_MINUTE_EMPIRE_BIDDINGFACILITY_H