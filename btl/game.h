#ifndef GAME_H
#define GAME_H


#include<iostream>
#include<vector>
#include<time.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <SDL_ttf.h>
#include <string>
#include <deque>
#include "sdl.h"
#include "LTexture.h"
#include "Dot.h"
#include "cot.h"
#include "LTimer.h"
#include "giao.h"
#include "point.h"
#include "onsegment.h"
using namespace std;

class Game
{
    public:
        int Run();
        Game();
    private:
        deque<cot*> de;
        SDL_Event e;
        int scrolling=0,sinhcot=0;
        bool quit=false;
        SDL_Window* window;
        SDL_Renderer* gRenderer;

        SDL_Color textColor = { 0, 0, 0, 255 };

			//The frames per second timer
        LTimer fpsTimer;

			//The frames per second cap timer
		LTimer capTimer;

			//In memory text stream
		stringstream timeText;

			//Start counting frames per second
		int countedFrames = 0;
        TTF_Font* gFont = NULL;
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 640;
        const char* WINDOW_TITLE = "con chim thieu nang";
        const int FPS=144;
        const int SCREEN_TICK_PER_FRAME=1000/FPS;
        bool checkcollider(Dot &b, cot &c);
        //Point<double> xoay(Point<double> a, Point<double> b, double deg);
};
#endif // GAME_H
