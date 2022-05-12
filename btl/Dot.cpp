#include "Dot.h"
#include <cmath>
using namespace std;
Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    stVelY = mVelY = 0;

}
Dot::Dot(double stx,double sty,double vx,double vy)
{
    //Initialize the offsets
    mPosX = stx;
    mPosY = sty;

    //Initialize the velocity
    mVelX = vx;
    stVelY = mVelY = vy;

}
void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) mVelY = -stVelY;
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) mVelY = stVelY;

}

void Dot::move()
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}
void Dot::render()
{
    if (mVelY < 0)
    {
        curdeg -= 5;
        if (curdeg < -deg) curdeg = -deg;
    }
    else
    {
        curdeg += 5;
        if (curdeg > deg) curdeg = deg;
    }
	mTexture.render(mPosX, mPosY, WIDTH, HEIGHT,curdeg);


	par.push_back(new Particle(mPosX, mPosY, mTexture.gRenderer, curdeg, deg));

    Particle *it;

	for (int i = 0; i < par.size(); ++i)
    {
        it = par[i];
        while (it != NULL && it->isDead())
        {
            swap((*it), (*par.back()));
            delete par.back();
            par.pop_back();
        }
        if (it != NULL) it->render();
    }


}
