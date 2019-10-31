#pragma once

#include <entt.hpp>

#include "../Components/PlayerWeaponInputComponent.cpp"
#include "../Components/InventoryComponent.cpp"

void playerWeaponInputSystem(entt::registry& reg) {
	const auto view = reg.view<PlayerWeaponInputComponent, InventoryComponent>();
	for (const entt::entity e : view) {
		auto &inv = view.get<InventoryComponent>(e);

		auto &weapon = reg.get<WeaponComponent>(inv.items[inv.selected]);

		if(SDL_BUTTON(1) & SDL_GetMouseState(NULL, NULL)) weapon.firing = true; // It is the job of the weapons system to turn off firing.

	}
}