#include "LineImmunityBonus.h"
#include "Game.h" 

LineImmunityBonus::LineImmunityBonus(int x, int y) : Bonus(x, y) {}

void LineImmunityBonus::applyEffect(Player& player, Game& game)
{
    game.activateLineImmunity(player);
}