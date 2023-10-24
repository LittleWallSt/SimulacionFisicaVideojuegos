#include "ParticleGenerator.h"

// Constructora - Inicializa valores básicos, aleatorios y muestra información por pantalla
ParticleGenerator::ParticleGenerator(Vector3 iniPos, Vector3 medSpeed, Vector3 medVar, float prob, bool st) :
	iniPos(iniPos), meanVel(medSpeed), meanVar(medVar), probability(prob), staticGenerator(st),
	gen(default_random_engine(chrono::system_clock::now().time_since_epoch().count())) {
	srand((unsigned)time);

	cout << "Particle generation set with " << prob << " probability\n";
	cout << "Speed: (" << medSpeed.x << ", " << medSpeed.y << ", " << medSpeed.z << ")\n";
	cout << "Var:   (" << medVar.x << ", " << medVar.y << ", " << medVar.z << ")\n";
}

// Destructora
ParticleGenerator::~ParticleGenerator() {
	delete model;
}