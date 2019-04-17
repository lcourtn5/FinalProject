//Including needed libraries for game
#include "window.h"
#include <cstdio>
#include <string>
#include <map>

using namespace std;

int WindowWidth, WindowHeight;

map<string, string> myTextures;
string textureName;

class Cat{
	public:
		static const int CAT_WIDTH = 174;
		static const int CAT_HEIGHT = 180;
		
		Cat();
		void moveCat();
		void render();
		void setX(int x);
		int getX();
	private:
		int mPosX, mPosY;
};	

class Dog{
	public:
		static const int DOG_WIDTH = 244;
		static const int DOG_HEIGHT = 164;
	
		Dog();
		void jumpDog();
		void downDog();
		int getY();
		void bark();
		void render();
		void renderJump();
	private:
		int mPosX, mPosY;
};

void PlayGame(){
	bool back = 0;
	int DogY;
	bool jump = 0;
	SDL_Event e;
	Dog Raisin;	
	Cat cat1, cat2;
				
	cat2.setX(890);

	WindowWidth = 1230;
	WindowHeight = 846;
	SDL_SetWindowSize(gWindow, WindowWidth, WindowHeight);
		
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gBGTexture.render(0,0);
	
	Raisin.render();
	cat1.render();
	cat2.render();
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
						
						WindowWidth = 1099;
						WindowHeight = 780;
						SDL_SetWindowSize(gWindow, WindowWidth, WindowHeight);	
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);
						menu.render(0,0);
						SDL_RenderPresent(gRenderer);
						back = 1;
						return;
					}
				}	
			} else if(e.type == SDL_KEYDOWN){
				jump = 1;
			}
		}

		DogY = Raisin.getY();	
		if(jump == 1 && DogY > 450){
			Raisin.jumpDog();
		}
		else if(DogY != 662){
			jump = 0;
			Raisin.downDog();
		}	
		cat1.moveCat();
		cat2.moveCat();		

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		gBGTexture.render(0,0);
		
		if(DogY == 662){
			Raisin.render();
		}
		else{
			Raisin.renderJump();
		}
		cat1.render();
		cat2.render();
		SDL_RenderPresent(gRenderer);	
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
						if(x < 672 && x > 411) {
							if(y < 550 && y > 462) {
								x = 0;
								y = 0;
								PlayGame();
							}
						}

						//Check if mouse is in the credits button
						if(x < 672 && x > 411) {
							if(y < 660 && y > 570) {
								x = 0;
								y = 0;
								//Credits
								textureName = "credits";
								
								WindowWidth = 1395;
								WindowHeight = 781;
								SDL_SetWindowSize(gWindow,WindowWidth,WindowHeight);
								SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
								SDL_RenderClear(gRenderer);
								credits.render(0,0);
								SDL_RenderPresent(gRenderer);
							}
						}

						//Check if mouse is in the exit button
						if(x < 672 && x > 411) {
							if(y < 773 && y > 687) {
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
								
								WindowWidth = 1099;
								WindowHeight = 780;								
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
	mPosY = 662;
}
void Dog::bark(){

}

int Dog::getY(){
	return mPosY;
}

void Dog::jumpDog(){
	mPosY -= 5;
}
void Dog::downDog(){
	if(mPosY + 10 > 662){
		mPosY = 662;
	}
	else{
		mPosY += 5;
	}
}

void Dog::render(){
	gDogTexture.render(mPosX, mPosY);
}
void Dog::renderJump(){
	DogJump.render(mPosX, mPosY);
}

Cat::Cat(){
	mPosX = 300;
	mPosY = 662;
}

void Cat::setX(int x){
	mPosX = x;
}

int Cat::getX(){
	return mPosX;
}

void Cat::moveCat(){
	if(mPosX < -100 ){
		mPosX = 1100;
	}
	else{
		mPosX -= 5;
	}
}

void Cat::render(){
	cat.render(mPosX, mPosY);
}

