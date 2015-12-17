#include "GraphicsDemo.hpp"

#include <Static\Renderer.hpp>

#include <Component\Camera.hpp>
#include <Component\Debug\Grid.hpp>
#include <Component\Debug\Noclip.hpp>
#include <Component\Input.hpp>

#include "Spin.hpp"

void GraphicsDemo::on(){
	Entity* origin = EntityManager::createEntity("main");
	origin->addComponent(new Grid(512, 8, 8, Grid::AxisZ));
	
	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setPosition(glm::vec3(0, -512, -128));
	player->addComponent(new Camera);
	player->getComponent<Camera>()->set2d(false);
	player->getComponent<Camera>()->setFov(90);
	player->getComponent<Camera>()->setDrawDistance(1024 * 8);
	player->addComponent(new Input);
	player->addComponent(new Noclip(64.f, 0.1f));
	
	int size = 1;
	float spread = 256.f;
	
	for (int y = -size; y <= size; y++){
		for (int x = -size; x <= size; x++){
			Entity* model = EntityManager::createEntity("model");
			model->getComponent<Transform>()->setScale(glm::vec3(5, 5, 5));
			model->getComponent<Transform>()->setPosition(glm::vec3(x * spread, y * spread, 0));
			model->addComponent(new Model("bunny.obj", "wood.mtl", "main"));
			model->addComponent(new Spin(0.5f));
		}
	}

	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void GraphicsDemo::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}