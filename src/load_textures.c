#include "../includes/wolf3d.h"


void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  Uint32 *target_pixel = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch
  	 + x * sizeof *target_pixel);
  *target_pixel = pixel;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
	return *(Uint32 *)p;
}

int				load_textures(t_wolf *wolf, t_sdl *sdl)
{
	SDL_Surface	*tex;

	if (!(tex = SDL_LoadBMP(TEXTURE_PATH)))
		printf("%s\n", SDL_GetError());
	sdl->textures = tex;
	//sdl->textures = SDL_ConvertSurfaceFormat(tex, SDL_PIXELFORMAT_ABGR8888, 0);
	sdl->bytes_texture = (unsigned char*)sdl->textures->pixels;
	
	return 0;
}