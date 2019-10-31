#pragma once

#include <SDL.h>
#include <entt.hpp>
#include "../Components/PlayerMovementInputComponent.cpp"
#include "../Components/VelocityComponent.cpp"

void playerMovementInputSystem(entt::registry& reg, SDL_Event& event) {

	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		const auto view = reg.view<PlayerMovementInputComponent, VelocityComponent>();
		for (const entt::entity e : view) {
			auto &vel = view.get<VelocityComponent>(e);
			auto &pmic = view.get<PlayerMovementInputComponent>(e);

			pmic.dir.x = 0;
			pmic.dir.y = 0;

			if (pmic.state[SDL_SCANCODE_W]) pmic.dir.y -= 1; 
			if (pmic.state[SDL_SCANCODE_S])  pmic.dir.y += 1; 
			if (pmic.state[SDL_SCANCODE_A]) pmic.dir.x -= 1;
			if (pmic.state[SDL_SCANCODE_D]) pmic.dir.x += 1;


			pmic.dir.norm();
			vel.vel = pmic.dir * pmic.speed;
			}
	}

}