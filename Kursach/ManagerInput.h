#pragma once

#include <SDL.h>
#include <unordered_map>

class ManagerInput
{
public:
	ManagerInput();
	~ManagerInput();

	void update(SDL_Event event);

	void Dispose();
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	void setMouseCoords(int x, int y);

	bool isKeyDown(unsigned int keyID);

	bool isKeyPressed(unsigned int keyID);

	SDL_Point  getMouseCoords() const { return _mouseCoords; }

	bool exit;

private:
	bool wasKeyDown(unsigned int keyID);

	std::unordered_map<unsigned int, bool> _keyMap;
	std::unordered_map<unsigned int, bool> _previousKeyMap;

	SDL_Point _mouseCoords;
};

