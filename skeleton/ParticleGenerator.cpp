#include "ParticleGenerator.h"

// Constructora 
ParticleGenerator::ParticleGenerator(Vector3 iniPos, Vector3 medSpeed, Vector3 medVar, float prob, bool st) :
	iniPos(iniPos), meanVel(medSpeed), meanVar(medVar), probability(prob), staticGenerator(st),
	gen(default_random_engine(chrono::system_clock::now().time_since_epoch().count())) {
	srand((unsigned)time);

}

// Destructora
ParticleGenerator::~ParticleGenerator() {
	delete model;
}