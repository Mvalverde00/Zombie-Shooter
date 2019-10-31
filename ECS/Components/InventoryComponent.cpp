#pragma once

#include <entt.hpp>

struct InventoryComponent {
	std::vector<entt::entity> items;
	int selected;
	int max_size;
};