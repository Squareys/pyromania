#include "main.h"
#include "sprite.h"
#include "entity.h"
#include "enemy.h"

SDL_Surface* screen = NULL;
SDL_Event event;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);

	bool done=false;


	Sprite *sprite = new Sprite(10, 10, 20, 20);
	Sprite *esprite = new Sprite(10, 10, 15, 15);
	Entity *entity = new Entity(10, 10, sprite);
	Enemy* enemy = new Enemy(60, 60, esprite);
	enemy->setTarget(entity);

	bool w_pressed = false;
	bool a_pressed = false;
	bool s_pressed = false;
	bool d_pressed = false;

	while(!done) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				done=true;
			}

			if (event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
				case SDLK_w:
					w_pressed = true;
					break;
				case SDLK_a:
					a_pressed = true;
					break;
				case SDLK_s:
					s_pressed = true;
					break;
				case SDLK_d:
					d_pressed = true;
					break;
				default:
					break;
				}
			} else if (event.type == SDL_KEYUP){
				switch(event.key.keysym.sym){
				case SDLK_w:
					w_pressed = false;
					break;
				case SDLK_a:
					a_pressed = false;
					break;
				case SDLK_s:
					s_pressed = false;
					break;
				case SDLK_d:
					d_pressed = false;
					break;
				default: break;
				}
			}
		}

		float dirX = d_pressed ? 1.0 : 0.0;
		dirX -= a_pressed ? 1.0 : 0.0;
		float dirY = s_pressed ? 1.0 : 0.0;
		dirY -= w_pressed ? 1.0 : 0.0;

		entity->setDirection(dirX, dirY);

		// fill the screen with black color
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 123, 123, 123));

		entity->update();
		enemy->update();
		sprite->draw(screen);
		esprite->draw(screen);

		// update the screen buffer
		SDL_Flip(screen);
	}

	SDL_Quit();

	return 0;
}
