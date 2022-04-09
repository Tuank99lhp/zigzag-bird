#include "Dot.h"
using namespace std;
Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}
Dot::Dot(int stx,int sty,int vx,int vy)
{
    //Initialize the offsets
    mPosX = stx;
    mPosY = sty;

    //Initialize the velocity
    mVelX = vx;
    mVelY = vy;

}
void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) mVelY = -mVelY;
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) mVelY = -mVelY;

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
    double XXX=25;
    if (mVelY<0) XXX=-XXX;
	mTexture.render( mPosX, mPosY, WIDTH, HEIGHT,XXX);
}