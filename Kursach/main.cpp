#include "Game.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int main(int argc, char** argv)
{
    int j = 1;
    srand(time(NULL));
    SDL_Event event;
    bool flag = true, f = false, t = false;
    SDL_Color col = { 0,0,0 }; //Цвет текста
    SDL_Rect pos = { 20,45,200,75 }, pos1 = { 20,150,200,75 }; //Позиция текста 1
    SDL_Surface* surface = NULL, * surface1 = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl; return 1; }
    if (TTF_Init() == -1) { return 6; }
    atexit(TTF_Quit);
    TTF_Font* font;
    font = TTF_OpenFont("ofont.ru_Zametka Parletter.ttf", 72);
    if (!font) { return 1; }

    SDL_Window* win = SDL_CreateWindow("Tag", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == NULL) { cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl; return 1; }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) { cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl; return 1; }

    SDL_Surface* bmp = SDL_LoadBMP("five.bmp");
    if (bmp == NULL) { cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl; return 1; }

    surface = TTF_RenderUTF8_Solid(font, "Play", col);

    if (surface == NULL) { return 3; }

    surface1 = TTF_RenderUTF8_Solid(font, "Exit", col);
    if (surface1 == NULL) { return 3; }

    col.r = col.g = col.b = 0;

    SDL_Texture* background = SDL_CreateTextureFromSurface(ren, bmp);
    if (background == NULL) { cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl; return 1; }
    SDL_FreeSurface(bmp);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surface);
    if (tex == NULL) { cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl; return 1; }

    SDL_Texture* text = SDL_CreateTextureFromSurface(ren, surface1);
    if (tex == NULL) { cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl; return 1; }

    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface1);

    while (j)
    {
        SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, background, NULL, NULL);
        SDL_RenderCopy(ren, tex, NULL, &pos);
        SDL_RenderCopy(ren, text, NULL, &pos1);
        if (SDL_PollEvent(&event))
        {

            if (event.type == SDL_MOUSEMOTION)
            {
                int x, y;
                x = event.motion.x;
                y = event.motion.y;
                if (x > 20 && x < 250 && y>35 && y < 100)
                    f = true;
                else
                    f = false;
                if (x > 20 && x < 250 && y>150 && y < 220)
                    t = true;
                else
                    t = false;
            }
            if (event.type == SDL_QUIT)
            {
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(tex);
                SDL_DestroyTexture(text);
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(win);
                TTF_CloseFont(font);
                SDL_Quit();
                return 0;
            }
        }
        if (f)
        {
            SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(ren, pos.x - 10, pos.y + pos.h - 10, pos.w + 50, pos.y + pos.h - 10);
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                
                Game game;
                game.create(256, 256);
                game.play();
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(tex);
                SDL_DestroyTexture(text);
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(win);
                TTF_CloseFont(font);
                SDL_Quit();
                j = 0;
                
            }
        }
        if (t)
        {
            SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(ren, pos1.x - 10, pos1.y + pos1.h - 10, pos1.w + 50, pos1.y + pos1.h - 10);
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(tex);
                SDL_DestroyTexture(text);
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(win);
                TTF_CloseFont(font);
                SDL_Quit();
                return 0;
            }
        }
        SDL_RenderPresent(ren);
    }
    system("pause void");
	return 0;
}