#ifndef __ModuleStageIntro_H__
#define __ModuleStageIntro_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleStageIntro : public Module {
public:

	ModuleStageIntro();
	~ModuleStageIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

private:

	SDL_Texture* title_texture = nullptr;
	Mix_Music* music;
	Animation title_screen;
};


#endif //__ModuleStageIntro_H__