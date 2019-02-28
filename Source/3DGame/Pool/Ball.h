#pragma once
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Object3D.h"
#include "Wall.h"

class Ball : public Object3D
{
public:
	Ball(double x, double y, double z, double radius);
	~Ball();

	//Setters & Creators
	void setVelocity(glm::vec3 velocity);
	void setBallColor(int color);
	Mesh* createMesh() override;
	Mesh* getMesh() override;
	void makeVisualMatrix(float radians, float deltaTimeSeconds) override;

	//Checkers
	glm::vec3 getVelocity();
	double getRadius();
	bool isMoving();
	int checkBallColor();
	bool checkBallCollision(Ball* opponent);
	int checkBorderCollision(Ball *ball, Wall *border[]);

	//Manager
	void manageCollision(Ball* opponent);
	void manageBorderCollision(int type) override;
	void Ball::manageBallInPocket();
	void startMoving();
	void moveBall();

private:
	//Movement variables
	bool moving = false;
	float angle;
	float mass = 1;
	glm::vec3 velocity;
	glm::vec3 orientation = glm::vec3(0, 0, 0);
	
	//Particular object variables
	double radius;
	double speed = 10;
	Mesh* mesh = nullptr;
	int ballColor = -1; // White = 2 | Black = 3 | Red = 0 | Yellow = 1
};