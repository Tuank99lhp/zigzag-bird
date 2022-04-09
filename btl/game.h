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
#include "sdl.h"
#include "LTexture.h"
#include "Dot.h"

using namespace std;

class Game
{
    public:
        int Run();
        Game();
    private:

        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 640;
        const char* WINDOW_TITLE = "con chim thieu nang";
        const int FPS=60;
        const int time_one_frame=1000/FPS;
};
#endif // GAME_H
