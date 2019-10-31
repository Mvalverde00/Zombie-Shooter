#ifndef PHYSICS_COMPONENT_C
#define PHYSICS_COMPONENT_C

class Entity;

class PhysicsComponent {
public:
	virtual ~PhysicsComponent(){};
	virtual void update(Entity& e, Uint32 deltaT) {};
};

#endif