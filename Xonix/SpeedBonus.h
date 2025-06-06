#pragma once
#include "Bonus.h"
#include "Player.h"

class SpeedBonus: public Bonus {
public:
	SpeedBonus(int x, int y) : Bonus(x, y) {}
	void applySpeedBonus(Player& player);
	void resetSpeedBonus(Player& player);
};
