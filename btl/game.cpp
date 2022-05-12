#include "Game.h"

Game:: Game()
{
    srand(time(NULL));

    initSDL(window, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    gFPSTextTexture.gRenderer = gScore.gRenderer = mp.gRenderer = top.gRenderer = bottom.gRenderer = gameover.gRenderer = gStartgame.gRenderer = bird2.gRenderer = gRenderer;

    bird = new Dot(SCREEN_WIDTH/6, SCREEN_HEIGHT/2,0, 5);

    mp.loadFromFile("image/bkgn.png");

    gMusic = Mix_LoadMUS( "music/bg1.mp3" );

    (*bird).mTexture.gRenderer = gRenderer;
    (*bird).mTexture.loadFromFile("image/ship2.png");

    bird2.loadFromFile("image/ship2.png");

    gFont = TTF_OpenFont( "lazy.ttf", 28 );
    gStartgame.gFont = gFont;
    gFPSTextTexture.gFont = gFont;
    gScore.gFont = gFont;

    fpsTimer.start();

    top.loadFromFile("image/topblock2.png");
    bottom.loadFromFile("image/bottomblock2.png");

    gameover.loadFromFile("image/GAMEOVER.png", 1);

    timeText.str("");
    timeText << "Press 1, 2, 3 to play! (Difficulty 1-3)";
    gStartgame.loadFromRenderedText( timeText.str().c_str(), textColor );

}
void Game:: rendermap()
{
    scrolling-=2;
    if( scrolling < -mp.mWidth ) scrolling = 0;

    mp.render(scrolling,0);
    mp.render(scrolling + mp.mWidth,0);
}
void Game:: start()
{
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );
    rendermap();
    bird2.render(SCREEN_WIDTH/6, SCREEN_HEIGHT/2, 60, 30);
    gStartgame.render(SCREEN_WIDTH/2 - gameover.mWidth/2 + 30, SCREEN_HEIGHT/2 + gameover.mHeight/2);
    SDL_RenderPresent(gRenderer);
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT) quit=true;
        if (e.type == SDL_KEYDOWN)
        {
            auto x = e.key.keysym.sym;
            if (x != SDLK_1 && x != SDLK_2 && x != SDLK_3) continue;
            if (x == SDLK_1) M = 200;
            if (x == SDLK_2) M = 150;
            if (x == SDLK_3) M = 100;
            startgame = true;
        }
    }

}
void Game:: rollback()
{
    score = 0;
    (*bird).mPosY = SCREEN_HEIGHT/2;
    while (!de.empty()) de.pop_back();
    sinhcot = 0;
    tryagain = 0;
}
void Game:: gameOver()
{
    gameover.render(SCREEN_WIDTH/2 - gameover.mWidth/2, SCREEN_HEIGHT/2 - gameover.mHeight/2);
    timeText.str("");
    timeText << "Press space to try again !";
    gFPSTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor );
    gFPSTextTexture.render(SCREEN_WIDTH/2 - gameover.mWidth/2 + 100, SCREEN_HEIGHT/2 + gameover.mHeight/2);
    SDL_RenderPresent(gRenderer);
    while (!quit && !tryagain)
    {
        while( SDL_PollEvent( &e ) != 0)
        {

            if( e.type == SDL_QUIT ) quit = true;
            if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_SPACE)) tryagain = true;
        }

    }
}
void Game:: rcol()
{
    sinhcot++;
    if (sinhcot == M)
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
            if (abs(trunc(bird->mPosX-(**it).X))<=10  && !(**it).scored)
            {
                score ++;
                (**it).scored = 1;
            }
            if (checkcollider(*bird, (**it)))
            {
                gameOver();
                return;
            }
        }
    }
}
void Game:: play()
{

    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
        bird->handleEvent(e);
    }
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );
    bird->move();
    rendermap();
    bird->render();
    rcol();
}
void Game:: playmusic()
{
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( gMusic, -1 );
    }
}
void Game:: fpsandscore()
{
    float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
    if( avgFPS > 2000000 ) avgFPS = 0;

    //Set text to be rendered
    timeText.str( "" );
    timeText << int(avgFPS);

    //Render text
    if( !gFPSTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
    {
        printf( "Unable to render FPS texture!\n" );
    }
    gFPSTextTexture.render(0,0,15,15);
    timeText.str( "" );
    timeText << "Score: "<<score;

    //Render text
    if( !gScore.loadFromRenderedText( timeText.str().c_str(), textColor ) )
    {
        printf( "Unable to render FPS texture!\n" );
    }
    gScore.render(SCREEN_WIDTH-60,0,60,20);
}
void Game:: delay()
{
    ++countedFrames;

    //If frame finished early
    int frameTicks = capTimer.getTicks();
    if( frameTicks < SCREEN_TICK_PER_FRAME )
    {
        //Wait remaining time
        SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
    }
}
int Game:: Run()
{
    while (!quit)
    {

        if (!startgame)
        {
            start();
            continue;
        }
        if (tryagain)
        {
            rollback();
        }
        play();
        if (tryagain) continue;
        if (quit) return 1;
        playmusic();
        fpsandscore();
        SDL_RenderPresent(gRenderer);
        delay();

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
                                Point(c.X+5,0.0)
                               };
    double nY=c.Y + c.GAP + 10;
    vector<Point<double> > v3= {Point(c.X+5,nY),
                                Point(c.X+c.WIDTH-5,nY),
                                Point(c.X+c.WIDTH-5,1.0*SCREEN_HEIGHT),
                                Point(c.X+5,1.0*SCREEN_HEIGHT),
                                Point(c.X+5,nY)
                               };
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
