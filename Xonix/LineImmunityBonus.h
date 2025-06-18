#pragma once

#include "Bonus.h"

class Player;
class Game;

class LineImmunityBonus : public Bonus {
public:
    LineImmunityBonus(int x, int y);
    void applyEffect(Player& player, Game& game) override;
};