#include "Particle.h"
#include <stdlib.h>
#include <math.h>

namespace pawstef {

Particle::Particle(): m_x(0), m_y(0)
{
   init();
}

void Particle::init()
{
    m_x=0;
    m_y=0;
    direction = (2* M_PI*rand())/RAND_MAX;
    speed = (0.04* rand())/RAND_MAX;

    speed *= speed;
}

Particle::~Particle()
{

}

void Particle::update(int interval)
{
    direction+= interval*0.0004;
    double xspeed = speed * cos(direction);
    double yspeed = speed * sin(direction);

    m_x += xspeed*interval;
    m_y += yspeed*interval;

    if(m_x<-1 || m_x>1 || m_y<-1 || m_y>1) {
        init();
    }
}
}
