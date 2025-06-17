#include "LineImmunityBonus.h"
#include "Game.h" // Potrzebny do interakcji z gr¹/graczem

LineImmunityBonus::LineImmunityBonus(int x, int y) : Bonus(x, y) {}

// ZMIANA: Implementacja wirtualnej metody.
void LineImmunityBonus::applyEffect(Player& player, Game& game)
{
    game.activateLineImmunity(player);
}