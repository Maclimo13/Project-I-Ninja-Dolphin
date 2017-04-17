#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL.h"

#define PLAYER_SPEED 4
#define SPRITE_WIDTH 57
#define SPRITE_HEIGHT 49
#define LASER_COOLDOWN 100

struct SDL_Texture;
struct Collider;

enum player_state {
	IDLE = 0,
	LEFT,
	RIGHT,
	FORWARD,
	STOP

};

class ModulePlayer : public Module {
public:

	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	SDL_Texture* graphics = nullptr; //((box of the collider))
	SDL_Rect boxy; // trying to make it work
	SDL_Texture* player;
	SDL_Rect player_sprite;
	SDL_Rect player_sprite_left;
	SDL_Rect player_sprite_right;
	int player_x, player_y;
	player_state state;
	Mix_Chunk* laser_sfx;
	uint sdl_clock;
	uint sdl_shot;
	void OnCollision(Collider* c1, Collider* c2);

	Collider* player_collider;
	bool destroyed = false;
};

#endif