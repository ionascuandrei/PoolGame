#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include <math.h>

#include "Object3D.h"
#include "Cue.h"
#include "Ball.h"
#include "Pocket.h"
#include "Wall.h"
#include "Background.h"
#include "Camera.h"

class Pool : public SimpleScene
{
	public:
		Pool();
		~Pool();
		void Init() override;
		Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		//Game Functions
		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, glm::vec3 &color);
		int checkEveryCollision(Ball* ball);

			//Variable
		//Illumination
		glm::vec3 lightPosition = glm::vec3(0, 2, 0);
		glm::vec3 lightDirection = glm::vec3(0, 0, 0);
		unsigned int materialShininess;
		float materialKd;
		float materialKs;
		float cut_off;
		int spotLightOn = 1;

		//Game components
		Ball* whiteBall;
		Ball* balls[15];
		Wall* walls[6];
		Pocket* pockets[6];
		Cue* cue;
		Background* bg;

		//Game State
		bool foul = false;
		bool paused = true;
		bool setPower = false;
		bool gameEnded = false;

		//Camera
		Camera::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		bool perspective = true;
		float fov = 60.0f;
		float width = 5.5f;
		float height = 3.0f;

		//Ball power
		double power = 0;
		double kick = 0;
		bool isRising = true;

		//Foul State
		double whiteBallX = 0;
		double whiteBallZ = 2.20;
		double whiteBallSpeed = 2.0f;
		Ball* firstBallHited = nullptr;
		bool isFirstBallHited = false;
		bool colorsAreSet = false;
		bool hitFoul = false;

		//2 Players
		int playerTurn = 2; // Player 1 = 1  | Player 2 = 2
		int ballsLeft[2];
		int color[3]; // Red = 0 | Yellow = 1
		bool startOfTheGame = true;
		bool announce = true;
		bool noScored = true;
		bool hitedBalls = false;
			
		//Cue variables for VertexShader
		int isCue = 0;
		float cueAngle = 0;
};
