#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "mathV.h"

typedef struct metaball{
    Vec2 center;
    f32 s;
}Metaball;

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
    memset(img, 39, width * height * 4);

    bool isRunning = true;
    int x = 0;
    int y = 0;
    SDL_Surface *ss = SDL_CreateRGBSurfaceFrom(img, width, height, 32, width * 4, 0,0,0, 0);

    Metaball balls[3];

    u8 count = 0;
    u8 capacity = 3;

    while (isRunning){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            } else if(event.type == SDL_MOUSEBUTTONDOWN){
                count += 1;
                if(count > capacity){
                    count = 3;
                }
                SDL_GetMouseState(&x, &y);

                balls[count -1].center = (Vec2){x, y};
            } else if(event.key.keysym.sym == SDLK_c){
                memset(img, 39, width * height * 4);
                count = 0;
            }
        }
        for(u32 j = 0; j < height; j++){
            for(u32 i = 0; i < width; i++){
                f32 sum = 0;
                for(u8 px = 0; px < count; px++){
                    Vec2 p = subVec2((Vec2){i,j}, balls[px].center);
                    balls[px].s = 1.0f / sqrlLen(p);
                    sum += balls[px].s;
                    //amatista = 147, 104, 183
                    //uranian blue = 166, 217, 247
                    u8 r = lerpf(147, 166, balls[px].s / sum);
                    u8 g = lerpf(104, 217, balls[px].s / sum);
                    u8 b = lerpf(183, 247, balls[px].s / sum);

                    if( sum >= 0.00005f){
                        img[j * width + i] = SDL_MapRGBA(ss->format, r, g, b ,255);
                    } else{
                        img[j * width + i] = SDL_MapRGBA(ss->format, 39, 39, 39 ,255);
                    }
                }




            }
        }



        SDL_BlitSurface(ss, NULL, wSurface, NULL);

        SDL_UpdateWindowSurface(window);
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(ss);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


