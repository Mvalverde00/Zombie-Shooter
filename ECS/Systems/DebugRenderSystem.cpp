#pragma once

// Display hitboxes, positions
void debugRenderSystem(entt::reg, SDL_Renderer* renderer){

	const auto view = reg.view<PositionComponent, CollisionComponent>();
	for (const entt::entity e : view) {
		auto &bbox = view.get<CollisionComponent>(e).bbox;

		SDL_RenderDrawRect(renderer, &bbox);

	}
}