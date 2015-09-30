#include "Velocity.hpp"

Velocity::Velocity(float friction, float tolerance){
	_friction = friction;
	_tolerance = tolerance;
}

void Velocity::load(){
	_transform = getComponent<Transform>();
}

void Velocity::update(double dt){
	_velocity = glm::mix(_velocity, _transform->rotation() * _push, (float)dt);

	_push = glm::vec3(0, 0, 0);

	_velocity *= (1.0 - _friction * (float)dt);

	if (glm::length(_velocity) > _tolerance)
		_transform->translate(_velocity * (float)dt);
}

void Velocity::localPush(const glm::vec3& push){
	_push = push;
}