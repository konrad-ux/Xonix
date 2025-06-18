#include "SpeedBonus.h"
#include "Game.h"

SpeedBonus::SpeedBonus(int x, int y) : Bonus(x, y) {}

void SpeedBonus::applyEffect(Player& player, Game& game)
{
    game.activateSpeedBonus();
}