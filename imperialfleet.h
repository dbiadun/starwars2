//
// Created by dawid on 09.01.19.
//

#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

#include "helper.h"

class ImperialUnit : public DefendingUnit, public AttackingUnit {

};

class ImperialStarship : public ImperialUnit {

};

class DeathStar : public ImperialStarship {

};

class ImperialDestroyer : public ImperialStarship {

};

class TIEFigher : public ImperialStarship {

};

class Squadron : public ImperialUnit {

};

#endif //STARWARS2_IMPERIALFLEET_H
