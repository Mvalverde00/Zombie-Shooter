#pragma once

#include <string>

struct WeaponComponent {
	int speed;
	int range;
	float damage;
	std::string type;

	int fire_rate;
	int ticks_since_last_fired;
	bool firing = false;
};