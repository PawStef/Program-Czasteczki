#ifndef SWARM_H
#define SWARM_H

#include "Particle.h"

namespace pawstef {

class Swarm
{
public:
    const static int NPARTICLES = 10000; //number of particles
private:
    Particle *m_pParticles;
    int lastTime;
public:
    Swarm();
    virtual ~Swarm();
    void update( int elapsed);
    const Particle * const getParticles() {return m_pParticles;};
};
}

#endif // SWARM_H
