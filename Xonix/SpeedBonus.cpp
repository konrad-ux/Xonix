#include"SpeedBonus.h"

void SpeedBonus::applySpeedBonus(Player& player) {
	player.dx *= 2; // Zwiêkszenie prêdkoœci w poziomie
	player.dy *= 2; // Zwiêkszenie prêdkoœci w pionie
}
void SpeedBonus::resetSpeedBonus(Player& player) {
	player.dx /= 2; // Przywrócenie prêdkoœci w poziomie
	player.dy /= 2; // Przywrócenie prêdkoœci w pionie
}