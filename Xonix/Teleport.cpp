#include "Teleport.h"

Teleport::Teleport(int x, int y)
    : Bonus(x, y)
{
}

void Teleport::applyEffect(Player& player, Game& game)
{
    // Puste, logika jest w Game::checkPlayerTeleportCollision
}