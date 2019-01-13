#ifndef STARWARS2_HELPER_H
#define STARWARS2_HELPER_H

#include <assert.h>
#include <memory>

using ShieldPoints = int;
using AttackPower = int;
template <typename T> using UnitPtr = std::shared_ptr<T>;

template <typename T, typename... Args>
UnitPtr<T> makeUnitPtr(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

class AttackingUnit;

class AttackableUnit {
public:
    explicit AttackableUnit(ShieldPoints shield) : shield(shield) {
        assert(shield >= 0);
    }

    virtual ~AttackableUnit() = default;

    ShieldPoints getShield() {
        return shield;
    }

    virtual void takeDamage(AttackPower damage) = 0;

    virtual void getAttacked(AttackingUnit &) = 0;

protected:
    ShieldPoints shield;
};

class AttackingUnit : virtual public AttackableUnit {
public:
    AttackingUnit(ShieldPoints shield, AttackPower attackPower) : AttackableUnit(shield), attackPower(attackPower) {
        assert(attackPower >= 0);
    }

    AttackPower getAttackPower() {
        return attackPower;
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
