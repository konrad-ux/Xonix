#include "SpeedBonus.h"

SpeedBonus::SpeedBonus(int x, int y) : Bonus(x, y), originalDelay(0.0f) {}

// Zapisujemy oryginalne opóŸnienie i ustawiamy nowe, szybsze
void SpeedBonus::applySpeedBonus(float& delay) {
    originalDelay = delay;
    delay = 0.05f; // Nowa, mniejsza wartoœæ opóŸnienia (wiêksza prêdkoœæ)
}

// Przywracamy oryginalne opóŸnienie
void SpeedBonus::resetSpeedBonus(float& delay) {
    if (originalDelay > 0.0f) { // Upewniamy siê, ¿e mamy zapisan¹ wartoœæ
        delay = originalDelay;
    }
}