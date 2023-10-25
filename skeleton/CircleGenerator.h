#pragma once
#include "ParticleGenerator.h"
#include <list>
#include "core.hpp"
#include "RenderItems/particle.h"
#include <string>

class CircleGenerator : public ParticleGenerator {
protected:
	Vector3 _std_dev_vel, _std_dev_pos;
	double _min_t, _max_t = 10;

	int _n_particles;

public:
	CircleGenerator(Vector3 iniPos, Vector3 var, float prob, particle* m, int _n = 1, bool st = true);
	virtual ~CircleGenerator() {};

	virtual list<particle*> generateParticles();

	
};