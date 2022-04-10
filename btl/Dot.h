#ifndef DOT_H
#define DOT_H

#include "LTexture.h"
using namespace std;

class Dot
{
    public:
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 640;
		//The dimensions of the dot
		const int WIDTH = 60;
		const int HEIGHT = 30;

		Dot();
		Dot(int stx,int sty,int vx,int vy);

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen
		void render();

        LTexture mTexture;
		//The X and Y offsets of the dot
		int mPosX, mPosY;
		//The velocity of the dot
		int mVelX, mVelY;
};
#endif // DOT_H
