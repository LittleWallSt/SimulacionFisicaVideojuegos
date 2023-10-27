#include "FireworkGenerator.h"
#include "FireworkGenerator.h"

FireworkGenerator::FireworkGenerator(string n, Vector3 var, bool up) :
	name(n), mean_var(var), uniquePoint(up), rg(rd()) {

}

FireworkGenerator::~FireworkGenerator() {
	delete vX; delete vY; delete vZ;
}

list<Firework*> FireworkGenerator::generateFireworks(Firework* f) {
	
	assignVel(f->getVel());

	//Creamos una lista donde guardar los nuevos fireworks
	list<Firework*> newFs;
	
	//calculamos la nueva vida de los fireworks
	float newLT = calculateLT(f->getLifetime(), f->getGeneration());
	
	//Creamos la cantidad de hijos del firework
	for (int i = 0; i < f->getNumberSons(); i++) {
		int sons = calculateSons(f->getNumberSons());
		if (uniquePoint)
			newFs.push_back(f->clone(f->getPos(), calculateVel(), newLT, sons));
		else
			newFs.push_back(f->clone(calculatePos(f->getPos(), f->getRadious()), calculateVel(), newLT, sons));
	}
	return newFs;
}

//Asignamos velocidades con distribucion uniforme
void FireworkGenerator::assignVel(Vector3 const& v) {
	if (vX != nullptr) {
		delete vX; delete vY; delete vZ;
	}

	vX = new uniform_real_distribution<float>(v.x, v.x + mean_var.x);

	vY = new uniform_real_distribution<float>(0, mean_var.y);

	vZ = new uniform_real_distribution<float>(v.z, v.z + mean_var.z);
}

Vector3 FireworkGenerator::calculateVel() {
	return Vector3((*vX)(rg), (*vY)(rg), (*vZ)(rg));
}

//calculamos las nuevas posiciones con distribucion uniforme
Vector3 FireworkGenerator::calculatePos(Vector3 const& p, float r) {
	uniform_int_distribution<>* posX = new uniform_int_distribution<>(p.x - r, p.x + r);
	
	uniform_int_distribution<>* posY = new uniform_int_distribution<>(p.y - r, p.y + r);
	
	uniform_int_distribution<>* posZ = new uniform_int_distribution<>(p.z - r, p.z + r);

	Vector3 newP = Vector3((*posX)(rg), (*posY)(rg), (*posZ)(rg));
	delete posX; delete posY; delete posZ;
	return newP;
}


//Calculamos la vida de los nuevos hijos creados al explotar los padres fireworks
float FireworkGenerator::calculateLT(float ltF, int g) {
	float lifeperG = (float)ltF / g;
	return lifeperG * (g - 1);
}

//numero de hijos a invocar
int FireworkGenerator::calculateSons(int fSons) {
	if (sons != nullptr) delete sons;
	sons = new uniform_int_distribution<>(fSons - (fSons / 2), fSons + (fSons / 2));
	return (*sons)(rg);
}