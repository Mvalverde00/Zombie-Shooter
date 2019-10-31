#pragma once


void weaponSystem(entt::registry& reg) {
	const auto view = reg.view<WeaponComponent>();
	for (const entt::entity e : view) {
		auto &weapon = view.get(e);

		if (weapon.firing) {
			weapon.ticks_since_last_fired++;
			if (weapon.ticks_since_last_fired == weapon.fire_rate) {
				weapon.ticks_since_last_fired = 0;
				weapon.firing = false;
			}
		}
	}
}