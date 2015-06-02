#pragma once

#include <stdio.h>
#include <typeinfo>
#include <unordered_map>
#include "Component.hpp"
#include "Identifier.hpp"
#include "Renderer.hpp"

class Entity : public Identifier{
private:
	typedef std::unordered_map<const type_info*, Component*> ComponentMap;
	ComponentMap _components;

public:
	// Destroys all components
	~Entity();

	// Clone entity and contents with new ID
	Entity* clone(int id);

	// Update all components with proper dt
	void update(long dt);

	// Render components passing a renderer object interface
	void render(Renderer* renderer);

	// addComponent(component) - Adds a component using typeid as key
	template <typename T>
	void addComponent(T* component){
		// Add component if not already part of Entity
		if (!_components[&typeid(T)]){
			_components[&typeid(T)] = component;

			// Parent and enable the component
			component->setID(ID());
			component->enable();
		}
		else
			printf("%s!\n", "Component already exists");
	}

	// getComponent<type>() - Returns corresponding component key as appropriate type
	template <typename T>
	T* getComponent(){
		ComponentMap::iterator component = _components.find(&typeid(T));

		// If component exists, cast to T and return
		if (component != _components.end()){
			T* casted = dynamic_cast<T*>(component->second);

			if (!casted)
				printf("%s!\n", "Failed to cast component");

			return casted;
		}

		printf("%s!\n", "Cannot find component");

		return 0;
	}

	// destroyComponent<type>() - Removes and deletes component
	template <typename T>
	void destroyComponent(){
		ComponentMap::iterator component = _components.find(&typeid(T));

		// If component exists, erase and delete
		if (component != _components.end()){
			_components.erase(&typeid(T));
			delete component->second;
		}
		else
			printf("%s!\n", "Cannot find component");
	}
};