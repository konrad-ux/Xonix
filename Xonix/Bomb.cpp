#include "Bomb.h"
#include "Game.h"

Bomb::Bomb(int x, int y) : Bonus(x, y) {}

void Bomb::applyEffect(Player& player, Game& game)
{
    game.triggerBombEffect();
}