#include <Setup.hpp>

#include "GraphicsDemo.hpp"

bool setup(int argc, char *args[]){
	Renderer::window().setSize(1280, 720);
	Renderer::window().setFixedMouse(true);

	AssetLoader::setAssetLocation("data/assets");
	Renderer::shaderManager().setShaderLocation("data/shaders");

	if (!Renderer::initiate())
		return false;

#ifdef _DEBUG
	Renderer::console().setRunning(true);
#endif

	Renderer::shaderManager().createProgram("main", "test_vertex.gls", "test_fragment.gls");
	Renderer::shaderManager().useProgram("main");
	
	EntityManager::stateMachine().addState(new GraphicsDemo);
	EntityManager::stateMachine().changeState<GraphicsDemo>();

	return true;
}