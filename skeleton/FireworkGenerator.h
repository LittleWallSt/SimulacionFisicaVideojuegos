#pragma once
#include "ParticleGenerator.h"
#pragma once
#include "RenderItems/Firework.h"
#include <random>

using namespace std;
using random_generator = std::mt19937;

//Maldito generador de fireworks que no querias hacer static cast maldito
class FireworkGenerator {
protected:
	string name;
	bool uniquePoint;
	Vector3 mean_var;

	uniform_real_distribution<float>* vX = nullptr;
	uniform_real_distribution<float>* vY = nullptr;
	uniform_real_distribution<float>* vZ = nullptr;

	uniform_int_distribution<>* sons = nullptr;

	std::random_device rd;
	random_generator rg;

public:
	//constructora
	FireworkGenerator(string n, Vector3 var, bool up = true);
	~FireworkGenerator();

	//metodos
	virtual list<Firework*> generateFireworks(Firework* father);
	virtual void assignVel(Vector3 const& v);
	virtual Vector3 calculateVel();
	virtual Vector3 calculatePos(Vector3 const& p, float r);
	virtual float calculateLT(float ltF, int g);
	virtual int calculateSons(int fSons);
};