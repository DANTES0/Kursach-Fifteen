#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SDL_Sprite
{
public:
	SDL_Sprite();

	~SDL_Sprite();

	void draw(SDL_Renderer*	renderer);  

	void setPosition(SDL_FPoint position); 
	void setPosition(const float & x, const float &y);

	void setTexture(SDL_Texture* texture);  
	void setTextureRect(SDL_Rect rectTxt);
	void setTextureRect(const int & x, const int & y, const int & w, const int & h);
	void setTextureRect(const float & x, const float & y, const float & w, const float & h);

	SDL_FPoint getPosition() { return _position; }  

	SDL_Texture* getTexture() { return _texture; }

	SDL_Rect getTextureRect() {	return _rectTxt; }

	SDL_FRect getRect();

	void move(SDL_FPoint move); 
	void move(float x, float y);
	void move(int x, int y);

private:

	void init();
	float			_angel;
	SDL_FPoint		_position;
	SDL_FPoint		_scale;
	SDL_FPoint		_origin;
	SDL_Texture*	_texture;
	SDL_Rect		_rectTxt;
	SDL_Color		_color;
};

