#include "Game.h"

Game:: Game()
{
}

int Game:: Run()
{
    srand(time(NULL));


    initSDL(window, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    LTexture gFPSTextTexture(gRenderer);
    LTexture mp(gRenderer);
    mp.loadFromFile("image/bkgn.png");


    Dot bird(SCREEN_WIDTH/6, SCREEN_HEIGHT/2,0, 3);
    bird.mTexture.gRenderer = gRenderer;
    bird.mTexture.loadFromFile("image/ship2.png");

    gFont = TTF_OpenFont( "lazy.ttf", 28 );
    gFPSTextTexture.gFont = gFont;

    fpsTimer.start();


    LTexture top(gRenderer);
    top.loadFromFile("image/topblock2.png");
    LTexture bottom(gRenderer);
    bottom.loadFromFile("image/bottomblock2.png");


    LTexture gameover(gRenderer);
    gameover.loadFromFile("image/GAMEOVER.png");

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
        scrolling-=2;
        if( scrolling < -mp.mWidth ) scrolling = 0;

        mp.render(scrolling,0);
        mp.render(scrolling + mp.mWidth,0);
        bird.render();
        sinhcot++;
        if (sinhcot == 200)
        {
            sinhcot = 0;
            de.push_back(new cot);
        }
        if (!de.empty())
        {
            cot *tmp = de.front();
            if (tmp->X + tmp->WIDTH < 0)
            {
                de.pop_front();
                delete tmp;
            }
            for (auto it = de.begin(); it != de.end(); it ++)
              (*it)->render(top, bottom);

        for (auto it = de.begin(); it != de.end(); it ++)
         {
             int X,Y,W,GAP,x,y,bw,bh;
             X = (*it)->X;
             Y = (*it)->Y;
             W = (*it)->WIDTH;
             GAP = (*it)->GAP;
             x = bird.mPosX;
             y = bird.mPosY;
             bw= bird.WIDTH;
             bh= bird.HEIGHT;
             if (((x + bw > X && x < X + W)) && (y < Y || y + bh > Y + GAP))
             {
                 gameover.render(SCREEN_WIDTH/2 - gameover.mWidth/2, SCREEN_HEIGHT/2 - gameover.mHeight/2);
                 SDL_RenderPresent(gRenderer);
                 while (!quit)
                 {
                    while( SDL_PollEvent( &e ) != 0 )
                    {

                       if( e.type == SDL_QUIT ) quit = true;


                    }

                 }
                 return 1;
             }
          }
         }
        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 ) avgFPS = 0;

				//Set text to be rendered
				timeText.str( "" );
				timeText << "FPS: " << avgFPS;

				//Render text
				if( !gFPSTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render FPS texture!\n" );
				}
        gFPSTextTexture.render(0,0,100,25);
        SDL_RenderPresent(gRenderer);
        ++countedFrames;

				//If frame finished early
		int frameTicks = capTimer.getTicks();
		if( frameTicks < SCREEN_TICK_PER_FRAME )
		{
			//Wait remaining time
			SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
		}

    }
    quitSDL(window, gRenderer);
    return 1;
}

