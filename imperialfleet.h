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

    void getAttacked(AttackingUnit &unit) override {
        takeDamage(unit.getAttackPower());
    }

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
    Squadron(std::vector<std::shared_ptr<ImperialUnit>> &subunits)
            : AttackableUnit(0), ImperialUnit(0, 0), subunits(subunits) {
        for (auto unit : subunits) {
            shield += unit->getShield();
            attackPower += unit->getAttackPower();
        }
    }

    Squadron(std::initializer_list<std::shared_ptr<ImperialUnit>> subunits)
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
    std::vector<std::shared_ptr<ImperialUnit>> subunits;
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

std::shared_ptr<Squadron> createSquadron(std::vector<std::shared_ptr<ImperialUnit>> subunits) {
    return std::make_shared<Squadron>(subunits);
}

std::shared_ptr<Squadron> createSquadron(std::initializer_list<std::shared_ptr<ImperialUnit>> subunits) {
    return std::make_shared<Squadron>(subunits);
}

#endif //STARWARS2_IMPERIALFLEET_H
