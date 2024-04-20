#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "mathV.h"


int main() {

    SDL_Init(SDL_INIT_VIDEO);
    const int width  = 16 * 80;
    const int height = 9 * 80;


    SDL_Window *window = SDL_CreateWindow(
            "Metabolsc",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
            );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *wSurface = SDL_GetWindowSurface(window);


    u32 img[width * height];

    bool isRunning = true;
    int x = 0;
    int y = 0;
    SDL_Surface *ss = SDL_CreateRGBSurfaceFrom(img, width, height, 32, width * 4, 0,0,0, 0);

    Vec2 ball = {300, 300};
    Vec2 ball2 = {800, 365};

    while (isRunning){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            } else if(event.type == SDL_MOUSEMOTION){
                SDL_GetMouseState(&x, &y);
            }
        }
        for(u32 j = 0; j < height; j++){
            for(u32 i = 0; i < width; i++){
                Vec2 p = subVec2((Vec2){i,j}, ball);
                Vec2 p2 = subVec2((Vec2){i,j}, ball2);

                f32 s1 = 1.0f / sqrlLen(p);
                f32 s2 = 1.0f / sqrlLen(p2);
                f32 s = s1 + s2;

                //amatista = 147, 104, 183
                //uranian blue = 166, 217, 247
                u8 r = lerpf(147, 166, s1/s);
                u8 g = lerpf(104, 217, s1/s);
                u8 b = lerpf(183, 247, s1/s);

                if( s >= 0.00005f){
                    img[j * width + i] = SDL_MapRGBA(ss->format, r, g, b ,255);
                } else{
                    img[j * width + i] = SDL_MapRGBA(ss->format, 39, 39, 39 ,255);
                }

            }
        }



        SDL_BlitSurface(ss, NULL, wSurface, NULL);

        SDL_UpdateWindowSurface(window);
        SDL_RenderPresent(renderer);
    }

    fprintf(stdout, "0x%X\n", ss->format->Rmask);
    fprintf(stdout, "%f", lerpf(0.0f, 25.0f, 1.0f));

    SDL_FreeSurface(ss);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


