#include "Ball.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Ball::~Ball() {}
Ball::Ball(double x, double y, double z, double radius){
	this->radius = radius;
	this->x = x;
	this->y = y;
	this->z = z;
}

double Ball::getRadius(){
	return this->radius;
}
int Ball::checkBallColor() {
	return ballColor;
}
glm::vec3 Ball::getVelocity()
{
	return velocity;
}
bool Ball::isMoving()
{
	return moving;
}
Mesh* Ball::getMesh() {
	if (mesh == nullptr) {
		return createMesh();
	}
	else {
		return mesh;
	}
}


void Ball::setVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}
void Ball::startMoving() {
	moving = true;
}
void Ball::setBallColor(int color) {
	ballColor = color;
}


void Ball::moveBall() {
	updatePosition(this->x + this->velocity.x, this->y, this->z + this->velocity.z);
	this->velocity.x *= 0.99f;
	this->velocity.z *= 0.99f;
	if (abs(abs(velocity.x) + abs(velocity.z)) <= 0.001f) {
		setVelocity(glm::vec3(0, 0, 0));
		moving = false;
	}
}
void Ball::manageBallInPocket() {
	this->setStatus(false);
	this->setVelocity(glm::vec3(0, 0, 0));
}
Mesh* Ball::createMesh(){
	mesh = new Mesh("sphere");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	return mesh;
}
void Ball::makeVisualMatrix(float radians, float deltaTimeSeconds) {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(this->x, this->y, this->z));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, radius/2, 0));
	modelMatrix  = glm::rotate(modelMatrix , RADIANS(radians), glm::vec3(1, 0, 0));
	modelMatrix  = glm::scale(modelMatrix , glm::vec3(radius));
	this->visualMatrix = modelMatrix;
	
}

bool Ball::checkBallCollision(Ball* opponent) {
	glm::vec3 distance(this->x - opponent->getX(), 0, this->z - opponent->getZ());
	if (glm::length(distance) < this->radius) {
		return true;
	}
	else {
		return false;
	}
}

void Ball::manageCollision(Ball * opponent) {
	float tmp;
	glm::vec3 normal, v1, v2, v1n, v1t, v2n, v2t;

	normal = glm::vec3 (opponent->getX(), opponent->getY(), opponent->getZ()) - glm::vec3(this->x, this->y, this->z);
	tmp = this->radius / 2 - glm::length(normal) / 2;
	normal = glm::normalize(normal);

	v1 = this->velocity;
	v1n = normal * glm::dot(normal, this->velocity);
	v1t = v1 - v1n;

	normal = normal * -1.0f;
	v2 = opponent->velocity;
	v2n = normal * glm::dot(normal, v2);
	v2t = v2 - v2n;

	this->velocity = v2n + v1t;
	opponent->velocity = v1n + v2t;

	//Set Moving State
	opponent->moving = true;
	this->moving = true;

	this->updatePosition(this->x + normal.x * tmp, this->y + normal.y * tmp, this->z + normal.z * tmp);
	opponent->updatePosition(opponent->x - normal.x * tmp, opponent->y - normal.y * tmp, opponent->z - normal.z * tmp);
}

void Ball::manageBorderCollision(int type) {
	if (type == 1) {
		setVelocity(glm::vec3(-velocity.x, 0, velocity.z));
		this->updatePosition(this->x + this->getRadius() / 10, y, this->z);
	}
	if (type == 2) {
		setVelocity(glm::vec3(-velocity.x, 0, velocity.z));
		this->updatePosition(this->x - this->getRadius() / 10, y, this->z);
	}
	if (type == 3) {
		setVelocity(glm::vec3(velocity.x, 0, -velocity.z));
		this->updatePosition(this->x, this->y, this->z + this->getRadius() / 10);
	}
	if (type == 4) {
		setVelocity(glm::vec3(velocity.x, 0, -velocity.z));
		this->updatePosition(this->x, this->y, this->z - this->getRadius() / 10);
	}
}

int Ball::checkBorderCollision(Ball *ball, Wall *border[]) {
	if (border[0]->getX() + border[0]->getWidth() / 2 >= ball->getX() - ball->getRadius()/2) {
		return 1;
	}
	if (border[1]->getX() - border[1]->getWidth() / 2 <= ball->getX() + ball->getRadius()/2) {
		return 2;
	}

	if (border[2]->getZ() + border[2]->getWidth() / 2 >= ball->getZ() - ball->getRadius()/2) {
		return 3;
	}
	if (border[3]->getZ() - border[3]->getWidth() / 2 <= ball->getZ() + ball->getRadius()/2) {
		return 4;
	}
	return 0;
}
