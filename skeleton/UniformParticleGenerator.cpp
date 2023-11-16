#include "UniformParticleGenerator.h"
// Constructora - Setea la partícula modelo y las distribuciones según proceda
UniformParticleGenerator::UniformParticleGenerator(Vector3 iniPos, Vector3 var, float prob, particle* m,int nPart, bool st)
	: ParticleGenerator(iniPos, m->getVelocity(), var, prob, st), _n_particles(nPart) {

	// Partícula modelo
	m->setPos(iniPos);
	setParticle(m);

	// Distribuciones de velocidad
	vX = new uniform_real_distribution<float>(m->getVelocity().x - var.x, m->getVelocity().x + var.x);
	vY = new uniform_real_distribution<float>(m->getVelocity().y - var.y, m->getVelocity().y + var.y);
	vZ = new uniform_real_distribution<float>(m->getVelocity().z - var.z, m->getVelocity().z + var.z);

	// Distribuciones de posición
	if (!st) {
		pX = new uniform_real_distribution<float>(iniPos.x - var.x * 2, iniPos.x + var.x / 2.0f);
		pY = new uniform_real_distribution<float>(iniPos.y - var.y * 2, iniPos.y + var.y / 2.0f);
		pZ = new uniform_real_distribution<float>(iniPos.z - var.z * 2, iniPos.z + var.z / 2.0f);
	}
}

// Destructora
UniformParticleGenerator::~UniformParticleGenerator() {
	delete vX, vY, vZ;
	if (pX != nullptr) delete pX, pY, pZ;
}

list<particle*> UniformParticleGenerator::generateParticles() {
	// Lista de partículas a  invocar
	list<particle*> prtcls;

	//si esta activo el generador
	if (active) {
		for (int i = 0; i < _n_particles; i++) {
			float random = (rand() % 101) / 100.0f;
			Vector4 color = model->getColor();

			if (random < probability) {
				// Variables aleatorias
				Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));
				int lifeTime;
				float mass = model->getMass();

				//si tiene probabilidad de vida
				if (randomLifeTime) {
					lifeTime = rand() % RandomLifeTimeRange + minimumLifeTime;
				}
				//sino se gestiona en clone
				else lifeTime = -1;
				
				if (randomColor) {
					int value[3];
					for (int k = 0; k < 3; k++) {
						value[k] = rand() % 2;
					}
					color = Vector4(value[0], value[1], value[2], 1);
				}
				if (randomMass) {
					mass = rand() % randomMassRange + minimumMass;
				}

				// Crear partícula
				if (!staticGenerator) {
					Vector3 pos = Vector3((*pX)(gen), (*pY)(gen), (*pZ)(gen));
					prtcls.push_back(model->clone(pos, vel, model->getAcceleration(), lifeTime, color));
				}
				else prtcls.push_back(model->clone(vel, model->getAcceleration(), lifeTime, color));
			}
		}
	}
	
	

	return prtcls;
}