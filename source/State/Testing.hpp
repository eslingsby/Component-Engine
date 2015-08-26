#pragma once

#include "Static\EntityManager.hpp"

#include "Component\Light.hpp"
#include "Component\Camera.hpp"
#include "Component\Input.hpp"
#include "Component\Model\Model.hpp"
#include "Component\Model\Plane.hpp"
#include "Component\Ship.hpp"

struct Testing : public State{
	void on(){
		// Camera setup
		Entity* camera = EntityManager::createEntity("player");

		camera->getComponent<Transform>()->setPosition(Vector3f(0.f, -10.f, -75.f));
		camera->addComponent(new Input(100.f));
		camera->addComponent(new Camera);
		camera->addComponent(new Light);
		camera->addComponent(new Ship);

		// Sky sphere
		Entity* sky = EntityManager::createEntity("sky");

		sky->getComponent<Transform>()->setScale(Vector3f(250.f, 250.f, 250.f));
		sky->addComponent(new Sphere(250.f, true));
		sky->addComponent(new Model("relaxed_cube.obj", "grid.png"));

		// Checkerboard testing floor
		Entity* floor = EntityManager::createEntity("floor");

		floor->getComponent<Transform>()->setPosition(Vector3f(0.f, -4.f, 0.f));
		floor->getComponent<Transform>()->setScale(Vector3f(250.f, 250.f, 250.f));
		floor->addComponent(new Plane("floor.jpg"));

		// Evil face model
		Entity* face = EntityManager::createEntity("face");

		face->getComponent<Transform>()->setPosition(Vector3f(-10.f, -20.f, 0.f));
		face->getComponent<Transform>()->setRotation(Vector3f(0.f, 180.f, 0.f));
		face->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		face->addComponent(new Model("face.obj", "face.png"));
	}

	void off(){
		// Keep camera + sky
		EntityManager::destroyEntities("floor");
		EntityManager::destroyEntities("face");
		EntityManager::destroyEntities("ship");
	}
};