#include"SpeedBonus.h"

void SpeedBonus::applySpeedBonus(Player& player) {
	player.dx *= 2; // Zwi�kszenie pr�dko�ci w poziomie
	player.dy *= 2; // Zwi�kszenie pr�dko�ci w pionie
}
void SpeedBonus::resetSpeedBonus(Player& player) {
	player.dx /= 2; // Przywr�cenie pr�dko�ci w poziomie
	player.dy /= 2; // Przywr�cenie pr�dko�ci w pionie
}