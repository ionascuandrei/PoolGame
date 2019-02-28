#include "Wall.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Wall::Wall() {};
Wall::Wall(double x, double y, double z, double length, double width){
	this->x = x;
	this->y = y;
	this->z = z;
	this->length = length;
	this->width = width;
}
double Wall::getLength(){
	return this->length;
}
double Wall::getWidth(){
	return this->width;
}

Wall::~Wall()
{
}

Mesh* Wall::getMesh(){
	if (mesh == nullptr) {
		return createMesh();
	}
	else {
		return mesh;
	}
}

Mesh* Wall::createMesh() {
	Mesh* mesh = new Mesh("wall");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	return mesh;
}

void Wall::makeVisualMatrix(float radians, float deltaTimeSeconds) {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, width/4, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(radians), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(width, width/2, length));
	this->visualMatrix = modelMatrix;
}