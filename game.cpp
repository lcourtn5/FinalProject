//Including needed libraries for game
#include "window.h"
#include <cstdio>
#include <string>
#include <map>
#include <set>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

int WindowWidth, WindowHeight;

map<char, set<string> > Winners;
map<string, string> myTextures;
string textureName;

class Cat{
	public:
		static const int CAT_WIDTH = 174;
		static const int CAT_HEIGHT = 180;
		
		Cat();
		void moveCat(bool & reset, int & score);
		void render(int cat);
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
		bool checkCatPos(Cat cat, bool jump);
		void jumpDog();
		void downDog();
		void setX(int x);
		int getY();
		int getX();
		void bark();
		void moveRight();
		void render(int & timer);
		void renderJump();
	private:
		int mPosX, mPosY;
};

void RenderGame(bool lose, int DogY, bool begin, int &time, int &score, string &scoreText, int cat1num, int cat2num, Cat cat1, Cat cat2, Dog Raisin, TTF_Font* Sans);
void ReturnMenu();
void ReadIn();
void Save();
void PlayGame();
void WinnerScreen();

//Main Menu
int main(int argc, char* argv[]) {
	
	myTextures["menu"] = "Pictures/menu.png";
	myTextures["credits"] = "Credits.PNG";

	textureName = "menu";
	
	ReadIn();
	
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
			WinnerButton.render(828,0);
			MusicOn.render(0,0);
			SDL_RenderPresent(gRenderer);
			//Main loop flag
			bool quit = false;	
			//Event handler
			SDL_Event e;
			if(Mix_PlayingMusic() == 0){
				Mix_PlayMusic(MenuMusic, -1);
				MusicOn.render(0,0);
			}
			while(!quit) {
				//Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					//User clicks the mouse down in the menu
					}
					 else if((e.type == SDL_MOUSEBUTTONDOWN) && textureName == "menu") {
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
								if(Mix_PausedMusic() == 1){
									MusicOff.render(0,0);
								}	
								else{
									MusicOn.render(0,0);
								}
								SDL_RenderPresent(gRenderer);
							}
						}

						//Check if mouse is in the exit button
						if(x < 672 && x > 411) {
							if(y < 773 && y > 687) {
								quit = true;
							}
						}
						
						if(x < 1099 && x > 828){
							if(y < 70 && y > 0){
								WinnerScreen();
							}
						}					

	
						//check if mouse in on music button
						if(x < 100 && x > 0){
							if(y < 100 && y > 0){
								if(Mix_PausedMusic() == 1){
									Mix_ResumeMusic();
										
									SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
									SDL_RenderClear(gRenderer);
									menu.render(0,0);
									WinnerButton.render(828,0);
									MusicOn.render(0,0);
									SDL_RenderPresent(gRenderer);
								}
								else{
									Mix_PauseMusic();
									
									SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
									SDL_RenderClear(gRenderer);
									menu.render(0,0);
									WinnerButton.render(828,0);
									MusicOff.render(0,0);
									SDL_RenderPresent(gRenderer);
								}
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
								ReturnMenu();
							}
						}

						//check if mouse is on music button
						if(x < 100 && x > 0){
							if(y < 100 && y > 0){
								if(Mix_PausedMusic() == 1){
									Mix_ResumeMusic();
										
									SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
									SDL_RenderClear(gRenderer);
									credits.render(0,0);
									MusicOn.render(0,0);
									SDL_RenderPresent(gRenderer);
								}
								else{
									Mix_PauseMusic();
									
									SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
									SDL_RenderClear(gRenderer);
									credits.render(0,0);
									MusicOff.render(0,0);
									SDL_RenderPresent(gRenderer);
								}
							}
						}
					
					}
				}
			}
		}
	}

	//Free resources
	close();
	Save();	
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	return 0;
}

Dog::Dog(){
	mPosX = 0;
	mPosY = 662;
}
void Dog::bark(){

}
void Dog::setX(int x){
	mPosX = x;
}

int Dog::getY(){
	return mPosY;
}

int Dog::getX(){
	return mPosX;
}

bool Dog::checkCatPos(Cat cat, bool jump ){
	if(cat.getX() < 195 && jump == 0){
		return true;
	}	
	else{
		return false;
	}
}	

void Dog::jumpDog(){
	mPosY -= 5;
}
void Dog::moveRight(){
	mPosY = 662;
	mPosX += 10;
}

void Dog::downDog(){
	if(mPosY + 10 > 662){
		mPosY = 662;
	}
	else{
		mPosY += 5;
	}
}

void Dog::render(int & timer){
	//determines which picture to render
	if(timer < 10){
		gDogTexture.render(mPosX, mPosY);
		timer++;
	}
	else if(timer <= 20){
		RaisinWalk.render(mPosX, mPosY);
		timer++;
	} else if(timer > 20){
		timer = 0;
		gDogTexture.render(mPosX, mPosY);
	}
}
void Dog::renderJump(){
	DogJump.render(mPosX, mPosY);
}

Cat::Cat(){
	mPosX = 500;
	mPosY = 662;
}

void Cat::setX(int x){
	mPosX = x;
}

int Cat::getX(){
	return mPosX;
}

void Cat::moveCat(bool & reset, int & score){
	if(mPosX < -100 ){
		mPosX = 1100;
		reset = true;
		score += 10;
	}
	else{
		mPosX -= 5;
	}
}

void Cat::render(int cat){
	cats[cat].render(mPosX, mPosY);
}


void RenderGame(bool lose, int DogY, bool begin, int &time, int &score, string &scoreText, int cat1num, int cat2num, Cat cat1, Cat cat2, Dog Raisin, TTF_Font* Sans){
	
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	gBGTexture.render(0,0);

	scoreText += to_string(score);

	//render surface for text
	surfaceMessage = TTF_RenderText_Solid(Sans, scoreText.c_str(), White);
	Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);	

	SDL_QueryTexture(Message, NULL, NULL, &MessageRect.w, &MessageRect.h);
	MessageRect.x = 1220 - MessageRect.w;
	MessageRect.y = 0;

	//renders text
	SDL_RenderCopy(gRenderer, Message, NULL, &MessageRect);

	scoreText = "Score: ";	

	if(begin == 1){
		OKButton.render(575, 550);
		BeginPrompt.render(265,240);
	}
	BackButton.render(-10,-10);
	if(lose == 1){
		LosePrompt.render(335,150);
		MainButton.render(501,475);
		RetryButton.render(540,575);
	}

	if(DogY == 662){
		Raisin.render(time);
	}
	else{
		Raisin.renderJump();
	}
	
	cat1.render(cat1num);
	cat2.render(cat2num);
	SDL_RenderPresent(gRenderer);	
}


void ReturnMenu(){
	
	//Back to menu
	textureName = "menu";

	//renders main menu
	WindowWidth = 1099;
	WindowHeight = 780;
	SDL_SetWindowSize(gWindow, WindowWidth, WindowHeight);	
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	menu.render(0,0);
	WinnerButton.render(828,0);
	if(Mix_PausedMusic() == 1){
		MusicOff.render(0,0);
	}	
	else{
		MusicOn.render(0,0);
	}
	SDL_RenderPresent(gRenderer);

	return;

}

void ReadIn(){
	char last;
	string first;
	
	while(cin >> first >> last){
		Winners[last].insert(first);
	}	
	
}

void Save(){
	ofstream fout;
	fout.open("SavedWinners.txt");
	map<char, set<string> >::iterator mit;
	set<string>::iterator sit;
	
	for(mit = Winners.begin(); mit != Winners.end(); mit++){
		for(sit = mit->second.begin(); sit != mit->second.end(); sit++){
			fout << *sit << " " << mit->first << endl;
		}	
	}

	fout.close();
}

void PlayGame(){
	TTF_Font* Sans = TTF_OpenFont("Font.ttf", 40);
	string scoreText;
	string first;
	char last;
	string winnerText = "Enter First Name and Last Inital: ";
	scoreText = "Score: ";
	bool retry = 0;
	int score = 0;
	int time = 0;
	int scrollingOffset = 0;
	bool play = 0;
	bool back = 0;
	int DogY = 662;
	bool hasjump = 0;
	bool resetcat1 = false, resetcat2 = false;
	bool jump = 0;
	bool begin = 1;
	int cat1num, cat2num;
	SDL_Event e;
	Dog Raisin;	
	Cat cat1, cat2;
	bool cat1Lose = false, cat2Lose = false;
	bool lose = 0;				
	cat2.setX(1100);
		
	//resize window
	WindowWidth = 1230;
	WindowHeight = 840;
	SDL_SetWindowSize(gWindow, WindowWidth, WindowHeight);
		
	//determines which color cat
	cat1num = rand() % 3;
	cat2num = rand() % 3;
	
	RenderGame(lose, DogY, begin, time, score, scoreText, cat1num, cat2num, cat1, cat2, Raisin, Sans);
	begin = 0;		
	
	while(back != 1){
		//determines if the user has selected ok yet
		if(play == 1){			
			while(SDL_PollEvent(&e) != 0){
				retry = 0;
				//if mouse is pressed it determines if it was in the back button area
				if(e.type == SDL_MOUSEBUTTONDOWN){
					int x, y;
					SDL_GetMouseState(&x, &y);

					//check if mouse is in back button in credits
					if(x < 100 && x > 0){
						if(y < 100 && y > 0 ){
							x = 0;
							y = 0;
							ReturnMenu();
							return;
						}
					}	
				//if any key is pressed Raisin jumps
				} else if(e.type == SDL_KEYDOWN){
					if(hasjump == 0){
						jump = 1;
						hasjump = 1;
					//	Mix_PlayChannel(-1,JumpMusic, 0);
					}
				}
			}
			
			//makes Raisin jump
			DogY = Raisin.getY();	
			if(jump == 1 && DogY > 450){
				Raisin.jumpDog();
			}
			else if(DogY != 662){
				jump = 0;
				Raisin.downDog();
				if(Raisin.getY() == 662){
					hasjump = 0;
				}
			} 

			//moves the cat and determines if the cat was reset to right side
			cat1.moveCat(resetcat1, score);
			cat2.moveCat(resetcat2, score);
			
			//if cat was reset it determines new color
			if(resetcat1 == true){
				cat1num = rand() % 3;
				resetcat1 = false;
			}

			if(resetcat2 == true){
				cat2num = rand() % 3;
				resetcat2 = false;
			}		
	
			//determines if someone has lost the game
			cat1Lose = Raisin.checkCatPos(cat1, hasjump);
			cat2Lose = Raisin.checkCatPos(cat2, hasjump);
			
			if(cat1Lose == true || cat2Lose == true){
				lose = 1;
				RenderGame(lose, DogY,begin,time,score,scoreText,cat1num,cat2num,cat1,cat2,Raisin,Sans);
				lose = 0;
				while(retry == 0){
					while(SDL_PollEvent(&e) != 0){
						//if mouse is pressed it determines if it was in the back button area
						if(e.type == SDL_MOUSEBUTTONDOWN){
							int x, y;
							SDL_GetMouseState(&x, &y);

							//check if mouse is in back button
							if((x < 729 && x > 501) || (x < 100 && x > 0)){
								if((y < 533 && y > 475) || (y < 100 && y > 0)){
									x = 0;
									y = 0;
									ReturnMenu();
									return;
								}
							}
							
							if(x < 689  && x > 540){
								if(y < 633  && y > 575){
									retry = 1;
									score = 0;
									cat1.setX(500);
									cat2.setX(1100);
								}
							}
						}
					}
				}
			}

			if(score < 100){	
				//makes the background move
				--scrollingOffset;
				if(scrollingOffset < -gBGTexture.getWidth()){
					scrollingOffset = 0;
				}	
				
				RenderGame(lose,DogY,begin,time,score,scoreText,cat1num,cat2num,cat1,cat2,Raisin,Sans);
			
			} else{
				while(Raisin.getX() < 300){
					Raisin.moveRight();
					
					//makes the background move
					--scrollingOffset;
					if(scrollingOffset < -gBGTexture.getWidth()){
						scrollingOffset = 0;
					}	

					//render new screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					gBGTexture.render(scrollingOffset,0);
					gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0);
					BackButton.render(-10,-10);		

					Raisin.render(time);
					
					WinImage.render(393,151);
					OKButton.render(550, 650);				
	
					Bone.render(550,725);
													
					surfaceWin = TTF_RenderText_Solid(Sans, winnerText.c_str(), White);
					WinText = SDL_CreateTextureFromSurface(gRenderer, surfaceWin);

					SDL_QueryTexture(WinText, NULL, NULL, &WinRect.w, &WinRect.h);
					WinRect.x = 615 - (WinRect.w / 2);
					WinRect.y = 550;
					
					SDL_RenderCopy(gRenderer, WinText, NULL, &WinRect); 	
	
					scoreText += "100";

					//render surface for text
					surfaceMessage = TTF_RenderText_Solid(Sans, scoreText.c_str(), White);
					Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);	
					
					SDL_QueryTexture(Message, NULL, NULL, &MessageRect.w, &MessageRect.h);
					MessageRect.x = 1220 - MessageRect.w;
					MessageRect.y = 0;

					//renders text
					SDL_RenderCopy(gRenderer, Message, NULL, &MessageRect);

					scoreText = "Score: ";	
					SDL_RenderPresent(gRenderer);
				}
				back = 0;
				while(back == 0){
					//render screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					gBGTexture.render(0,0);
					BackButton.render(-10,-10);		

					Raisin.render(time);

					Bone.render(550,725);

					WinImage.render(393,151);
					OKButton.render(550, 650);

					scoreText += "100";

					//render surface for text
					surfaceMessage = TTF_RenderText_Solid(Sans, scoreText.c_str(), White);
					Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);	

					surfaceWin = TTF_RenderText_Solid(Sans, winnerText.c_str(), White);
					WinText = SDL_CreateTextureFromSurface(gRenderer, surfaceWin);

					SDL_QueryTexture(WinText, NULL, NULL, &WinRect.w, &WinRect.h);
					WinRect.x = 615 - (WinRect.w / 2);
					WinRect.y = 550;

					//renders text
					SDL_RenderCopy(gRenderer, WinText, NULL, &WinRect); 	

					SDL_QueryTexture(Message, NULL, NULL, &MessageRect.w, &MessageRect.h);
					MessageRect.x = 1220 - MessageRect.w;
					MessageRect.y = 0;

					//renders text
					SDL_RenderCopy(gRenderer, Message, NULL, &MessageRect);

					scoreText = "Score: ";	
					SDL_RenderPresent(gRenderer);



					while(SDL_PollEvent(&e) != 0){
						if(e.type == SDL_KEYDOWN){
							if(e.key.keysym.sym == SDLK_BACKSPACE && winnerText.length() != 34){
								winnerText.pop_back();
							}
						}
						else if(e.type == SDL_TEXTINPUT){
							winnerText += e.text.text;
						}

						if(e.type == SDL_MOUSEBUTTONDOWN){
							int x, y;
							SDL_GetMouseState(&x, &y);

							if((x < 631 && x > 550) || (x < 100 && x > 0)){
								if((y < 725 && y > 650) || (y < 100 && y > 0)){

									x = 0;
									y = 0;
									ReturnMenu();
									first = winnerText.substr(34,winnerText.length() - 34 - 2);
									last = winnerText[winnerText.length() - 1];
									if(first != "" && last != ' '){
										Winners[last].insert(first);
									}	
									return;


								} 
							}
						}			
					}
				}	
			}	
		//if user has not selected ok yet
		}else {
			while(SDL_PollEvent(&e) != 0){
				if(e.type == SDL_MOUSEBUTTONDOWN){
					int x, y;
					SDL_GetMouseState(&x, &y);

					if(x < 655 && x > 575){
						if(y < 625 && y > 550){
							x = 0;
							y = 0;

							play = 1;
							RenderGame(lose, DogY,begin,time,score,scoreText,cat1num,cat2num,cat1,cat2,Raisin,Sans);
						
						}
					}else{
						if(x < 100 && x > 0){
							if(y < 100 && y > 0){	
								x = 0;
								y = 0;
								ReturnMenu();
								return;
							}
						}
					}	
				}
			}	
		}
	}
}

void WinnerScreen(){
	SDL_Event e;
	TTF_Font* Sans = TTF_OpenFont("Font.ttf", 40);
	bool space = 0;
	char winnerL;
	string winnerLast = "", winnerFirst = "";
	string view;
	string winnerFound;
	map<char, set<string> >::iterator mit;	
	
	while(true){
		//resize window
		WindowWidth = 1280;
		WindowHeight = 800;
		SDL_SetWindowSize(gWindow, WindowWidth, WindowHeight);

		//render new screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		
		WinnerTab.render(0,0);
		BackButton.render(-10,-10);

		view = "Enter Last Initial and First Name: " +  winnerLast + " " + winnerFirst;
		//render Text
		surfaceWin = TTF_RenderText_Solid(Sans, view.c_str() , Blue);
		WinText = SDL_CreateTextureFromSurface(gRenderer, surfaceWin);

		SDL_QueryTexture(WinText, NULL, NULL, &WinRect.w, &WinRect.h);
		WinRect.x = 640 - (WinRect.w / 2);
		WinRect.y = 400;

		mit = Winners.find(winnerL);
		if(mit != Winners.end()){
			if(mit->second.find(winnerFirst) != mit->second.end()){
				winnerFound = "Winner Found!";
			}
			else{
				winnerFound = "No Winner Found!";
			}
		}
		else{
			winnerFound = "No Winner Found!";
		}
											
		//render surface for text
		surfaceMessage = TTF_RenderText_Solid(Sans, winnerFound.c_str(), Blue);
		Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);	

		SDL_QueryTexture(Message, NULL, NULL, &MessageRect.w, &MessageRect.h);
		MessageRect.x = 640 - (MessageRect.w / 2);
		MessageRect.y = 500;

		//renders text
		SDL_RenderCopy(gRenderer, Message, NULL, &MessageRect);

		//renders text
		SDL_RenderCopy(gRenderer, WinText, NULL, &WinRect); 	
		SDL_RenderPresent(gRenderer);

		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				int x,y;
				SDL_GetMouseState(&x,&y);
				if(x < 100 && x > 0){
					if(y < 100 && y > 0){
						x = 0;
						y = 0;
						ReturnMenu();
						return;
					}
				}
			}

			if(e.type == SDL_KEYDOWN){
				if(e.key.keysym.sym == SDLK_BACKSPACE && winnerFirst.length() != 0){
					winnerFirst.pop_back();
				}
				else if(e.key.keysym.sym == SDLK_BACKSPACE && winnerFirst.length() == 0 && space == 1){
					space = 0;
				}
				else if(e.key.keysym.sym == SDLK_BACKSPACE && winnerLast.length() != 0 && space == 0){
					winnerLast.pop_back();
				}
			}
			else if(e.type == SDL_TEXTINPUT){
				if(e.text.text[0] == ' '){	
					space = 1;
				}
				else if(space == 1){
					winnerFirst += e.text.text;
				}
				else{
					winnerL = e.text.text[0];
					winnerLast += e.text.text;
				}
			}
		}
	}
}
