#include "Game.h"

Game:: Game()
{
}

int Game:: Run()
{
    srand(time(NULL));

    SDL_Window* window;
    SDL_Renderer* gRenderer;
    initSDL(window, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    bool quit=false;
    LTexture mp(gRenderer);
    mp.loadFromFile("image/bkgn.png");
    Dot bird(SCREEN_WIDTH/6, SCREEN_HEIGHT/2,0, 3);
    bird.mTexture.gRenderer = gRenderer;
    bird.mTexture.loadFromFile("image/ship.png");
    SDL_Event e;
    int scrolling=0;
    while (!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {

            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            bird.handleEvent(e);
        }
        bird.move();
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        --scrolling;
        if( scrolling < -mp.mWidth ) scrolling = 0;

        mp.render(scrolling,0);
        mp.render(scrolling + mp.mWidth,0);
        bird.render();
        SDL_RenderPresent( gRenderer );
    }
    quitSDL(window, gRenderer);
    return 1;
}

