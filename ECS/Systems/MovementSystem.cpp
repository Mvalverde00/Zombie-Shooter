#pragma once

#include <entt.hpp>

#include "../Components/VelocityComponent.cpp"
#include "../Components/PositionComponent.cpp"

void movementSystem(entt::registry& reg, Uint32 dt){
	const auto view = reg.view<PositionComponent, VelocityComponent>();
	for (const entt::entity e : view) {
		auto &vel = view.get<VelocityComponent>(e);
		auto &pos = view.get<PositionComponent>(e);

		pos.pos += (vel.vel * (dt/1000.0));

	}

}