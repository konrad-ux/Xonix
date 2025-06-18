#pragma once

#include "Bonus.h"

class Teleport : public Bonus {
public:
    Teleport(int x, int y);
    void applyEffect(Player& player, Game& game) override;
};