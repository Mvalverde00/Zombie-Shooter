#ifndef CAMERA_C
#define CAMERA_C

#include "Vector2D.cpp"
#include "ECS/Components/PositionComponent.cpp"
#include <entt.hpp>

class Camera {

	// The x and y coordinates of the TOP LEFT of the camera
	Vector2D pos;
	// The x and y coordinates of the BOTTOM RIGHT of the camera
	Vector2D br;

	// The resolution of the camera
	Vector2D res;

	// The rightmost (highest x) and bottommost (highest y) coordinates that the camera should display.
	Vector2D bounds;

	 entt::entity target;
	 Vector2D* target_pos;

public:

	Camera(int camera_width, int camera_height, int world_width, int world_height) {
		res.x = camera_width;
		res.y = camera_height;

		bounds.x = world_width;
		bounds.y = world_height;

		br.x = pos.x + camera_width;
		br.y = pos.y + camera_height;

	}

	// Use this constructor if you dont have access to the boundary size when creating the map.
	// You can altar the boundary size later using setBounds
	Camera(int camera_width, int camera_height) {
		res.x = camera_width;
		res.y = camera_height;

		bounds.x = camera_width;
		bounds.y = camera_height;

		br.x = pos.x + camera_width;
		br.y = pos.y + camera_height;

	}


	void setPos(int x, int y) {
		if (x < 0) x = 0;
		if (y < 0) y = 0;

		if (x > bounds.x - res.x) x = bounds.x - res.x;
		if (y > bounds.y - res.y) y = bounds.y - bounds.x;

		pos.x = x;
		pos.y = y;

		br.x = pos.x + res.x;
		br.y = pos.y + res.y;

	}

	// Returns a reference to pos, with the promise not to change it
	const Vector2D& getPos() {
		return pos;
	}
	// Returns a reference to br, with the promise not to change it
	const Vector2D& getBR() {
		return br;
	}

	void setBounds(int x, int y) {
		bounds.x = x;
		bounds.y = y;
	}

	void bind(entt::registry &reg, entt::entity e) {
		target = e;
		target_pos = &(reg.get<PositionComponent>(e).pos);
	}

	void update(entt::registry &reg) {
		if (reg.valid(target)) setPos(target_pos->x - res.x/2, target_pos->y - res.y/2);
	}

};

#endif