#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"
#include "SDL\include\SDL.h"
#define MAX_REQUESTS 1000

struct SDL_Renderer;
struct SDL_Texture;

struct Blit_Request {
	SDL_Texture* texture;
	int priority;
	SDL_Rect section;
	SDL_Rect rect;

	Blit_Request() : texture(nullptr) 
	{}
	
	~Blit_Request() {}

	Blit_Request(SDL_Texture* texture, SDL_Rect rect, int priority, SDL_Rect section) : 
		texture(texture), rect(rect), priority(priority), section(section)
	{}
};

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, int layer = 1, int size = 1, SDL_Rect* section = nullptr);

public:
	SDL_Renderer* renderer = nullptr;

private:
	Blit_Request* requests[MAX_REQUESTS];
};

#endif //__ModuleRenderer_H__