#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

#include <memory>
#include <vector>
#include <initializer_list>
#include <assert.h>
#include "helper.h"

class ImperialUnit : public AttackingUnit {
public:
    ImperialUnit(ShieldPoints shield, AttackPower attackPower) : AttackingUnit(shield, attackPower) {}

    void getAttacked(AttackingUnit &unit) override {}

    void tryToAttack(AttackableUnit &unit) override {
        unit.getAttacked(*this);
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
public:
    Squadron(std::vector<UnitPtr<ImperialUnit>> &subunits)
            : AttackableUnit(0), ImperialUnit(0, 0), subunits(subunits) {
        for (auto unit : subunits) {
            shield += unit->getShield();
            attackPower += unit->getAttackPower();
        }
    }

    Squadron(std::initializer_list<UnitPtr<ImperialUnit>> subunits)
            : AttackableUnit(0), ImperialUnit(0, 0), subunits(subunits) {
        for (auto unit : subunits) {
            shield += unit->getShield();
            attackPower += unit->getAttackPower();
        }
    }

    void takeDamage(AttackPower damage) override {
        for (auto unit : subunits) {
            unsigned int startShield = unit->getShield();
            unit->takeDamage(damage);
            unsigned int endShield = unit->getShield();

            assert(shield >= startShield - endShield);
            shield -= (startShield - endShield);
        }
    }

private:
    std::vector<UnitPtr<ImperialUnit>> subunits;
};

UnitPtr<DeathStar> createDeathStar(ShieldPoints shield, AttackPower attackPower) {
    return makeUnitPtr<DeathStar>(shield, attackPower);
}

UnitPtr<ImperialDestroyer> createImperialDestroyer(ShieldPoints shield, AttackPower attackPower) {
    return makeUnitPtr<ImperialDestroyer>(shield, attackPower);
}

UnitPtr<TIEFighter> createTIEFighter(ShieldPoints shield, AttackPower attackPower) {
    return makeUnitPtr<TIEFighter>(shield, attackPower);
}

UnitPtr<Squadron> createSquadron(std::vector<UnitPtr<ImperialUnit>> subunits) {
    return makeUnitPtr<Squadron>(subunits);
}

UnitPtr<Squadron> createSquadron(std::initializer_list<UnitPtr<ImperialUnit>> subunits) {
    return makeUnitPtr<Squadron>(subunits);
}

#endif //STARWARS2_IMPERIALFLEET_H
