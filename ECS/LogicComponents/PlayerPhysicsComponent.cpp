#include "PhysicsComponent.cpp"

class PlayerPhysicsComponent : public PhysicsComponent {
public:
	virtual void update(Entity& e, Uint32 deltaT){

		e.pos += e.vel * (deltaT/1000.0);
		//std::cout<<e.pos;
		// Prevent walking through walls.
	}
};