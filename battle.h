#ifndef STARWARS2_BATTLE_H
#define STARWARS2_BATTLE_H

#include <vector>
#include "helper.h"
#include "rebelfleet.h"
#include "imperialfleet.h"

using Time = int;

class TimeCounter {
public:
    TimeCounter(Time startTime, Time maxTime) : time(startTime), maxTime(maxTime) {}

    virtual ~TimeCounter() = default;

    virtual Time tick(Time delta) = 0;

    virtual bool canAttack() = 0;

protected:
    Time time;
    Time maxTime;
};

class BasicTimeCounter : public TimeCounter {
public:
    BasicTimeCounter(Time startTime, Time maxTime) : TimeCounter(startTime, maxTime) {
        assert(startTime >= 0 && maxTime >= 0);
        assert(startTime <= maxTime);
    }

    Time tick(Time delta) override {
        if (delta >= (maxTime + 1) - time) {
            time = (delta - ((maxTime + 1) - time)) % (maxTime + 1);
        } else {
            time += delta;
        }

        return time;
    }

    bool canAttack() override {
        return (time % 5) && !(time % 2 && time % 3);
    }

};

class SpaceBattle {
public:
    SpaceBattle(
            Time t0,
            Time t1,
            std::vector<UnitPtr<RebelStarship>> &rebels,
            std::vector<UnitPtr<ImperialUnit>> &imperium)
            : timeCounter(std::make_shared<BasicTimeCounter>(t0, t1)),
              imperialUnits(imperium),
              rebelUnits(rebels),
              imperialFleetSize(0),
              rebelFleetSize(rebelUnits.size()) {
        for (auto unit : imperium) {
            imperialFleetSize += unit->getAlive();
        }
    }

    size_t countImperialFleet() {
        return imperialFleetSize;
    }

    size_t countRebelFleet() {
        return rebelFleetSize;
    }

    void tick(Time delta) {
        if (countImperialFleet() == 0 && countRebelFleet() == 0) {
            printf("DRAW\n");
        } else if (countImperialFleet() == 0) {
            printf("REBELLION WON\n");
        } else if (countRebelFleet() == 0) {
            printf("IMPERIUM WON\n");
        }

        if (timeCounter->canAttack()) {
            for (auto imperialUnit : imperialUnits) {
                size_t imperialAlive = imperialUnit->getAlive();
                if (imperialAlive == 0) continue;

                for (auto rebelUnit : rebelUnits) {
                    if (imperialUnit->getShield() == 0 || rebelUnit->getShield() == 0) continue;

                    imperialUnit->attack(*rebelUnit);
                    if (rebelUnit->getShield() == 0) rebelFleetSize--;
                }

                imperialFleetSize -= imperialAlive - imperialUnit->getAlive();
            }
        }
        timeCounter->tick(delta);
    }

    class Builder {
    public:
        Builder &ship(UnitPtr<RebelStarship> unit) {
            rebelUnits.push_back(unit);
            return *this;
        }

        Builder &ship(UnitPtr<ImperialUnit> unit) {
            imperialUnits.push_back(unit);
            return *this;
        }

        Builder &startTime(Time startTime) {
            startT = startTime;
            return *this;
        }

        Builder &maxTime(Time maxTime) {
            maxT = maxTime;
            return *this;
        }

        SpaceBattle build() {
            return SpaceBattle(startT, maxT, rebelUnits, imperialUnits);
        }

    private:
        Time startT;
        Time maxT;
        std::vector<UnitPtr<ImperialUnit>> imperialUnits;
        std::vector<UnitPtr<RebelStarship>> rebelUnits;
    };

private:
    std::shared_ptr<TimeCounter> timeCounter;
    std::vector<UnitPtr<ImperialUnit>> imperialUnits;
    std::vector<UnitPtr<RebelStarship>> rebelUnits;
    size_t imperialFleetSize;
    size_t rebelFleetSize;
};

#endif //STARWARS2_BATTLE_H
