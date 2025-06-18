#pragma once

#include "Bonus.h"

class SpeedBonus : public Bonus {
public:
    SpeedBonus(int x, int y);
    void applyEffect(Player& player, Game& game) override;
};