#include"SpeedBonus.h"

void SpeedBonus::applySpeedBonus(Player& player) {
	player.dx *= 2; // Zwiększenie prędkości w poziomie
	player.dy *= 2; // Zwiększenie prędkości w pionie
}
void SpeedBonus::resetSpeedBonus(Player& player) {
	player.dx /= 2; // Przywrócenie prędkości w poziomie
	player.dy /= 2; // Przywrócenie prędkości w pionie
}