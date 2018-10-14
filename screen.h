#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>

namespace pawstef {
class Screen
{
public:
    const static int screenWidth = 800;
    const static int screenHeight = 600;
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Uint32 *buffer1;
    Uint32 *buffer2;
public:
    Screen();
    bool init();
    bool processEvents();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void close();
    void update();
    void boxBlur();
};
}

#endif // SCREEN_H
