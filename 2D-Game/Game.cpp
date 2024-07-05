#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
 
Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
auto& player(manager.addEntity());

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int hieght, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "subsystem initialised" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, hieght, flags);
		if (window) {
		std::cout << "window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}

		isRunning = true;
	}
	
	map = new Map();
	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets//Individual Sprites//adventurer-idle-00.png");
	player.addComponent<KeyboardController>();
}

void Game::handleEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
	}
}

void Game::update() {
	manager.refresh();
	manager.update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->drawMap();

	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}