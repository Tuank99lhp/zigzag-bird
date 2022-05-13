#ifndef PARTICLE
#define PARTICLE

#include "LTexture.h"
using namespace std;
class Particle
{
	public:
		//Initialize position and animation
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 640;
		Particle(double x, double y, SDL_Renderer* gRenderer, double st, double deg);

		//Shows the particle
		void render();

		//Checks if particle is dead
		bool isDead();


		double X, Y;
        int mFrame = 0;
		LTexture mTexture;
		LTexture shimmer;
};
void swap(Particle &a, Particle &b);
#endif // PARTICLE
