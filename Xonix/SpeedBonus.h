#pragma once
#include "Bonus.h"
#include "Player.h"

class SpeedBonus : public Bonus {
private:
    float originalDelay; // Zmienna do przechowywania oryginalnej prêdkoœci

public:
    SpeedBonus(int x, int y);

    // Przekazujemy teraz referencjê do opóŸnienia z klasy Game
    void applySpeedBonus(float& delay);
    void resetSpeedBonus(float& delay);
};