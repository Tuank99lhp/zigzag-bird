#include "cot.h"
using namespace std;
cot::cot()
{
    X = SCREEN_WIDTH + 5;
    Y = rand()%(SCREEN_HEIGHT*9/10 - GAP) + (SCREEN_HEIGHT/15);
}
void cot::render(LTexture &top, LTexture &bottom)
{
    X-=5;
    top.render(X,Y-top.mHeight,WIDTH);
    bottom.render(X,Y+GAP,WIDTH);

}
