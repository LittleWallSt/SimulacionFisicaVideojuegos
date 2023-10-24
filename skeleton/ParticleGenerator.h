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

	// Generador de aleatorios
	default_random_engine gen;

public:
	// Constructora y destructora
	ParticleGenerator(Vector3 iniPos, Vector3 medSpeed, Vector3 medVar, float prob, bool st);
	~ParticleGenerator();

	// Método abstracto
	virtual list<particle*> generateParticles() = 0;

	// Getters y setters
	inline void setParticle(particle* m) { model = m; }
	inline string getName() { return name; }
};
