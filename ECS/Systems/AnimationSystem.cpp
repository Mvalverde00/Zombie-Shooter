#pragma once

#include "../Components/VelocityComponent.cpp"
#include "../Components/SpriteComponent.cpp"
#include "../Components/AnimationComponent.cpp"

void animationSystem(entt::registry& reg, Uint32 dt) {

	// Check for moving animation
	const auto move_view = reg.view<VelocityComponent, AnimationComponent>();
	for (const entt::entity e : move_view) {
		auto &vel = move_view.get<VelocityComponent>(e);
		auto &anim = move_view.get<AnimationComponent>(e);

		if(vel.vel.x != 0 || vel.vel.y != 0) {
			anim.state = ANIMATION_STATES::MOVING;
		} else {
			anim.state = ANIMATION_STATES::IDLE;
		}

	}

	// Check for shooting animation
	const auto weapon_view = reg.view<InventoryComponent, AnimationComponent>();
	for (const entt::entity e : move_view) {
		auto &inv = weapon_view.get<InventoryComponent>(e);
		auto &anim = weapon_view.get<AnimationComponent>(e);

		auto &weapon = reg.get<WeaponComponent>(inv.items[inv.selected]);

		if (weapon.firing){
			if (weapon.type.compare("MELEE") == 0) {
				anim.state = ANIMATION_STATES::MELEEING;
			} else{
				anim.state = ANIMATION_STATES::SHOOTING;
			}
		}

	}




	const auto view = reg.view<SpriteComponent, AnimationComponent>();
	for (const entt::entity e : view) {
		auto &sprite = view.get<SpriteComponent>(e);
		auto &anim = view.get<AnimationComponent>(e);

		if (anim.state != anim.prev_state) {
			anim.elapsed_frames = 0;
			anim.current_animation_frame = 0;
			anim.prev_state = anim.state;
		}

		std::cout<<anim.state<<"\n";

		sprite = anim.animations[anim.state].frames[anim.current_animation_frame].sprite;

		anim.elapsed_frames++;
		if (anim.elapsed_frames == anim.animations[anim.state].frames[anim.current_animation_frame].frame_duration) {
			anim.elapsed_frames = 0;
			anim.current_animation_frame  = (anim.current_animation_frame + 1)%anim.animations[anim.state].frames.size();
		}


	}

}