#include "CircleGenerator.h"
#include <math.h>
#include <random>
# define M_PI           3.14159265358979323846

CircleGenerator::CircleGenerator(Vector3 iniPos, Vector3 var, float prob, particle* m, int nParticles, bool st)
    : ParticleGenerator(iniPos, m->getVelocity(), var, prob, st), _n_particles(nParticles) {

    // Partícula modelo
    m->setPos(iniPos);
    setParticle(m);
    
}

list<particle*> CircleGenerator::generateParticles() {

    std::list<particle*> generations;

    float alpha = startingalpha;
    //cout << alpha << endl;
    float x, y;
    if (active) {
        for (int i = 0; i < _n_particles; ++i) {
            auto part = model->clone(model->getPos(), model->getAcceleration(), model->getLifeTime());
            generations.push_back(part);             
            auto radians = (alpha * M_PI) / 180;
            x = std::cos(radians);
            y = std::sin(radians);
            alpha += (360.0 / _n_particles);
            part->setPos({ 10, 40 , 10 });
            part->setVelocity({ x * 20, y * 20, 0 });
            part->setLifeTime(minimumLifeTime);

        }
        startingalpha++;
        startingalpha %= 360;
        
    }
    
    

    return generations;
}