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

    float alpha = 0.0f;
    float x, y;
    if (active) {
        for (int i = 0; i < 30; ++i) {
            auto part = model->clone(model->getPos(), model->getAcceleration(), model->getLifeTime());
            generations.push_back(part); // new particle

            // modify its pos. and vel. according to the generator type

            auto radians = (alpha * M_PI) / 180;
            x = std::cos(radians);
            y = std::sin(radians);
            alpha += (360.0 / 30);

            part->setPos({ 10, 40 , 10 });
            part->setVelocity({ x * 20, y * 20, 0 });

            // set a rnd life span
            part->setLifeTime(minimumLifeTime);

        }
    }
    

    return generations;
}