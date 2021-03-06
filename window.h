#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <cstdio>
#include <string>
#include <vector>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
using namespace std;

const int SCREEN_WIDTH = 1099;
const int SCREEN_HEIGHT = 780;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Renderer* gRenderer = NULL;

//declares all variables needed
SDL_Surface * surfaceMessage;
SDL_Texture * Message;
SDL_Surface * surfaceWin;
SDL_Texture * WinText;

SDL_Rect WinRect;
SDL_Rect MessageRect;

Mix_Music *MenuMusic = NULL;
Mix_Chunk *JumpMusic = NULL;

//saves different colors
SDL_Color White = {255,255,255};
SDL_Color Orange = {235,105,0};
SDL_Color Blue = { 0, 51, 102};

class LTexture{
        public:
                //Initializes variables
                LTexture();
                //Deallocates memory
                ~LTexture();
                //Loads image at specified path
                bool loadFromFile( std::string path );
                #ifdef _SDL_TTF_H
                //Creates image from font string
                bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
                #endif
                //Deallocates texture
                void free();
                //Set color modulation
                void setColor( Uint8 red, Uint8 green, Uint8 blue );
                //Set blending
                void setBlendMode( SDL_BlendMode blending );
                //Set alpha modulation
                void setAlpha( Uint8 alpha );
                //Renders texture at given point
                void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
                //Gets image dimensions
                int getWidth();
                int getHeight();
        private:
                //The actual hardware texture
                SDL_Texture* mTexture;
                //Image dimensions
                int mWidth;
                int mHeight;
};

//declare all textures needed
LTexture gBGTexture;
LTexture gDogTexture;
LTexture menu;
LTexture credits;
vector<LTexture> cats;
LTexture DogJump;
LTexture BeginPrompt;
LTexture OKButton;
LTexture BackButton, MusicOn, MusicOff;
LTexture RaisinWalk, WinImage;
LTexture LosePrompt, MainButton, RetryButton, Bone;
LTexture WinnerTab;
LTexture WinnerButton;

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	} else {
		TTF_Init();	
		//Create window
		gWindow = SDL_CreateWindow("Raisin Run", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if(gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		} else {
			
			//create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer == NULL){
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else{
				//initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				} else {
					//Get window surface
					gScreenSurface = SDL_GetWindowSurface(gWindow);
				}

				if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

//loads all pictures and music files
bool loadMedia(string file) {
	//Loading success flag
	bool success = true;
	cats.resize(3);
	if(!menu.loadFromFile(file)){
		printf("fail to load background texture\n");
		success = false;
	}
	if(!credits.loadFromFile("Pictures/Credits.PNG")){
		printf("fail to load background texture\n");
		success = false;
	}	
	if(!gBGTexture.loadFromFile("Pictures/background.png")){
		printf("failed to load background texture\n" );
		success = false;
	}
	if(!gDogTexture.loadFromFile("Pictures/RaisinFullBody.png")){
		printf("failed to load dog texture\n");
		success = false;
	}
	if(!cats[0].loadFromFile("Pictures/cat.png")){
		printf("failed to load cat texture\n");
		success = false;
	}	
	if(!cats[1].loadFromFile("Pictures/cat2.png")){
		printf("failed to load second cat texture\n");
		success = false;
	}
	if(!cats[2].loadFromFile("Pictures/cat3.png")){
		printf("failed to load third cat texture\n");
		success = false;
	}
	if(!DogJump.loadFromFile("Pictures/RaisinJumping.png")){
		printf("failed to load jump texture\n");
		success = false;
	}
	if(!BeginPrompt.loadFromFile("Pictures/BeginPrompt.png")){
		printf("failed to load begin prompt texture\n");
		success = false;
	}
	if(!OKButton.loadFromFile("Pictures/OKButton.png")){
		printf("failed to load OK Button texture\n");
		success = false;
	}
	if(!BackButton.loadFromFile("Pictures/BackButton.png")){
		printf("failed to load Back Button texture\n");
		success = false;
	}
	if(!RaisinWalk.loadFromFile("Pictures/RaisinWalk.png")){
		printf("failed to load walking raisin texture\n");
		success = false;	
	}	

	if(!LosePrompt.loadFromFile("Pictures/LosePrompt.png")){
		printf("failed to Lose Prompt texture\n");
		success = false;	
	}	
	if(!MainButton.loadFromFile("Pictures/MainButton.png")){
		printf("failed to Main Button texture\n");
		success = false;	
	}	
	if(!RetryButton.loadFromFile("Pictures/RetryButton.png")){
		printf("failed to Retry Button texture\n");
		success = false;	
	}	
	if(!Bone.loadFromFile("Pictures/Bone.png")){
		printf("failed to load Bone texture\n");
		success = false;
	}
	if(!WinImage.loadFromFile("Pictures/WinImage.png")){
		printf("failed to load Win Image texture\n");
		success = false;
	}
	if(!WinnerTab.loadFromFile("Pictures/WinnerTab.png")){
		printf("Failed to load Window Tab Texture\n");
		success = false;
	}
	if(!WinnerButton.loadFromFile("Pictures/WinnerButton.png")){
		printf("Failed to load Winner Button Texture\n");
		success = false;
	}

	//load music
	MenuMusic = Mix_LoadMUS("DogSong.mp3");
	if(MenuMusic == NULL){
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	if(!MusicOn.loadFromFile("Pictures/MusicOn.png")){
		printf("failed to load music on texture\n");
		success = false;
	}	
	if(!MusicOff.loadFromFile("Pictures/MusicOff.png")){
		printf("failed to load music off texture\n");
		success = false;
	}
	
	JumpMusic = Mix_LoadWAV("Bark.mp3");
	if(JumpMusic == NULL){
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}	
		
	return success;
}

//frees all surfaces and textures and sounds
void close() {
	//Deallocated surface
	gBGTexture.free();
	gDogTexture.free();
	credits.free();
	menu.free();
	for(int i = 0; i < cats.size(); i++){
		cats[i].free();
	}	
	MusicOn.free();
	MusicOff.free();
	DogJump.free();
	BeginPrompt.free();
	OKButton.free();
	BackButton.free();
	RaisinWalk.free();
	WinImage.free();
	LosePrompt.free();
	MainButton.free();
	RetryButton.free();
	WinnerTab.free();
	Bone.free();
	WinnerButton.free();
	Mix_FreeMusic(MenuMusic);
	MenuMusic = NULL;
	Mix_FreeChunk(JumpMusic);
	JumpMusic = NULL;	
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyRenderer (gRenderer);
	SDL_DestroyTexture(WinText);
	SDL_FreeSurface(surfaceWin);
	//Make sure to put SDL_Quit at the end of main game
}

//given to us by SDL

LTexture::LTexture(){
        //Initialize
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
}

LTexture::~LTexture(){
        //Deallocate
        free();
}

bool LTexture::loadFromFile( std::string path ){
        //Get rid of preexisting texture
        free();
        //The final texture
        SDL_Texture* newTexture = NULL;
        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == NULL ){
                printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        }
        else{
                //Color key image
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
                //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( newTexture == NULL ){
                        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
                }
                else{
                        //Get image dimensions
                        mWidth = loadedSurface->w;
                        mHeight = loadedSurface->h;
                }
                //Get rid of old loaded surface
                SDL_FreeSurface( loadedSurface );
        }
        //Return success
        mTexture = newTexture;
        return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor ){
        //Get rid of preexisting texture
        free();
        //Render text surface
        SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
        if( textSurface != NULL ){
                //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
                if( mTexture == NULL ){
                        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
                }
                else{
                        //Get image dimensions
                        mWidth = textSurface->w;
                        mHeight = textSurface->h;
                }
                //Get rid of old surface
                SDL_FreeSurface( textSurface );
        }
        else{
                printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        //Return success
        return mTexture != NULL;
}
#endif

void LTexture::free(){
        //Free texture if it exists
        if( mTexture != NULL ){
                SDL_DestroyTexture( mTexture );
                mTexture = NULL;
                mWidth = 0;
                mHeight = 0;
        }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
        //Modulate texture rgb
        SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending ){
        //Set blending function
        SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha ){
        //Modulate texture alpha
        SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };
        //Set clip rendering dimensions
        if( clip != NULL ){
                renderQuad.w = clip->w;
                renderQuad.h = clip->h;
        }
        //Render to screen
        SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth(){
        return mWidth;
}

int LTexture::getHeight(){
        return mHeight;
}
