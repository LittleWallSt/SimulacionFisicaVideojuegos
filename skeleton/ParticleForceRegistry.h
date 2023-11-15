#pragma once
#include "ForceGenerator.h"
#include "RenderItems/particle.h"
#include <map>
typedef std::pair<ForceGen*, particle*> FRpair;

class ParticleForceReg : public std::multimap<ForceGen*, particle*>
{
public:
	void updateForces(float t) {
		for (auto it = begin(); it != end(); ++it) {
			it->first->updateForce(it->second, t);
			it->first->updateTime(t);
		}
			
	}

	void addReg(ForceGen* fg, particle* p) {
		insert({ fg, p });
	}

	//switch de casos con el fG a añadir
	void addReg(int type, particle* p) {
		ForceGen* fg;
		switch (type) {
		case 0:
			return;
			break;
		case 1:
			fg = new GravForceGen(Vector3(0, -9.8, 0), 100);
			break;
		case 2:
			fg = new WindForceGen(Vector3(  100.0, 1.0, 100.0 ), 0.1, 0.2, Vector3(0.0, 10.0, 0.0), 50, 50, 50);
			break;
		case 3:
			fg = new TornadoForceGen(Vector3(-200, 100, 0), 1, 1, 1);
			break;
		case 4:
			fg = new DragForceGen(200, 0);
			break;
		case 5:
			fg = new GravForceGen(Vector3(0, 40, 0), 100);
			break;
		case 6:
			fg = new ExplosionGen(200, 40000, Vector3(1, 45, 1), 7);
			break;

		default:
			return;
			break;
		}
		insert({ fg, p });
	}

	void deletePartReg(particle* p) {
		for (auto it = begin(); it != end();) {
			if (it->second == p) it = erase(it);
			else ++it;
		}
	}
};