#ifndef DOT_H
#define DOT_H

#include "LTexture.h"
#include "Particle.h"
#include <vector>
using namespace std;

class Dot
{
    public:
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 640;
		//The dimensions of the dot
		const double WIDTH = 60;
		const double HEIGHT = 30;
        double deg=40;
        double curdeg=0;
		Dot();
		Dot(double stx,double sty,double vx,double vy);

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen
		void render();
        LTexture mTexture;
		//The X and Y offsets of the dot
		double mPosX, mPosY;
		//The velocity of the dot
		double mVelX, mVelY;
		vector<Particle*> par;
		void renderPar();
};
#endif // DOT_H
