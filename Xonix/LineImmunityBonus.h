#pragma once
#include "Bonus.h"
#include "Player.h"

class LineImmunityBonus : public Bonus {
public:
    LineImmunityBonus(int x, int y);

    void applyEffect(Player& player);
    void removeEffect(Player& player);
};