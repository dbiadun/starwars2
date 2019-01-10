#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

#include "helper.h"

class ImperialUnit : public AttackingUnit {
public:
    ImperialUnit(ShieldPoints shield, AttackPower attackPower) : AttackingUnit(shield, attackPower) {}

    void getAttacked(AttackingUnit &unit) override {
        takeDamage(unit.getAttackPower());
    }
};

class ImperialStarship : public ImperialUnit, public Starship {
public:
    ImperialStarship(ShieldPoints shield, AttackPower attackPower)
            : ImperialUnit(shield, attackPower), Starship(shield) {}

    ~ImperialStarship() override = 0;
};

ImperialStarship::~ImperialStarship() {}


class DeathStar : public ImperialStarship {
public:
    DeathStar(ShieldPoints shield, AttackPower attackPower)
            : AttackableUnit(shield), ImperialStarship(shield, attackPower) {}
};

class ImperialDestroyer : public ImperialStarship {
public:
    ImperialDestroyer(ShieldPoints shield, AttackPower attackPower)
            : AttackableUnit(shield), ImperialStarship(shield, attackPower) {}
};

class TIEFighter : public ImperialStarship {
public:
    TIEFighter(ShieldPoints shield, AttackPower attackPower)
            : AttackableUnit(shield), ImperialStarship(shield, attackPower) {}
};

class Squadron : public ImperialUnit {

};

std::shared_ptr<DeathStar> createDeathStar(ShieldPoints shield, AttackPower attackPower) {
    return std::make_shared<DeathStar>(shield, attackPower);
}

std::shared_ptr<ImperialDestroyer> createImperialDestroyer(ShieldPoints shield, AttackPower attackPower) {
    return std::make_shared<ImperialDestroyer>(shield, attackPower);
}

std::shared_ptr<TIEFighter> createTIEFighter(ShieldPoints shield, AttackPower attackPower) {
    return std::make_shared<TIEFighter>(shield, attackPower);
}

#endif //STARWARS2_IMPERIALFLEET_H
