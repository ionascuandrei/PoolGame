#include "Object3D.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Object3D::Object3D() {}
Object3D::~Object3D() {}

	//Position
Object3D::Object3D(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Object3D::updatePosition(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

	//Getters and Setters
double Object3D::getX() {
	return this->x;
}
double Object3D::getY() {
	return this->y;
}
double Object3D::getZ() {
	return this->z;
}
glm::vec3 Object3D::getColor()
{
	return glm::vec3(R, G, B);
}
glm::mat4 Object3D::getVisualMatrix(float deltaTimeSeconds) {
	return this->visualMatrix;
}
bool Object3D::isActive() {
	return status;
}
void Object3D::setStatus(bool status){
	this->status = status;
}
void Object3D::updateColor(float R, float G, float B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

	//Object Properties
Mesh* Object3D::getMesh() {
	return nullptr;
}
Mesh * Object3D::createMesh() {
	return nullptr;
}

void Object3D::makeVisualMatrix(float radians, float deltaTimeSeconds) {
}

void Object3D::manageBorderCollision(int type) {
}
