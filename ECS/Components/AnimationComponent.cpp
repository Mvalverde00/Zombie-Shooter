#pragma once

#include "../../AssetManager.cpp"
#include "SpriteComponent.cpp"

enum ANIMATION_STATES {
	IDLE = 0,
	MOVING,
	MELEEING,
	SHOOTING,
	RELOADING,
	NUMBER_OF_ANIMATION_STATES
};

struct AnimationFrame {
	SpriteComponent sprite;
	int frame_duration;
};

struct AnimationStrip{
	bool defined; // Whether the strip is defined or not
	std::vector<AnimationFrame> frames;
};

class AnimationComponent{

public:
	std::vector<AnimationStrip> animations;
	ANIMATION_STATES state; // Index of current animation strip
	ANIMATION_STATES prev_state;

	int current_animation_frame;
	int elapsed_frames;

	std::vector<bool> strip_exists{std::vector<bool>(ANIMATION_STATES::NUMBER_OF_ANIMATION_STATES, false)}; // Whether an animation strip is defined for a given animation state

	AnimationComponent(std::vector<AnimationStrip> anims){
		animations = anims;
		state = ANIMATION_STATES::IDLE;
		prev_state = ANIMATION_STATES::IDLE;

		current_animation_frame = 0;
		elapsed_frames = 0;

		// Check which strips are defined
		for(int i = 0; i < animations.size(); i++) {
			if (animations[i].defined) strip_exists[i] = true;
		}

	}

};

// file: the filepath containing the animation
// width: the width of a single frame/sprite in the animation file
// height: the height of a single frame/sprite in the animation file
// d_width: the display width of the sprite when rendered
// d_height: the display height of the sprite when rendered
// dur: the number of frames to display the sprite for, before proceeding to the next 
AnimationStrip createAnimationStrip(AssetManager* assetManager, std::string file, int width, int height, int dur, int d_width, int d_height){
	AnimationStrip strip {true}; // The strip that will be returned
	AnimationFrame frame;
	SpriteComponent sprite;

	SDL_Rect r; // The rect used for SpriteComponent
	r.w = width;
	r.h = height;

	// Load the texture
	assetManager->load(file);
	SDL_Texture* t = assetManager->get(file);

	// Grab texture's width and height
	int t_width, t_height;
	SDL_QueryTexture(t, NULL, NULL, &t_width, &t_height);

	// Grab all the frames from the texture
	for (int x = 0; x < t_width/width; x++) {
		for (int y = 0; y < t_height/height; y++) {
			r.x = x*width;
			r.y = y*height;

			sprite = {t, r, d_width, d_height};

			frame = {sprite, dur};
			strip.frames.push_back(frame);
		}
	}

	return strip;


}