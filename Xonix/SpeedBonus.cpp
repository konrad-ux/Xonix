#include "SpeedBonus.h"
#include "Game.h" // Potrzebny do wywo³ania metody na obiekcie gry

SpeedBonus::SpeedBonus(int x, int y) : Bonus(x, y) {}

// ZMIANA: Implementacja wirtualnej metody.
// Logika zosta³a przeniesiona tutaj z Game.cpp, ale zamiast bezpoœrednio
// modyfikowaæ 'delay', wywo³ujemy publiczn¹ metodê z 'game'.
void SpeedBonus::applyEffect(Player& player, Game& game) {
    game.activateSpeedBonus();
}