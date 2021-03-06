#ifndef COT_H
#define COT_H

#include "LTexture.h"

using namespace std;

class cot
{
    public:
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 640;

		const double WIDTH = 50;
		const double GAP = 200;
		bool scored = 0;

		cot();

		void render(LTexture &top, LTexture &bottom);

		double X, Y;
};
#endif // COT_H
