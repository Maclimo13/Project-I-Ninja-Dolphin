#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender() : Module()
{}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	for (int i = 0; i < MAX_REQUESTS; ++i)
		requests[i] = nullptr;

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update() {
	for (int i = 0; i < MAX_REQUESTS && requests[i] != nullptr; ++i) {
		if (SDL_RenderCopy(renderer, requests[i]->texture, &requests[i]->section, &requests[i]->rect) != 0) {
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		}
		//delete requests[i];
		requests[i] = nullptr;
	}
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, int layer , int size, SDL_Rect* section)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;

	if(section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= size;
	rect.h *= size;

	Blit_Request* n_request = new Blit_Request(texture,rect,layer,*section);
	//n_request->texture = texture;
	//n_request->rect = rect;
	//n_request->priority = layer;
	//n_request->section.x = section->x;
	//n_request->section.y = section->y;
	//n_request->section.w = section->w;
	//n_request->section.h = section->h;
	if (requests[MAX_REQUESTS - 1] != nullptr) {
		ret = false;
		LOG("Blit requests overflow, cannot Blit.");
	}
	else {
		for (int i = MAX_REQUESTS - 2; i >= 0; --i) {
			if (requests[i] == nullptr && i != 0)
				continue;
			else if (i == 0)
				requests[i] = n_request;
			if (requests[i]->priority > layer) {
				requests[i + 1] = requests[i];
				requests[i] = nullptr;
			}
			else {
				requests[i + 1] = n_request;
				break;
			}

		}
	}

	return ret;
}
