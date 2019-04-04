//Including needed libraries for game
#include "window.h"
#include <cstdio>
#include <string>

using namespace std;

//Main Menu
int main(int argc, char* argv[]) {
	//Start up SDL and create window
	if(!init()) {
		printf("Failed to initialize!\n");
	} else {
		//Load media
		if(!loadMedia("menu.png")) {
			printf("Failed to load media!\n");
		} else {
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while(!quit) {
				//Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					//User clicks the mouse down
					} else if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
						//Get mouse position
						int x, y;
						SDL_GetMouseState(&x, &y);

						//Check if mouse if in the play button
						if(x < 779 && x > 482) {
							if(y < 632 && y > 533) {

							}
						}
						
						//Check if mouse is in the credits button
						if(x < 779 && x > 482) {
							if(y < 760 && y > 661) {

							}
						}
						
						//Check if mouse is in the exit button
						if(x < 779 && x > 482) {
							if(y < 887 && y > 788) {
								quit = true;
							}
						}

					}

					gCurrentSurface = loadSurface("menu.png");
				}

				//Apply the image
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	//Free resources
	close(gCurrentSurface);

	SDL_Quit();

	return 0;
}
