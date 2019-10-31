#include "../Map.cpp"
#include "../Camera.cpp"
#include "../Constants.cpp"
#include "../Vector2D.cpp"
#include "../AssetManager.cpp"

#include <SDL.h>

#include <entt.hpp>

#include "../ECS/Components/Components.h"
#include "../ECS/Systems/Systems.h"

class GameplayScreen : public GameScreen {

	Map* map;
	Camera* cam;
	AssetManager* assetManager;
	entt::registry registry;

public:
	GameplayScreen(){

		map = new Map("./map/main.txt", "./map/TileSet.png");
		cam = new Camera(CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT);

		// bind the camera to the player

	};

	void loadContent(SDL_Renderer *renderer){
		assetManager = new AssetManager(screenManager->game->getRenderer());

		map->loadContent(renderer);

		cam->setBounds(map->WIDTH, map->HEIGHT);

		// Create a player
		entt::entity player = registry.create();
		registry.assign<PlayerMovementInputComponent>(player, 120);
		registry.assign<VelocityComponent>(player);
		registry.assign<PositionComponent>(player, Vector2D(100,100), 90);
		registry.assign<SpriteComponent>(player);
		registry.assign<AnimationComponent>(player, std::vector<AnimationStrip> {createAnimationStrip(assetManager, "./assets/Survivor/knife/idle/survivor-idle_knife.png", 289, 224, 4, 64, 64), createAnimationStrip(assetManager, "./assets/Survivor/knife/move/survivor-move_knife.png", 279, 219, 4, 64, 64), createAnimationStrip(assetManager, "./assets/Survivor/knife/meleeattack/survivor-meleeattack_knife.png", 329, 300, 4, 83, 83) });
		registry.assign<PlayerAimInputComponent>(player, screenManager->game->getMouseX(), screenManager->game->getMouseY() );
		registry.assign<PlayerWeaponInputComponent>(player);

		// Create a knife
		entt::entity knife = registry.create();
		registry.assign<WeaponComponent>(knife, -1, 150, 10.0, "MELEE", 60, 0);

		// Put knife in player's inventory
		registry.assign<InventoryComponent>(player, std::vector<entt::entity> {knife}, 0, 1);

		cam->bind(registry, player);
		
	};
	void unloadContent(){
		map->unloadContent();
		delete map;

		delete cam;

		delete assetManager;

	};


	void processInput(SDL_Event* e){
		playerMovementInputSystem(registry, *e);
	};
	void update(Uint32 deltaT){
		playerAimInputSystem(registry, cam);
		playerWeaponInputSystem(registry);

		movementSystem(registry, deltaT);
		weaponSystem(registry);
		animationSystem(registry, deltaT);

		cam->update(registry);


	};
	void render(SDL_Renderer* renderer){
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, NULL);

		map->render(renderer, cam);

		renderSystem(registry, renderer, cam);



	};

};