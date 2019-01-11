#ifndef STARWARS2_HELPER_H
#define STARWARS2_HELPER_H

using ShieldPoints = unsigned int;
using AttackPower = unsigned int;

class AttackingUnit;

class AttackableUnit {
public:
    explicit AttackableUnit(ShieldPoints shield) : shield(shield) {}

    virtual ~AttackableUnit() = default;

    ShieldPoints getShield() {
        return shield;
    }

    virtual void takeDamage(AttackPower damage) = 0;

    virtual void getAttacked(AttackingUnit &) = 0;

    virtual void tryToAttack(AttackableUnit &) = 0;

protected:
    ShieldPoints shield;
};

class AttackingUnit : virtual public AttackableUnit {
public:
    AttackingUnit(ShieldPoints shield, AttackPower attackPower) : AttackableUnit(shield), attackPower(attackPower) {}

    AttackPower getAttackPower() {
        return attackPower;
    }

    void attack(AttackableUnit &unit) {
        unit.getAttacked(*this);
    }

protected:
    AttackPower attackPower;
};

class Starship : virtual public AttackableUnit {
public:
    explicit Starship(ShieldPoints shield) : AttackableUnit(shield) {}

    void takeDamage(AttackPower damage) override {
        if (damage > shield) {
            shield = 0;
        } else {
            shield -= damage;
        }
    }
};


#endif //STARWARS2_HELPER_H
