#pragma once
#include "RigidBody.h"
#include "core.hpp"
#include <list>
#include <string>
#include <random>
#include "UniformParticleGenerator.h"

class RigidBodyGenerator: public UniformParticleGenerator {
protected:
	RigidBody* model
};
