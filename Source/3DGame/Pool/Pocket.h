#pragma once
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Object3D.h"
#include "Ball.h"


class Pocket : public Object3D
{
public:
	Pocket(double x, double y, double z, double radius);
	~Pocket();

	double getRadius();
	Mesh* getMesh() override;
	Mesh* createMesh() override;
	void makeVisualMatrix(float radians, float deltaTimeSeconds) override;
	bool Pocket::checkBallInPocket(Ball* ball);
	void Pocket::manageBallInPocket(Ball* ball);

private:
	//Variables	
	double radius;
	Mesh* mesh = nullptr;
	std::unordered_map<std::string, Mesh*> meshes;
};