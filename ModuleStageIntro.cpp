#include "ModuleStageIntro.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTransition.h"
#include "ModuleStage2.h"
#include "ModulePlayer.h"
#include "ModuleStage1.h"


ModuleStageIntro::ModuleStageIntro() {
}

ModuleStageIntro::~ModuleStageIntro() {
}

bool ModuleStageIntro::Start() {
	bool ret = true;

	music = App->audio->LoadMusic("music/fighting_thunder.ogg");
	title_texture = App->textures->Load("revamp_spritesheets/attract_screen.png");

	title_screen.SetUp(0, 0, 518, 592, 6, 11, "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10");
	title_screen.speed = 0.15f;
	
	
	App->audio->PlayMusic(music);
	App->audio->MusicVolume(25);
	App->stage1->Disable();
	

	return ret;
}

update_status ModuleStageIntro::Update() {

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_REPEAT)
		App->transition->Transition(this, App->stage1, 0.8f);

	App->render->Blit(title_texture, (SCREEN_WIDTH-title_screen.frames[0].w)/2, (SCREEN_HEIGHT - title_screen.frames[0].h) / 2, 1, 1, &title_screen.GetCurrentFrame());

	return UPDATE_CONTINUE;
}

bool ModuleStageIntro::CleanUp() {
	bool ret = true;
	App->audio->StopMusic();
	App->intro->Disable();
	title_screen.CleanUp();

	return ret;
}
