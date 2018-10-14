#ifndef PARTICLE_H
#define PARTICLE_H

namespace pawstef {

class Particle
{
public:
    double m_x;
    double m_y;
private:
    double speed;
    double direction;
private:
    void init();
public:
    Particle();
    virtual ~Particle();
    void update(int interval);

};
}

#endif // PARTICLE_H
