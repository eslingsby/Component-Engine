#include "NameBank.hpp"
#include <Static\DebugOutput.hpp>

std::string Identifier::name(){
	return _name;
}

int Identifier::id(){
	return _id;
}

void Identifier::setName(std::string name){
	_name = name;
}

int Module::NameBank::generateId(){
	return -1;
}

void Module::NameBank::deleteId(int id){

}

std::string Module::NameBank::getName(int id){
	return "";
}

void Module::NameBank::getIds(std::string name, IntVector& intVector){

}

void Module::NameBank::bindName(int id, std::string name){

}

void Module::NameBank::unbindName(int id, std::string name){

}