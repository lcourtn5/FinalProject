//Including needed libraries for game
#include "window.h"
#include <cstdio>
#include <string>
#include <map>

using namespace std;

map<string, string> myTextures;
string textureName;

void windowUpdate() {
	//Load media
	if(!loadMedia(myTextures[textureName])) {
		printf("Failed to load media!\n");
	}
	gCurrentSurface = loadSurface(myTextures[textureName]);

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

void PlayGame(){
	myTextures["background"] = "background.png";
	textureName = "background";
	windowUpdate();
	bool back = 0;
	SDL_Event e;
	while(back != 1){
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				int x, y;
				SDL_GetMouseState(&x, &y);
			
				//check if mouse is in back button in credits
				if(x < 100 && x > 0){
					if(y < 100 && y > 0 ){
						x = 0;
						y = 0;
						//Back to menu
						textureName = "menu";
						windowUpdate();
						back = 1;
					}
				}	
			}
		}	
	}
}


//Main Menu
int main(int argc, char* argv[]) {
	myTextures["menu"] = "menu.png";
	myTextures["credits"] = "Credits.PNG";

	textureName = "menu";

	//Start up SDL and create window
	if(!init()) {
		printf("Failed to initialize!\n");
	} else {
		//Load media
		if(!loadMedia(myTextures[textureName])) {
			printf("Failed to load media!\n");
		} else {
			//Main loop flag
			bool quit = false;	
			//Event handler
			SDL_Event e;
			while(!quit) {
				//Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					//User clicks the mouse down in the menu
					} else if((e.type == SDL_MOUSEBUTTONDOWN) && textureName == "menu") {
						//Get mouse position
						int x, y;
						SDL_GetMouseState(&x, &y);

						//Check if mouse if in the play button
						if(x < 779 && x > 482) {
							if(y < 632 && y > 533) {
								x = 0;
								y = 0;
								PlayGame();
							}
						}

						//Check if mouse is in the credits button
						if(x < 779 && x > 482) {
							if(y < 760 && y > 661) {
								x = 0;
								y = 0;
								//Credits
								textureName = "credits";
								windowUpdate();
							}
						}

						//Check if mouse is in the exit button
						if(x < 779 && x > 482) {
							if(y < 887 && y > 788) {
								quit = true;
							}
						}
					//User clicks the mouse down in credits
					} else if((e.type == SDL_MOUSEBUTTONDOWN) && textureName == "credits") {
						//Get mouse position
						int x, y;
						SDL_GetMouseState(&x, &y);

						//Check if mouse is in back button in credits
						if(x < 841 && x > 525) {
							if(y < 768 && y > 609) {
								x = 0;
								y = 0;
								//Back to menu
								textureName = "menu";
								windowUpdate();
							}
						}
					}
					
					gCurrentSurface = loadSurface(myTextures[textureName]);
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

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;


	SDL_Quit();

	return 0;
}
