#pragma once
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Object3D.h"

class Wall : public Object3D
{
public:
	Wall();
	Wall(double x, double y, double z, double length, double width);
	~Wall();

	double getLength();
	double getWidth();
	Mesh* getMesh() override;
	Mesh* createMesh() override;
	void makeVisualMatrix(float radians, float deltaTimeSeconds) override;

private:
	//Variables	
	double length, width;
	Mesh* mesh = nullptr;
};