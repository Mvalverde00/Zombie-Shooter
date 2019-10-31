#include <SDL.h>
#include <string>
#include <functional>

#include "GameScreen.h"
#include "../Constants.cpp"

class ConfirmationBoxScreen : public GameScreen {

protected:
	// Used to customize the confirmation box
	char *message;


	//
	FC_Font* font;

	// Controls the appearance of the box
	int PADDING = 10;
	SDL_Color BG_COLOR = CONSTANTS::BLACK;

	int textX;
	int textY;
	int textHeight;
	int textWidth;

	int BUTTON_HEIGHT;
	int BUTTON_WIDTH;

	SDL_Rect container;
	SDL_Rect containerPos;

	char *confirmText = "Proceed";
	SDL_Color confirmColor = CONSTANTS::GREEN;
	SDL_Rect confirmButton;
	SDL_Rect confirmButtonPos;

	char *cancelText = "Cancel";
	SDL_Color cancelColor = CONSTANTS::RED;
	SDL_Rect cancelButton;
	SDL_Rect cancelButtonPos;


public:
	ConfirmationBoxScreen(char *message, std::function<void()> func ) {
		this->message = message;
		func();

		isBlocking = true;

		//Used to transition menu elements on/off screen
		transitionTime = 333; // miliseconds
		transitionTimeAccumulator = 0;
		maxTransitionOffset = 570; // Pixels
		transitionOffset = maxTransitionOffset;

	};

	void loadContent(SDL_Renderer* renderer){
		font = FC_CreateFont();
		FC_LoadFont(font, renderer, "FreeSans.ttf", 30, FC_MakeColor(255,255,255,255), TTF_STYLE_NORMAL); // Init a base font for all Menus

		textHeight = FC_GetHeight(font, message);
		textWidth = FC_GetWidth(font, message);

		textX = CONSTANTS::SCREEN_WIDTH/2;
		textY = (CONSTANTS::SCREEN_HEIGHT-textHeight)/2;

		BUTTON_WIDTH = (textWidth-PADDING)/2;
		BUTTON_HEIGHT = textHeight*.9;

		container = {textX - textWidth/2 - PADDING, textY - PADDING, textWidth + 2*PADDING, textHeight + 2*PADDING + BUTTON_HEIGHT};
		confirmButton = {container.x + PADDING, container.y + BUTTON_HEIGHT, container.w, container.h - BUTTON_HEIGHT};
		cancelButton = {container.x + 2*PADDING + BUTTON_WIDTH, container.y + BUTTON_HEIGHT, container.w, container.h - BUTTON_HEIGHT};

	};
	void unloadContent(){
		FC_FreeFont(font);
	};

	void processInput(SDL_Event* e){
	};
	void update(Uint32 deltaT){
		updateTransitionSlide(deltaT);
	};
	void render(SDL_Renderer* renderer){

		SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
		containerPos = {container.x, container.y + transitionOffset, container.w, container.h};
		SDL_RenderFillRect(renderer, &containerPos);

		SDL_SetRenderDrawColor(renderer, confirmColor.r, confirmColor.g, confirmColor.b, confirmColor.a);
		confirmButtonPos = {confirmButton.x, confirmButton.y + transitionOffset, confirmButton.w, confirmButton.h};
		SDL_RenderFillRect(renderer, &confirmButtonPos);

		SDL_SetRenderDrawColor(renderer, cancelColor.r, cancelColor.g, cancelColor.b, cancelColor.a);
		cancelButtonPos = {cancelButton.x, cancelButton.y + transitionOffset, cancelButton.w, cancelButton.h};
		SDL_RenderFillRect(renderer, &cancelButtonPos);

		FC_DrawAlign(font, renderer, textX, textY + transitionOffset, FC_ALIGN_CENTER, message);
		FC_DrawAlign(font, renderer, confirmButtonPos.x, confirmButtonPos.y + transitionOffset, FC_ALIGN_CENTER, confirmText);
		FC_DrawAlign(font, renderer, cancelButtonPos.x, cancelButtonPos.y + transitionOffset, FC_ALIGN_CENTER, cancelText);
	};

};