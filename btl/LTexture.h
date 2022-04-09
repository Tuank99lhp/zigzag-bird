#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;
class LTexture
{
	public:
		//Initializes variables
		SDL_Renderer *gRenderer;
		LTexture();
        LTexture(SDL_Renderer *ren);
		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( string path );

		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		int mHeight;
		int mWidth;
		//Renders texture at given point
		void render( int x, int y, int w=-1 ,int h=-1,double angle = 0.0, SDL_Rect* clip = NULL,  SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );


		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
};

#endif // LTEXTURE_H
