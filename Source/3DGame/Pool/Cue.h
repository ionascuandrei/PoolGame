#pragma once
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Object3D.h"
#include <cmath>

class Cue : public Object3D
{
public:
	Cue();
	Cue(double x, double y, double z, double length, double width);
	~Cue();

	double getLength();
	double getWidth();
	Mesh* getMesh() override;
	Mesh* createMesh() override;
	void makeVisualMatrix(float radians, float deltaTimeSeconds) override;

private:
	//Variables	
	double width, length;
	Mesh* mesh = nullptr;
};