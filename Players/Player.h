//
// Created by Tamar M on 2019-09-25.
//

#ifndef EIGHT_MINUTE_EMPIRE_PLAYER_H
#define EIGHT_MINUTE_EMPIRE_PLAYER_H

class Player {

public:
    int cubes;
    int disks;
    int tokenArmies;

    Player();
    void PayCoin();
    void PlaceNewArmies();
    void MoveArmies();
    void MoveOverLand();
    void BuildCity();
    void DestroyArmy();


};

#endif //EIGHT_MINUTE_EMPIRE_PLAYER_H
