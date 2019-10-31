#pragma once

#include <entt.hpp>
#include "Components/Components.h"

class Factory{

	entt::registry* reg;

public:
	Factory(entt::registry& r) {
		reg = &r;
	}

	entt::entity makePlayer(entt::registry& reg){
		entt::entity player = registry.create();
		registry.assign<PlayerMovementInputComponent>(player, 120);
		registry.assign<VelocityComponent>(player);
		registry.assign<PositionComponent>(player, Vector2D(100,100), 90);
		registry.assign<SpriteComponent>(player);
		registry.assign<AnimationComponent>(player, std::vector<AnimationStrip> {createAnimationStrip(assetManager, "./assets/Survivor/knife/idle/survivor-idle_knife.png", 289, 224, 4, 64, 64)}, 0, 0, 0);
		registry.assign<PlayerAimInputComponent>(player, screenManager->game->getMouseX(), screenManager->game->getMouseY() );
	}

};