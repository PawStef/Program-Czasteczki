#include <iostream>
#include <stdio.h>
#include <cstring>
#include <math.h>
#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "Swarm.h"

using namespace std;
using namespace pawstef;

int main(int argc, char* argv[]) {

    srand(time(NULL));

    Screen screen;

    if(screen.init() == false) {
        cout << "Error" << endl;
    }

    Swarm swarm;

    while(true) {
        int elapsed = SDL_GetTicks();


        swarm.update(elapsed);

        unsigned char red = (unsigned char)((1 + sin(elapsed*0.001))*128);
        unsigned char green = (unsigned char)((1 + sin(elapsed*0.002))*128);
        unsigned char blue = (unsigned char)((1 + sin(elapsed*0.003))*128);

        const Particle * const pParticles = swarm.getParticles();


        for (int i=0; i<Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];

            int x = (particle.m_x + 1) * Screen::screenWidth/2;
            int y = particle.m_y * Screen::screenWidth/2 + Screen::screenHeight/2;

            screen.setPixel(x, y, red, green, blue);
        }

        screen.boxBlur();

        screen.update();

        if(screen.processEvents() == false ) {
            break;
        }
    }

    screen.close();

    return 0;
}
