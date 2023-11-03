#pragma once
#include "ParticleGenerator.h"
#include <list>
#include "core.hpp"
#include "RenderItems/particle.h"
#include <string>

class CircleGenerator : public ParticleGenerator {
protected:
	
	int startingalpha = 0;

	int _n_particles;

public:
	CircleGenerator(Vector3 iniPos, Vector3 var, float prob, particle* m, int _n = 1, bool st = true);
	virtual ~CircleGenerator() {};

	inline void setNparticles(int n){ _n_particles = n; };
	virtual list<particle*> generateParticles();

	
};