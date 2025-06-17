#include "Bomb.h"
#include "Game.h"

// POPRAWKA: Dodana definicja konstruktora
Bomb::Bomb(int x, int y) : Bonus(x, y) {}

// POPRAWKA: Dodana definicja metody
void Bomb::applyEffect(Player& player, Game& game)
{
    game.triggerBombEffect();
}