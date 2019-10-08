//
// Created by MJ on 2019-10-04.
//

#include <vector>
#include "../Players/Player.h"

#ifndef EIGHT_MINUTE_EMPIRE_BIDDINGFACILITY_H
#define EIGHT_MINUTE_EMPIRE_BIDDINGFACILITY_H

#endif //EIGHT_MINUTE_EMPIRE_BIDDINGFACILITY_H

using namespace std;

class BiddingFacility {
private:
    int *amountBid;
    int *availableCoin;
    int *playerAge;
public:
    BiddingFacility(int *availableCoin, int *playerAge);
    void bid();
    bool largerBidThan(BiddingFacility *biddingFacility);
    int* getAmountBid();
    int* getPlayerAge();
    void payBid();

};