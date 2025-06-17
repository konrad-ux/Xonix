#include "LineImmunityBonus.h"

LineImmunityBonus::LineImmunityBonus(int x, int y) : Bonus(x, y) {}

void LineImmunityBonus::applyEffect(Player& player)
{
    player.isImmune = true;
}

void LineImmunityBonus::removeEffect(Player& player)
{
    player.isImmune = false;
}