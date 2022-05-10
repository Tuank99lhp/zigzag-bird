#include "Particle.h"
using namespace std;
Particle::Particle( double x, double y, SDL_Renderer* gRenderer,double st)
{
    //Set offsets
    X = x - (rand() % 5);
    if (st<0) Y = y + 35 + (rand()%10);
    else Y = y - 15 + (rand()%10);
    //Set type
    mTexture.gRenderer = gRenderer;
    switch( rand() % 3 )
    {
    case 0:
        mTexture.loadFromFile("image/red.png", 1);
        break;
    case 1:
        mTexture.loadFromFile("image/blue.png", 1);
        break;
    case 2:
        mTexture.loadFromFile("image/green.png", 1);
        break;
    }
    shimmer.gRenderer = gRenderer;
    shimmer.loadFromFile("image/shimmer.png", 1);;
}

void Particle::render()
{
    mTexture.render(X,Y);
    if (mFrame)
    {
        shimmer.render(X,Y);
        Y+=2;
    }
    X = X - 5;
    mFrame= 1 - mFrame;
}

bool Particle::isDead()
{
    return (X <= 0 || Y >= SCREEN_HEIGHT);
}

void swap(Particle &a, Particle &b)
{
    LTexture tmp;
    tmp = a.mTexture;
    a.mTexture = b.mTexture;
    b.mTexture = tmp;

    double tmp2;
    tmp2 = a.X;
    a.X = b.X;
    b.X = tmp2;

    tmp2 = a.Y;
    a.Y = b.Y;
    b.Y = tmp2;

}
