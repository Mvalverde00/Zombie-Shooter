#pragma once

#include <entt.hpp>
#include <SDL.h>

#include "../Components/SpriteComponent.cpp"
#include "../Components/PositionComponent.cpp"

void renderSystem(entt::registry& reg, SDL_Renderer* renderer, Camera* cam) {
	SDL_Rect dst;

	const auto view = reg.view<PositionComponent, SpriteComponent>();
	for (const entt::entity e : view) {
		auto &sprite = view.get<SpriteComponent>(e);
		auto &pos = view.get<PositionComponent>(e);

		if (sprite.t != NULL) {
			dst.x = (pos.pos.x - sprite.width/2) - cam->getPos().x; // We want the rect to be centered on the entities position, so we need to make some small adjustments.
			dst.y = (pos.pos.y - sprite.height/2) - cam->getPos().y;
			dst.w = sprite.width;
			dst.h = sprite.height;
			SDL_RenderCopyEx(renderer, sprite.t, &sprite.src, &dst, pos.rot, NULL, SDL_FLIP_NONE);
		}

	}

}