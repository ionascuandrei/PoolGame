#pragma once
#include <Component/SimpleScene.h>

class Object3D
{
public:
	Object3D();
	Object3D(double x, double y, double z);
	~Object3D();

	//Position
	void updatePosition(double x, double y, double z);
	double getX();
	double getY();
	double getZ();

	//Status
	bool isActive();
	void setStatus(bool status);

	//Object Properties
	void updateColor(float R, float G, float B);
	glm::vec3 getColor();

	glm::mat4 getVisualMatrix(float deltaTimeSeconds);
	virtual void makeVisualMatrix(float radians, float deltaTimeSeconds);
	virtual Mesh* createMesh();
	virtual Mesh* getMesh();

	//Collision
	virtual void manageBorderCollision(int type);

	
protected:
	//Variables
	double x, y, z;
	float R = 255;
	float G = 0;
	float B = 0;
	bool status = true;
	glm::mat4 visualMatrix;
};