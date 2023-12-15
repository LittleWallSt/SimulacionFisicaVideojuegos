#pragma once
#include <map>
#include "RigidBodyForceGen.h"

class RigidBodyForceRegistry:public std::multimap<RigidBodyForceGen*, RigidBody*>
{
public:
	void updateForces(float t) {
		for (auto it = begin(); it != end(); ++it) {
			it->first->updateForce(it->second, t);
			it->first->updateTime(t);
		}

	}

	void addReg(RigidBodyForceGen* fg, RigidBody* p) {
		insert({ fg, p });
	}

	void deleteRBReg(RigidBody* p) {
		for (auto it = begin(); it != end();) {
			if (it->second == p) it = erase(it);
			else ++it;
		}
	}
};

