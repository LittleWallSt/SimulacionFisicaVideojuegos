#include "ParticleSystem.h"


// Constructora
ParticleSystem::ParticleSystem() {

	// Generador de partículas verdes redondas con distribucion normal
	particle* model = new particle(100, Vector3(0), Vector3(0,0.0f,0), Vector3(0, 10, 0), 0.2, Vector4(1, 1, 0, 0), CreateShape(PxSphereGeometry(3)));
	ParticleGenerator* ptG = new GaussianParticleGenerator(Vector3(1, 45 , 1), Vector3(30, 50 ,30), 0.3, model, 3);
	ptG->setRandomLifeTimeRange(2);
	ptG->setMinimumLifeTime(5);
	ptG->setName("Avispero");
	_particle_generators.push_back(ptG);

	// Generador de partículas azules cuadradas con distribucion uniforme
	model = new particle(100, Vector3(0), Vector3(0,100,0), Vector3(0), 5, Vector4(0, 125, 1, 1), CreateShape(PxBoxGeometry(1, 1, 1)));
	ptG = new UniformParticleGenerator(Vector3(-150, 0, 0), Vector3(10,350,10), 0.3, model, 100);
	ptG->setName("Geyser");
	_particle_generators.push_back(ptG);



	model = new particle(100, Vector3(0), Vector3(0), Vector3(-5, 10, -5), 5, Vector4(1, 0, 0, 1), CreateShape(PxSphereGeometry( 1)));
	CircleGenerator* ptC= new CircleGenerator(Vector3(1, 45, 1), Vector3(8), 0.3, model, 3);
	ptC->setNparticles(16);
	ptC->setName("Circles");
	ptC->setMinimumLifeTime(7);
	_particle_generators.push_back(ptC);

	//dos fireworks no reutilizables, se vera en un futuro si se implementa debido a que los static casts me mataron 
	Firework* f1 = new Firework(Vector3(-50, 0, -100), Vector3(0, 60, 0), Vector3(0), Vector4(0, 1, 255, 1), 4.0f, 4, 8);
	fireworks_pool.push_back(f1);

	Firework* f2 = new Firework(Vector3(-200, 0, -300), Vector3(0, 60, 0), Vector3(0, -10, 0), Vector4(255, 1, 0, 1), 5.0f, 4, 7);
	fireworks_pool.push_back(f2);

	fireworkGen = new FireworkGenerator("Fireworks...", Vector3(10, 30, 10));

}

// Destructora
ParticleSystem::~ParticleSystem() {
	for (ParticleGenerator* p : _particle_generators) delete p;
	_particle_generators.clear();

	for (particle* p : _particles) delete p;
	_particles.clear();
}

// Update
void ParticleSystem::update(double t) {

	if (x) {
		Firework* f1 = new Firework(Vector3(-50, 0, -100), Vector3(0, 40, 0), Vector3(0), Vector4(0, 1, 255, 1), 4.0f, 3, 8);
		fireworks_pool.push_back(f1);

		Firework* f2 = new Firework(Vector3(-200, 0, -300), Vector3(0, 40, 0), Vector3(0, -10, 0), Vector4(255, 1, 0, 1), 5.0f, 3, 7);
		fireworks_pool.push_back(f2);

		spawnF();
	}

	for (ParticleGenerator* p : _particle_generators) {
		list<particle*> prtcls = p->generateParticles();
		for (auto p : prtcls) {
			_registry.addReg(activeForce, p);
		}

		if (!prtcls.empty()) _particles.splice(_particles.end(), prtcls);
	}

	for (auto it = _particles.begin(); it != _particles.end(); it++) {
		
		if (!(*it)->integrate(t)) _particlesToDelete.push_back(it);
	}

	_registry.updateForces(t);

	for (int i = 0; i < _particlesToDelete.size(); i++) {
		particle* p = *_particlesToDelete[i];
		_registry.deletePartReg(p);
		_particles.erase(_particlesToDelete[i]);
		delete p;
	}
	_particlesToDelete.clear();

	for (auto it = fireworks_pool.begin(); it != fireworks_pool.end(); it++) {
		if (!(*it)->integrate(t)) {
			deadFireworks.push_back(it);
		}
	}

	for (int i = 0; i < deadFireworks.size(); i++) {
		if ((*deadFireworks[i])->getGeneration() > 1) {
			list<Firework*> fs = fireworkGen->generateFireworks(*deadFireworks[i]);
			if (!fireworks_pool.empty()) fireworks_pool.splice(fireworks_pool.end(), fs);
		}
		delete* deadFireworks[i];
		fireworks_pool.erase(deadFireworks[i]);
	}
	deadFireworks.clear();



}

// Buscar y devolver un generador con el nombre recibido
ParticleGenerator* ParticleSystem::getParticleGenerator(string name) {
	auto it = _particle_generators.begin();
	bool enc = false;
	while (!enc && it != _particle_generators.end()) {
		enc = (*it)->getName() == name;
		if (!enc) it++;
	}

	return (*it);
}

//no me caes bien
void ParticleSystem::generateFireworkSystem() {

}