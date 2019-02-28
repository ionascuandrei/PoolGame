#include "Pocket.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Pocket::~Pocket() {}
Pocket::Pocket(double x, double y, double z, double radius) {
	this->radius = radius;
	this->x = x;
	this->y = y;
	this->z = z;
	this->radius = radius;
	updateColor(0, 0, 0);

}

double Pocket::getRadius() {
	return this->radius;
}

Mesh* Pocket::getMesh() {
	if (mesh == nullptr) {
		return createMesh();
	}
	else {
		return mesh;
	}
}

Mesh* Pocket::createMesh() {
	mesh = new Mesh("sphere");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	return mesh;
}

bool Pocket::checkBallInPocket(Ball* ball) {
	glm::vec3 distance(this->x - ball->getX(), 0, this->z - ball->getZ());
	if (glm::length(distance) < this->radius/2) {
		return true;
	}
	else {
		return false;
	}
}

void Pocket::manageBallInPocket(Ball * ball) {
	ball->setStatus(false);
	ball->setVelocity(glm::vec3(0, 0, 0));
}



void Pocket::makeVisualMatrix(float radians, float deltaTimeSeconds) {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(this->x, this->y, this->z));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(radians), glm::vec3(1, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(radius));
	this->visualMatrix = modelMatrix;
}