#include "Cue.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Cue::Cue() {};
Cue::Cue(double x, double y, double z, double length, double width) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->width = width;
	this->length = length;
}
double Cue::getLength() {
	return this->length;
}
double Cue::getWidth() {
	return this->width;
}

Cue::~Cue() {
}

Mesh* Cue::getMesh() {
	if (mesh == nullptr) {
		return createMesh();
	}
	else {
		return mesh;
	}
}

Mesh* Cue::createMesh() {
	Mesh* mesh = new Mesh("cue");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	return mesh;
}

void Cue::makeVisualMatrix(float radians, float deltaTimeSeconds) {
	glm::mat4 visualMatrix = glm::mat4(1);
	visualMatrix = glm::translate(visualMatrix, glm::vec3(x, y, z));
	visualMatrix = glm::rotate(visualMatrix, radians, glm::vec3(0, 1, 0));
	visualMatrix = glm::rotate(visualMatrix, RADIANS(15), glm::vec3(-1, 0, 0));
	visualMatrix = glm::translate(visualMatrix, glm::vec3(0, (double)width / 2 + 0.05, (double)(this->length / 2 + 0.2)));
	visualMatrix = glm::scale(visualMatrix, glm::vec3(this->width, this->width, this->length));
	this->visualMatrix = visualMatrix;
}