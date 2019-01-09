//
// Created by dawid on 09.01.19.
//

#ifndef STARWARS2_HELPER_H
#define STARWARS2_HELPER_H

using ShieldPoints = int;
using AttackPower = int;

class DefendingUnit {
public:
    DefendingUnit(ShieldPoints shield) : shield(shield) {}

    ShieldPoints getShield() {
        return shield;
    };

    virtual void takeDamage(AttackPower damage) {
        shield -= damage;
    };

protected:
    ShieldPoints shield;
};

class AttackingUnit {
public:
    AttackingUnit(AttackPower attackPower) : attackPower(attackPower) {}

    AttackPower getAttackPower() {
        return attackPower;
    };

    virtual void attack() = 0;
protected:
    AttackPower attackPower;
};


#endif //STARWARS2_HELPER_H
