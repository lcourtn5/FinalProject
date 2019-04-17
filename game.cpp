//Including needed libraries for game
#include "window.h"
#include <cstdio>
#include <string>
#include <map>

using namespace std;

int WindowWidth, WindowHeight;

map<string, string> myTextures;
string textureName;

class Dog{
	public:
		static const int DOG_WIDTH = 20;
		static const int DOG_HEIGHT = 20;
	
		Dog();
		void handleEvent(SDL_Event& e);
		void jump();
		void render();
	private:
		int mPosX, mPosY;
};

void PlayGame(){
	bool back = 0;
	SDL_Event e;
	Dog Raisin;	
	
	WindowWidth = 1230;
	WindowHeight = 846;
	SDL_SetWindowSize(gWindow, WindowWidth, WindowHeight);
		
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gBGTexture.render(0,0);
	
	Raisin.render();
	SDL_RenderPresent(gRenderer);	
		
	
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
						
						WindowWidth = 1112;
						WindowHeight = 790;
						SDL_SetWindowSize(gWindow, WindowWidth, WindowHeight);	
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);
						menu.render(0,0);
						SDL_RenderPresent(gRenderer);
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
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);
			menu.render(0,0);
			SDL_RenderPresent(gRenderer);
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
						if(x < 680 && x > 418) {
							if(y < 555 && y > 460) {
								x = 0;
								y = 0;
								PlayGame();
							}
						}

						//Check if mouse is in the credits button
						if(x < 680 && x > 418) {
							if(y < 665 && y > 575) {
								x = 0;
								y = 0;
								//Credits
								textureName = "credits";
								
								WindowWidth = 1401;
								WindowHeight = 790;
								SDL_SetWindowSize(gWindow,WindowWidth,WindowHeight);
								SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
								SDL_RenderClear(gRenderer);
								credits.render(0,0);
								SDL_RenderPresent(gRenderer);
							}
						}

						//Check if mouse is in the exit button
						if(x < 680 && x > 418) {
							if(y < 776 && y > 690) {
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
								
								WindowWidth = 1112;
								WindowHeight = 790;								
								SDL_SetWindowSize(gWindow,WindowWidth,WindowHeight);
								SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
								SDL_RenderClear(gRenderer);
								menu.render(0,0);
								SDL_RenderPresent(gRenderer);
							}
						}
					}
				}
			}
		}
	}

	//Free resources
	close();


	SDL_Quit();

	return 0;
}

Dog::Dog(){
	mPosX = 0;
	mPosY = 0;
}

void Dog::jump(){
	
}

void Dog::render(){
	gDogTexture.render(mPosX, mPosY);
}

