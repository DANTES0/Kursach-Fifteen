#include "Game.h"
#include "time.h "

Game::Game()
{
	GameLoop = true;

	GS_width = 1024;

	GS_height = 768;

}

Game::~Game()
{
	managertexture.Dispose();

	managerinput.Dispose();

	if (renderer) SDL_DestroyRenderer(renderer);  // удаляем render

	renderer = 0;

	if (window) SDL_DestroyWindow(window); // удалаем window

	window = 0;

	SDL_Quit();
}

void Game::create(int w, int h)
{
	srand(time(0));

	GS_width = w;
	GS_height = h;

	GameLoop = true;

	InitSDL();

	managertexture.SetRender(renderer);

	sizeCell = 64; 
	dx = 0;
	dy = 0;

	int n = 0;

	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
		{
			sprite[n].setTexture(managertexture.getTexture("texture.png"));
			sprite[n].setTextureRect(i*sizeCell, j*sizeCell, sizeCell, sizeCell); 
			n++;
		}
	while (n)
	{
		int i = rand() % 4;
		int j = rand() % 4;

		if (!grid[i][j]) grid[i][j] = --n;
	}
}

void Game::InitSDL() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)	printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());

	Uint32 flagsW = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL; //SDL_WINDOW_RESIZABLE

	window = SDL_CreateWindow("Tag", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GS_width, GS_height, flagsW);

	if (!window) printf("SDL window not create! SDL Error: %s\n", SDL_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) printf("SDL render not create! SDL Error: %s\n", SDL_GetError());
}

void Game::play() {

	while (GameLoop)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); 
		SDL_RenderClear(renderer);
		update();
		render();
	}
	SDL_Quit();
}

void Game::update() {

	managerinput.update(event);

	if (managerinput.exit) GameLoop = false;

	if (!dx && !dy)
	if (managerinput.isKeyDown(SDL_BUTTON_LEFT))  
	{
		SDL_Point  pos = managerinput.getMouseCoords(); 

		int x = pos.x / sizeCell;	
		int y = pos.y / sizeCell;

		if (x < 4 - 1)	if (!grid[x + 1][y]) { dx = 1;  dy = 0; };
		if (y < 4 - 1)	if (!grid[x][y + 1]) { dx = 0;  dy = 1; };
		if (y)		if (!grid[x][y - 1]) { dx = 0;  dy = -1; };
		if (x)		if (!grid[x - 1][y]) { dx = -1; dy = 0; };

		if (dx || dy)
		{
		dig = grid[x][y];
		move_dig.x = x + dx;
		move_dig.y = y + dy;
		dz = 0;
		}
		
	}
	else if (managerinput.isKeyPressed(SDLK_ESCAPE))
	{
			GameLoop = false;
			managertexture.Dispose();
			managerinput.Dispose();
			SDL_DestroyRenderer(renderer);
			renderer = 0;
			SDL_DestroyWindow(window);
			window = 0;
	}
}

void Game::render() {


	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			int n = grid[i][j];
			sprite[n].setPosition(i*sizeCell, j*sizeCell); 
			sprite[n].draw(renderer);
		}

	if (dx || dy)
	{
		sprite[dig].move(dx * dz, dy * dz);
		sprite[dig].draw(renderer);
		dz += sizeCell / 3.0;

		if (dz >= sizeCell)
		{

			grid[move_dig.x][move_dig.y] = dig;
			grid[move_dig.x - dx][move_dig.y - dy] = 0;
			dx = dy = 0;
		}
	}
	SDL_RenderPresent(renderer);
}