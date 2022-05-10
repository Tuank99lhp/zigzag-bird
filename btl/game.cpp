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


    Dot bird(SCREEN_WIDTH/6, SCREEN_HEIGHT/2,0, 5);
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
    gameover.loadFromFile("image/GAMEOVER.png", 1);

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
        if (sinhcot == 100)
        {
            sinhcot = 0;
            de.push_back(new cot);
        }
        if (!de.empty())
        {
            if (de.front()->X + de.front()->WIDTH <= 0)
            {
                delete de.front();
                de.pop_front();
            }
            for (auto it = de.begin(); it != de.end(); it ++)
                (*it)->render(top, bottom);

            for (auto it = de.begin(); it != de.end(); it ++)
            {

                //if (((x + bw > X && x < X + W)) && (y < Y - 5 || y + bh > Y + GAP + 5))
                if (checkcollider(bird, (**it)))
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
                    quitSDL(window, gRenderer);
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
static Point<double> xoay(Point<double> a, Point<double> b, double deg)
{
    a.x-=b.x;
    a.y-=b.y;
    a=a.rotate(-deg);
    a.x+=b.x;
    a.y+=b.y;
    return a;
}
bool Game::checkcollider(Dot &b, cot &c)
{
    Point cen(b.mPosX + b.WIDTH/2, b.mPosY + b.HEIGHT/2);
    vector<Point<double> > v1= {xoay(Point(b.mPosX,b.mPosY),cen,b.curdeg),
                                xoay(Point(b.mPosX+b.WIDTH,b.mPosY),cen,b.curdeg),
                                xoay(Point(b.mPosX+b.WIDTH,b.mPosY+b.HEIGHT),cen,b.curdeg),
                                xoay(Point(b.mPosX,b.mPosY+b.HEIGHT),cen,b.curdeg),
                                xoay(Point(b.mPosX,b.mPosY),cen,b.curdeg)
                               };
    vector<Point<double> > v2= {Point(c.X+5,0.0),
                                Point(c.X+c.WIDTH-5,0.0),
                                Point(c.X+c.WIDTH-5,c.Y-10),
                                Point(c.X+5,c.Y-10),
                                Point(c.X+5,0.0)};
    double nY=c.Y + c.GAP + 10;
    vector<Point<double> > v3= {Point(c.X+5,nY),
                                Point(c.X+c.WIDTH-5,nY),
                                Point(c.X+c.WIDTH-5,1.0*SCREEN_HEIGHT),
                                Point(c.X+5,1.0*SCREEN_HEIGHT),
                                Point(c.X+5,nY)};
    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            if (!segInter(v1[i],v1[i+1],v2[j],v2[j+1]).empty()) return 1;
            if (!segInter(v1[i],v1[i+1],v3[j],v3[j+1]).empty()) return 1;
        }
    }
    return 0;
}
