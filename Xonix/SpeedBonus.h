#pragma once
#include "Bonus.h"

class SpeedBonus : public Bonus {
public:
    SpeedBonus(int x, int y);

    // ZMIANA: Deklaracja nadpisania metody wirtualnej.
    // Stare metody applySpeedBonus/resetSpeedBonus s¹ ju¿ niepotrzebne.
    void applyEffect(Player& player, Game& game) override;
};