#pragma once

#include <math.h>

#include <entt.hpp>

#include "../Components/PositionComponent.cpp"
#include "../Components/PlayerAimInputComponent.cpp"

#include "../../Camera.cpp"

void playerAimInputSystem(entt::registry& reg, Camera* cam) {

	const auto view = reg.view<PositionComponent, PlayerAimInputComponent>();
	for (const entt::entity e : view) {
		auto &pos = view.get<PositionComponent>(e);
		auto &paic = view.get<PlayerAimInputComponent>(e);

		pos.rot = std::atan2(-pos.pos.y + cam->getPos().y + *paic.mouse_y, -pos.pos.x + cam->getPos().x + *paic.mouse_x)*(180/3.14159);
	}

}