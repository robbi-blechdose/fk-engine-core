#include "video.h"

#include <SDL/SDL.h>
#define CHAD_API_IMPL
#include "zbuffer.h"
#include "GL/gl.h"

SDL_Surface* screen;
ZBuffer* frameBuffer = NULL;

mat4 mPerspective;
mat4 mOrtho;

mat4 ortho(float b, float t, float l, float r, float n, float f)
{ 
    mat4 matrix;
    matrix.d[0] = 2 / (r - l); 
    matrix.d[1] = 0; 
    matrix.d[2] = 0; 
    matrix.d[3] = 0; 
 
    matrix.d[4] = 0; 
    matrix.d[5] = 2 / (t - b); 
    matrix.d[6] = 0; 
    matrix.d[7] = 0; 
 
    matrix.d[8] = 0; 
    matrix.d[9] = 0; 
    matrix.d[10] = -2 / (f - n); 
    matrix.d[11] = 0; 
 
    matrix.d[12] = -(r + l) / (r - l); 
    matrix.d[13] = -(t + b) / (t - b); 
    matrix.d[14] = -(f + n) / (f - n); 
    matrix.d[15] = 1;
    
    return matrix;
}

void initVideo(vec4 clearColor, vec4 viewport, float fov, float near, float far)
{
    #ifdef FUNKEY
    screen = SDL_SetVideoMode(WINX, WINY, 16, SDL_FULLSCREEN | SDL_HWSURFACE);
    #else
    screen = SDL_SetVideoMode(WINX, WINY, 16, SDL_SWSURFACE);
    #endif
	SDL_ShowCursor(SDL_DISABLE);

    //Initialize TinyGL
	frameBuffer = ZB_open(WINX, WINY, ZB_MODE_5R6G5B, 0);
	glInit(frameBuffer);
	glShadeModel(GL_FLAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(clearColor.d[0], clearColor.d[1], clearColor.d[2], clearColor.d[3]);
	glClearDepth(1.0f);
    glViewport(viewport.d[0], viewport.d[1], viewport.d[2], viewport.d[3]);
	glTextSize(GL_TEXT_SIZE8x8);
	glEnable(GL_TEXTURE_2D);
	
	//Initialize projection matrices
    mPerspective = perspective(fov, viewport.d[2] / viewport.d[3], near, far);
	mOrtho = ortho(0, WINX, 0, WINY, -32, 0);
}

void clearFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void flipFrame()
{
    #ifndef FUNKEY
    if(SDL_MUSTLOCK(screen))
    {
        SDL_LockSurface(screen);
    }
    #endif
    ZB_copyFrameBuffer(frameBuffer, screen->pixels, screen->pitch);
    #ifndef FUNKEY
	if(SDL_MUSTLOCK(screen))
    {
		SDL_UnlockSurface(screen);
    }
    #endif
	SDL_Flip(screen);
}

void quitVideo()
{
	ZB_close(frameBuffer);
	glClose();

    SDL_Quit();
}

void setOrtho()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(mOrtho.d);
	glMatrixMode(GL_MODELVIEW);
}

void setPerspective()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(mPerspective.d);
	glMatrixMode(GL_MODELVIEW);
}

void drawFPS(uint16_t fps)
{
    char buffer[12];
	sprintf(buffer, "FPS: %i", fps);
	glDrawText(buffer, 2, 2, 0xFFFFFF);
}