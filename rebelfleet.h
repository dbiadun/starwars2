//
// Created by dawid on 09.01.19.
//

#ifndef STARWARS2_REBELFLEET_H
#define STARWARS2_REBELFLEET_H

#include "helper.h"

using Speed = int;

class RebelStarship : public DefendingUnit {
public:
    Speed getSpeed() {
        return speed;
    }

private:
    Speed speed;
};

class Explorer : public RebelStarship {

};

class StarCruiser : public RebelStarship {

};

class XWing : public RebelStarship, public AttackingUnit {

};


#endif //STARWARS2_REBELFLEET_H
