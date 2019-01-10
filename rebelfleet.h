#ifndef STARWARS2_REBELFLEET_H
#define STARWARS2_REBELFLEET_H

#include "helper.h"

using Speed = unsigned int;

class RebelStarship : public Starship {
public:
    explicit RebelStarship(ShieldPoints shield, Speed speed) : Starship(shield), speed(speed) {}

    Speed getSpeed() {
        return speed;
    }

private:
    Speed speed;
};

class NonattackingRebelStarship : public RebelStarship {
public:
    NonattackingRebelStarship(ShieldPoints shield, Speed speed) : RebelStarship(shield, speed) {}

    ~NonattackingRebelStarship() override = 0;

    void getAttacked(AttackingUnit &unit) override {
        takeDamage(unit.getAttackPower());
    }
};

NonattackingRebelStarship::~NonattackingRebelStarship() {}


class AttackingRebelStarship : public RebelStarship, public AttackingUnit {
public:
    AttackingRebelStarship(ShieldPoints shield, Speed speed, AttackPower attackPower)
            : RebelStarship(shield, speed), AttackingUnit(shield, attackPower) {}

    ~AttackingRebelStarship() override = 0;

    void getAttacked(AttackingUnit &unit) override {
        takeDamage(unit.getAttackPower());
        unit.getAttacked(*this);
    }
};

AttackingRebelStarship::~AttackingRebelStarship() {}


class Explorer : public NonattackingRebelStarship {
public:
    Explorer(ShieldPoints shield, Speed speed)
            : AttackableUnit(shield), NonattackingRebelStarship(shield, speed) {}
};

class StarCruiser : public AttackingRebelStarship {
public:
    StarCruiser(ShieldPoints shield, Speed speed, AttackPower attackPower)
            : AttackableUnit(shield), AttackingRebelStarship(shield, speed, attackPower) {}
};

class XWing : public AttackingRebelStarship {
public:
    XWing(ShieldPoints shield, Speed speed, AttackPower attackPower)
            : AttackableUnit(shield), AttackingRebelStarship(shield, speed, attackPower) {}
};

std::shared_ptr<Explorer> createExplorer(ShieldPoints shield, Speed speed) {
    return std::make_shared<Explorer>(shield, speed);
}

std::shared_ptr<StarCruiser> createStarCruiser(ShieldPoints shield, Speed speed, AttackPower attackPower) {
    return std::make_shared<StarCruiser>(shield, speed, attackPower);
}

std::shared_ptr<XWing> createXWing(ShieldPoints shield, Speed speed, AttackPower attackPower) {
    return std::make_shared<XWing>(shield, speed, attackPower);
}


#endif //STARWARS2_REBELFLEET_H
