#ifndef STARWARS2_BATTLE_H
#define STARWARS2_BATTLE_H

#include <vector>
#include "helper.h"
#include "rebelfleet.h"
#include "imperialfleet.h"

using Time = unsigned int;

class TimeCounter {
public:
    TimeCounter(Time startTime, Time maxTime) : startTime(startTime), maxTime(maxTime) {}

    virtual ~TimeCounter() = default;

    virtual Time tick() = 0;

private:
    Time startTime;
    Time maxTime;
};

class BasicTimeCounter : TimeCounter {

};

class SpaceBattle {
public:
    SpaceBattle(Time t0, Time t1, std::vector<UnitPtr<AttackableUnit>> &units);

    size_t countImperialFleet();

    size_t countRebelFleet();

    void tick(Time);

    class Builder {
    public:
        Builder &ship(UnitPtr<AttackableUnit>);

        Builder &startTime(Time);

        Builder &maxTime(Time);

        SpaceBattle build();

    private:
        Time startT;
        Time maxT;
        std::vector<UnitPtr<AttackableUnit>> units;
        bool startTSet;
        bool maxTSet;
        bool unitsSet;
    };
private:
    Time startTime;
    Time maxTime;
    TimeCounter &counter;
    std::vector<UnitPtr<AttackableUnit>> units;

};

#endif //STARWARS2_BATTLE_H
