#include "particle.h"

class firework : public particle {
protected:
	virtual void createFirewordSystem();
	//FireworkSystem* sys;
	particle* p;
	int _num;
	int _gen;

public:
};