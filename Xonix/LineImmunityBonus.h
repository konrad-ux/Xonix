#pragma once
#include "Bonus.h"

// Forward-declaration, ¿eby unikn¹æ do³¹czania ca³ego Player.h
class Player;

class LineImmunityBonus : public Bonus {
public:
    LineImmunityBonus(int x, int y);

    // ZMIANA: Deklaracja nadpisania metody wirtualnej.
    void applyEffect(Player& player, Game& game) override;
};