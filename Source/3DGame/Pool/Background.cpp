#include "Background.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Background::Background() {};
Background::Background(double x, double y, double z, double length, double width, double height){
	this->x = x;
	this->y = y;
	this->z = z;
	this->length = length;
	this->width = width;
}
double Background::getLength(){
	return this->length;
}
double Background::getWidth(){
	return this->width;
}

Background::~Background()
{
}

Mesh* Background::getMesh(){
	if (mesh == nullptr) {
		return createMesh();
	}
	else {
		return mesh;
	}
}

Mesh* Background::createMesh() {
	Mesh* mesh = new Mesh("wall");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	return mesh;
}

Mesh * Background::createTop()
{
	Mesh* mesh = new Mesh("top");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane50.obj");
	return mesh;
}

Mesh * Background::getTop()
{
	if (top == nullptr) {
		return createTop();
	}
	else {
		return top;
	}
}

void Background::makeVisualMatrix(float radians, float deltaTimeSeconds) {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(radians), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(width, height, length));
	this->visualMatrix = modelMatrix;
}