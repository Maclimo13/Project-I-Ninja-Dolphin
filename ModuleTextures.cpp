#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{
	for (uint i = 0; i < MAX_TEXTURES; ++i)
		textures[i] = nullptr;

}

// Destructor
ModuleTextures::~ModuleTextures()
{}

// Called before render is available
bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before q	uitting
bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (int i = (MAX_TEXTURES - 1); i >= 0; --i) {
		if (textures[i] != nullptr) 
			SDL_DestroyTexture(textures[i]);
		textures[i] = nullptr;
	}

	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
	SDL_Surface* image = IMG_Load(path);
	SDL_Texture* ret = nullptr;
	if (image == NULL) {
		LOG("Failed to load image IMG_Load: %s\n", IMG_GetError());
	}
	else {
		textures[last_texture] = SDL_CreateTextureFromSurface(App->render->renderer, image);
		if (textures[last_texture] == NULL) {
			LOG("Failed to create texture from surface SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
		}
		else 
			ret = textures[last_texture++];

		SDL_FreeSurface(image);
	}
	return ret;
}
