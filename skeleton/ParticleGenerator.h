#pragma once
#include <iostream>
#include <list>
#include "core.hpp"
#include "RenderItems/particle.h"
#include <string>
#include <random>
#include <chrono>
using namespace std;

enum Generations {
	UNIFORM=0,
	GAUSSIAN, 
	FIREWORK
};

class ParticleGenerator {
protected:
	// Propiedades
	string name;
	particle* model;
	bool staticGenerator;

	// Variables
	Vector3 iniPos, meanVel, meanVar;
	float probability;
	bool active = false;
	bool randomLifeTime = true;
	int RandomLifeTimeRange = 10;
	int minimumLifeTime = 3;
	bool randomColor = false;
	
	// Generador de aleatorios
	default_random_engine gen;

public:
	// Constructora y destructora
	ParticleGenerator(Vector3 iniPos, Vector3 medSpeed, Vector3 medVar, float prob, bool st);
	~ParticleGenerator();

	// Método abstracto
	virtual list<particle*> generateParticles() = 0;

	// Getters y setters
	inline void setParticle(particle* m) { model = m; };
	inline void setRandomLifetime() { randomLifeTime = !randomLifeTime; };
	inline void setRandomLifeTimeRange(int range) { RandomLifeTimeRange = range; };
	inline void setMinimumLifeTime(int min) { minimumLifeTime = min; };
	inline void setName(string newName) { name = newName; };
	inline void setRandomColor() { randomColor = !randomColor; };


	inline string getName() { return name; };
	inline void setActive() { active = !active ; };
};
