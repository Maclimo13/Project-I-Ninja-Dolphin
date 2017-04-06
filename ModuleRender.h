#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"
#define MAX_REQUEST 50

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

struct Blit_Request {
	SDL_Texture* texture;
	int priority;
	int size;
	SDL_Rect* section;
	SDL_Rect* rect;

	Blit_Request(SDL_Texture* texture, SDL_Rect* rect, int priority, int size, SDL_Rect* section) : 
		texture(texture), rect(rect), priority(priority), size(size), section(section)
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
	Blit_Request* requests[MAX_REQUEST];
};

#endif //__ModuleRenderer_H__