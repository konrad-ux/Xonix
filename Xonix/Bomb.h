#pragma once

#include "Bonus.h"

class Bomb : public Bonus {
public:
    Bomb(int x, int y);
    void applyEffect(Player& player, Game& game) override;
};