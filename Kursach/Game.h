#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "ManagerTexture.h"
#include "ManagerInput.h"
#include "SDL_Sprite.h"

class Game
{
public:
	Game();
	~Game();

	void create(int, int);
	void play();

private:

	void update();
	void render();

	bool GameLoop;

	int GS_width;
	int GS_height;  // размеры окна

	SDL_Window			*window;   // ссылка на окно
	SDL_Renderer		*renderer; // ссылка на рендер
	SDL_Event			 event;     // события нажатия клавиш

	ManagerTexture managertexture;
	ManagerInput managerinput;

	void InitSDL();

	SDL_Sprite sprite[16];
	int sizeCell;
	int grid[4][4] = { 0 };

	int dig;
	int dx = 0, dy = 0;
	SDL_Point move_dig;
	float dz = 0;
};

