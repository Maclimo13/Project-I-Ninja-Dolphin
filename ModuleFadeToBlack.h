#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Rect;
struct SDL_Texture;

class ModuleFadeToBlack : public Module
{
public:
	ModuleFadeToBlack();
	~ModuleFadeToBlack();

	bool Start();
	update_status Update();
	bool FadeToBlack(Module* module_off, Module* module_on, float time = 2.0f);

private:

	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
	SDL_Texture* loading_screen;
	Animation loading_screen_animation;
	Animation loading_screen_animation_b;
	Module* to_disable;
	Module* to_enable;
};

#endif //__MODULEFADETOBLACK_H__
