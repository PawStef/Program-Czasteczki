#include "screen.h"
#include <stdio.h>
#include <cstring>

namespace pawstef {

Screen::Screen() : window(NULL), renderer(NULL), texture(NULL), buffer1(NULL), buffer2(NULL)
{

}

bool Screen::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    window = SDL_CreateWindow("Training project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, screenWidth, screenHeight);

    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
     if (texture == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    buffer1 = new Uint32[screenWidth*screenHeight];
    buffer2 = new Uint32[screenWidth*screenHeight];

    memset(buffer1, 0, screenWidth*screenHeight*sizeof(Uint32));
    memset(buffer2, 0, screenWidth*screenHeight*sizeof(Uint32));

    return true;
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
    if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight) {
        return;
    }

    Uint32 color = 0;

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    buffer1[(y * screenWidth) + x] = color;
}

void Screen::update()
{
        // drawing code
    SDL_UpdateTexture(texture, NULL, buffer1, screenWidth*sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool Screen::processEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT){
            return false;
        }
    }
    return true;
}

void Screen::close()
{
    delete [] buffer1;
    delete [] buffer2;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Screen::boxBlur()
{
    Uint32 *temp = buffer1;
    buffer1 = buffer2;
    buffer2 = temp;

    for(int y=0; y<screenHeight; y++) {
        for(int x=0; x<screenWidth; x++) {

            int redTotal=0;
            int greenTotal=0;
            int blueTotal=0;

            for(int row=-1; row<=1; row++){
                for(int col=-1; col<=1; col++){
                    int currentX = x + col;
                    int currentY = y + row;

                    if(currentX >= 0 && currentX < screenWidth && currentY >= 0 && currentY < screenHeight) {
                        Uint32 color = buffer2[currentY*screenWidth + currentX];
                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;

                        redTotal += red;
                        greenTotal += green;
                        blueTotal += blue;
                    }
                }
            }
            Uint8 red = redTotal/9;
            Uint8 green = greenTotal/9;
            Uint8 blue = blueTotal/9;

            setPixel(x, y, red, green, blue);
        }
    }
}
}

