#pragma once
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include "Object3D.h"

class Background : public Object3D
{
public:
	Background();
	Background(double x, double y, double z, double length, double width, double height);
	~Background();

	double getLength();
	double getWidth();
	Mesh* getMesh() override;
	Mesh* createMesh() override;
	Mesh* createTop();
	Mesh* getTop();
	void makeVisualMatrix(float radians, float deltaTimeSeconds) override;

private:
	//Variables	
	double length, width, height;
	Mesh* mesh = nullptr;
	Mesh* top = nullptr;
};