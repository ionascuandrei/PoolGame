#include "Pool.h"
#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Pool::Pool(){
}
Pool::~Pool(){
}

void Pool::Init()
{
	//Instances
	whiteBall = new Ball(0, 0, 0, 0.2);
	whiteBall->setBallColor(2);
	whiteBall->updateColor(255, 255, 255);

		//Balls
	//Fifth row
	balls[0] = new Ball(0, 0, -3.4, 0.2);
	balls[0]->setBallColor(1);
	balls[0]->updateColor(255, 255, 0);
	balls[1] = new Ball(-0.4, 0, -3.4, 0.2);
	balls[1]->setBallColor(0);
	balls[1]->updateColor(255, 0, 0);
	balls[2] = new Ball(-0.2, 0, -3.4, 0.2);
	balls[2]->setBallColor(1);
	balls[2]->updateColor(255, 255, 0);
	balls[3] = new Ball(0.2, 0, -3.4, 0.2);
	balls[3]->setBallColor(0);
	balls[3]->updateColor(255, 0, 0);
	balls[4] = new Ball(0.4, 0, -3.4, 0.2);
	balls[4]->setBallColor(0);
	balls[4]->updateColor(255, 0, 0);
	//Forth row
	balls[5] = new Ball(0.1, 0, -3.2, 0.2);
	balls[5]->setBallColor(0);
	balls[5]->updateColor(255, 0, 0);
	balls[6] = new Ball(-0.1, 0, -3.2, 0.2);
	balls[6]->setBallColor(0);
	balls[6]->updateColor(255, 0, 0);
	balls[7] = new Ball(0.3, 0, -3.2, 0.2);
	balls[7]->setBallColor(1);
	balls[7]->updateColor(255, 255, 0);
	balls[8] = new Ball(-0.3, 0, -3.2, 0.2);
	balls[8]->setBallColor(1);
	balls[8]->updateColor(255, 255, 0);
	//Third row
	balls[9] = new Ball(0, 0, -3, 0.2);
	balls[9]->setBallColor(3);
	balls[9]->updateColor(0, 0, 0);
	balls[10] = new Ball(0.2, 0, -3, 0.2);
	balls[10]->setBallColor(1);
	balls[10]->updateColor(255, 255, 0);
	balls[11] = new Ball(-0.2, 0, -3, 0.2);
	balls[11]->setBallColor(0);
	balls[11]->updateColor(255, 0, 0);
	//Second row
	balls[12] = new Ball(0.1, 0, -2.8, 0.2);
	balls[12]->setBallColor(0);
	balls[12]->updateColor(255, 0, 0);
	balls[13] = new Ball(-0.1, 0, -2.8, 0.2);
	balls[13]->setBallColor(1);
	balls[13]->updateColor(255, 255, 0);
	//First row
	balls[14] = new Ball(0, 0, -2.6, 0.2);
	balls[14]->setBallColor(0);
	balls[14]->updateColor(255, 255, 0);

	//Cue
	cue = new Cue(0, 0, 0.2, 1.5, 0.05);
	cue->updateColor(0, 0, 1);

	//Pool Table
	walls[0] = new Wall(-2.40, 0, 0, 9.13, 0.3);
	walls[0]->updateColor(0, 1, 0);
	walls[1] = new Wall(2.40, 0, 0, 9.13, 0.3);
	walls[1]->updateColor(0, 1, 0);
	walls[2] = new Wall(0, 0, -4.41, 4.65, 0.3);
	walls[2]->updateColor(0, 1, 0);
	walls[3] = new Wall(0, 0, 4.41, 4.65, 0.3);
	walls[3]->updateColor(0, 1, 0);

	//Background
	bg = new Background(0, 0, 0, 8.75, 4.65, 0.1);
	bg->updateColor(0.0f, 3.2f, 0.0f);

	//Pockets
	pockets[0] = new Pocket(-2.20, 0, 4.20, 0.3);
	pockets[1] = new Pocket(2.20, 0, 4.20, 0.3);
	pockets[2] = new Pocket(2.20, 0, -4.20, 0.3);
	pockets[3] = new Pocket(-2.20, 0, -4.20, 0.3);
	pockets[4] = new Pocket(2.20, 0, 0, 0.3);
	pockets[5] = new Pocket(-2.20, 0, 0, 0.3);

	//2Player variables
	ballsLeft[0] = 7;
	ballsLeft[1] = 7;

	{
		// Create a shader program for drawing face polygon with the color of the normal
		Shader *shader = new Shader("Shader");
		shader->AddShader("Source/3DGame/Pool/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/3DGame/Pool/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//Light & material properties
	{
		lightPosition = glm::vec3(0, 2, 0);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
		//Illumination
		cut_off = RADIANS(30);
	}

	//Camera
	renderCameraTarget = false;
	camera = new Camera::Camera();
	camera->Set(glm::vec3(whiteBall->getX(), whiteBall->getY() + 1, whiteBall->getZ() + 2),
		glm::vec3(whiteBall->getX(), whiteBall->getY(), whiteBall->getZ()), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

Mesh* Pool::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	//Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	//Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}


void Pool::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


int Pool::checkEveryCollision(Ball * ball)
{
	//Pocket Collision = 1
	for (int i = 0; i < 6; i++) {
		if (pockets[i]->checkBallInPocket(ball)) {
			return 1;
		}
	}
	//Border Collision = 2
	if (ball->checkBorderCollision(ball, walls) != 0) {
		return 2;
	}
	//Ball Collision = 3
	for (int i = 0; i < 15; i++) {
		if (ball != balls[i]) {
			if (ball->checkBallCollision(balls[i])) {
				return 3;
			}
		}
	}
	//No Collision
	return 0;
}

void Pool::Update(float deltaTimeSeconds)
{
	//Player announcer
	if (announce) {
		if (playerTurn == 1) {
			playerTurn = 2;
		}
		else {
			playerTurn = 1;
		}
		printf("=== Jucatorul %d loveste! ===\n", playerTurn);
		announce = false;
	}

	// PROIECTIE
	if (perspective) {
		projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f); //fovy aspect near far
	}
	else {
		projectionMatrix = glm::ortho(-width, width, -height, height, 0.5f, 3.0f); //left right bottom top near far
	}

	//Collisions
	if (!paused) {
		for (int i = 0; i < 15; i++) {
			if (!balls[i]->isActive()) {
				continue;
			}
			else {
				for (int j = i + 1; j < 15; j++) {
					if (i != j) {
						if (balls[j]->isActive()) {
							if (balls[i]->checkBallCollision(balls[j])) {
								balls[i]->manageCollision(balls[j]);
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < 15; i++) {
			if (balls[i]->isActive()) {
				if (whiteBall->checkBallCollision(balls[i])) {
					whiteBall->manageCollision(balls[i]);
					if (!isFirstBallHited) {
						firstBallHited = balls[i];
						isFirstBallHited = true;
						//printf("Am lovit prima bila!\n");
						//printf("Jucator %d | Culoare %d | Bila %d\n", playerTurn, color[playerTurn], balls[i]->checkBallColor());
						if (color[playerTurn] != firstBallHited->checkBallColor() && colorsAreSet) {
							//Wrong ball hited first
							printf("<FAULT> Prima bila lovita nu iti apartine!\n");
							hitFoul = true;

						}
					}
				}
			}
		}

	//PocketCollision
		//WhiteBall in Pocket?
		for (int i = 0; i < 6; i++) {
			if (pockets[i]->checkBallInPocket(whiteBall)) {
				//Foul on white Ball
				printf("<FAULT> Bila ALBA introdusa!\n");
				whiteBall->manageBallInPocket();
				foul = true;
				paused = true;
				whiteBall->setStatus(true);
				whiteBall->updatePosition(whiteBallX, 0, whiteBallZ);
			}
		}
		//OtherBalls in Pocket?
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 15; j++) {
				if (balls[j]->isActive()) {
					if (pockets[i]->checkBallInPocket(balls[j])) {
						balls[j]->manageBallInPocket();
						hitedBalls = true;
						noScored = false;
						if (balls[j]->checkBallColor() == 3) {
							gameEnded = true;
							paused = true;
							foul = true;
							if (ballsLeft[color[playerTurn]] == 0) {
								printf("Bila neagra introdusa!\n");
								printf("Jucatorul %d a castigat!\n", playerTurn);
							}
							else {
								printf("<FAULT> Bila neagra introdusa!\n");
								if (playerTurn == 1) {
									printf("Jucatorul 1 a castigat!\n Jocul s-a terminat!\n");
								}
								else {
									printf("Jucatorul 2 a castigat!\n Jocul s-a terminat!\n");
								}
							}
						}
						else {
							ballsLeft[balls[j]->checkBallColor()]--;
							if (ballsLeft[balls[j]->checkBallColor()] <= 0) {
								if (balls[j]->checkBallColor() == 0) {
									if (color[1] == 0) {
										color[1] = 3;
										printf("Player 1 a ajuns la bila NEAGRA!\n");
									}
									else {
										color[2] = 3;
										printf("Player 2 a ajuns la bila NEAGRA!\n");
									}
								}
								else {
									if (color[1] == 1) {
										color[1] = 3;
										printf("Player 1 a ajuns la bila NEAGRA!\n");
									}
									else {
										color[2] = 3;
										printf("Player 2 a ajuns la bila NEAGRA!\n");
									}

								}
							}

							switch (balls[j]->checkBallColor()) {
							case 0:
								printf("Bila ROSIE introdusa!\n");
								break;
							case 1:
								printf("Bila GALBENA introdusa!\n");
								break;
							}
							printf("Bile ROSII ramase: %d\n", ballsLeft[0]);
							printf("Bile GALBENE ramase: %d\n", ballsLeft[1]);

							switch (startOfTheGame) {
							case true:
								startOfTheGame = false;
								color[playerTurn] = balls[j]->checkBallColor();
								colorsAreSet = true;
								//printf("Jucatorul %d loveste!", playerTurn);
								if (playerTurn == 1) {
									if (balls[j]->checkBallColor() == 0) {
										printf("Jucatorul 1 este cu bilele ROSII\n");
										printf("Jucatorul 2 este cu bilele GALBENE\n");
										color[2] = 1;
										color[1] = 0;
									}
									else {
										printf("Jucatorul 1 este cu bilele GALBENE\n");
										printf("Jucatorul 2 este cu bilele ROSII\n");
										color[2] = 0;
										color[1] = 1;
									}
								}
								else {
									if (balls[j]->checkBallColor() == 0) {
										color[1] = 1;
										color[2] = 0;
										printf("Jucatorul 2 este cu bilele ROSII\n");
										printf("Jucatorul 1 este cu bilele GALBENE\n");
									}
									else {
										color[1] = 0;
										color[2] = 1;
										printf("Jucatorul 2 este cu bilele GALBENE\n");
										printf("Jucatorul 1 este cu bilele ROSII\n");
									}
								}
								break;
							case false:
								break;
							}
						}
					}
				}
			}
		}
	}

	//Move and Render Balls
	for (int i = 0; i < 15; i++) {
		if (balls[i]->isActive()) {
			if (balls[i]->isMoving()) {
				balls[i]->moveBall();
				int type = balls[i]->checkBorderCollision(balls[i], walls);
				if (type != 0) {
					balls[i]->manageBorderCollision(type);
				}
			}
			balls[i]->makeVisualMatrix(0, deltaTimeSeconds);
			RenderSimpleMesh(balls[i]->getMesh(), shaders["Shader"], balls[i]->getVisualMatrix(deltaTimeSeconds), balls[i]->getColor());
		}
	}

	//Move and Render White Ball
	if (!foul) {
		if (whiteBall->isMoving()) {
			whiteBall->moveBall();
			int type = whiteBall->checkBorderCollision(whiteBall, walls);
			if (type != 0) {
				whiteBall->manageBorderCollision(type);
			}
		}
		whiteBall->makeVisualMatrix(0, deltaTimeSeconds);
		RenderSimpleMesh(whiteBall->getMesh(), shaders["Shader"], whiteBall->getVisualMatrix(deltaTimeSeconds), whiteBall->getColor());
	}
	else {
		whiteBall->updatePosition(whiteBallX, 0, whiteBallZ);
		whiteBall->makeVisualMatrix(0, deltaTimeSeconds);
		RenderSimpleMesh(whiteBall->getMesh(), shaders["Shader"], whiteBall->getVisualMatrix(deltaTimeSeconds), whiteBall->getColor());
	}

	//Checking for No movement on the board
	bool noMovement = true;
	for (int i = 0; i < 15; i++) {
		if (balls[i]->isActive()) {
			if (balls[i]->isMoving()) {
				noMovement = false;
			}
		}
	}
	if (whiteBall->isMoving()) {
		noMovement = false;
	}

	if (noMovement && !paused) {
		paused = true;
		if (hitFoul) {
			whiteBall->manageBallInPocket();
			whiteBall->setStatus(true);
			whiteBall->updatePosition(whiteBallX, 0, whiteBallZ);
			foul = true;
		}
		else {
			camera->Set(glm::vec3(whiteBall->getX(), whiteBall->getY() + 1, whiteBall->getZ() + 2),
				glm::vec3(whiteBall->getX(), whiteBall->getY(), whiteBall->getZ()), glm::vec3(0, 1, 0));
			cueAngle = 0;
			perspective = true;

			if (noScored && !hitedBalls) {
				announce = true;
			}
		}

	}

	//Cue Render
	if (noMovement && !hitFoul) {
		cue->updatePosition(whiteBall->getX(), whiteBall->getY(), whiteBall->getZ());
		cue->makeVisualMatrix(cueAngle, deltaTimeSeconds);
		if (setPower) {
			isCue = 1;
			RenderSimpleMesh(cue->getMesh(), shaders["Shader"], cue->getVisualMatrix(deltaTimeSeconds), cue->getColor());
			isCue = 0;
		}
		else {
			RenderSimpleMesh(cue->getMesh(), shaders["Shader"], cue->getVisualMatrix(deltaTimeSeconds), cue->getColor());
		}
	}
	
	//Wall Render
	walls[0]->makeVisualMatrix(0, deltaTimeSeconds);
	walls[1]->makeVisualMatrix(0, deltaTimeSeconds);
	walls[2]->makeVisualMatrix(90, deltaTimeSeconds);
	walls[3]->makeVisualMatrix(90, deltaTimeSeconds);
	for (int i = 0; i < 4; i++) {
		RenderSimpleMesh(walls[i]->getMesh(), shaders["Shader"], walls[i]->getVisualMatrix(deltaTimeSeconds), walls[i]->getColor());
	}
	
	//Background Render
	bg->makeVisualMatrix(0, deltaTimeSeconds);
	RenderSimpleMesh(bg->getMesh(), shaders["Shader"], bg->getVisualMatrix(deltaTimeSeconds), bg->getColor());
	
	//Pocket Render
	for (int i = 0; i < 6; i++) {
		pockets[i]->makeVisualMatrix(0, deltaTimeSeconds);
		RenderSimpleMesh(pockets[i]->getMesh(), shaders["Shader"], pockets[i]->getVisualMatrix(deltaTimeSeconds), pockets[i]->getColor());
		
	}
}

void Pool::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}




void Pool::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	GLint light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(light_position, 1, glm::value_ptr(lightPosition));

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->GetTargetPosition();
	GLint eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(eye_position, 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	GLint material_kd_position = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd_position, materialKd);
	GLint material_ks_position = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks_position, materialKs);
	GLint material_shininess_position = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess_position, materialShininess);
	GLint object_color_position = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(object_color_position, 1, glm::value_ptr(color));

	//CutOFF
	int cutOff_location = glGetUniformLocation(shader->program, "cut_off");
	glUniform1f(cutOff_location, cut_off);

	int isCue_location = glGetUniformLocation(shader->program, "isCue");
	glUniform1i(isCue_location, isCue);

	//Time
	int location = glGetUniformLocation(shader->program, "ElapsedTime");
	//glUniform1f(location, Engine::GetElapsedTime());
	glUniform1f(location, (GLfloat) power);

	//WhiteBallPosition
	int ballLocation = glGetUniformLocation(shader->program, "ballPosition");
	//glUniform1f(location, Engine::GetElapsedTime());
	glUniform3f(ballLocation, (GLfloat) whiteBall->getX(), (GLfloat)whiteBall->getY(), (GLfloat)whiteBall->getZ());

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = this->projectionMatrix;
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Pool::OnInputUpdate(float deltaTime, int mods)
{
	//Set Ball Power
	if (paused) {
		if (!foul && !gameEnded) {
			if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && setPower) {
				//power = 40* (1.0f - (sin(Engine::GetElapsedTime()) + 1.0f) / 2.0f);
				if (isRising) {
					if (power <= 1.0f) {
						power += 0.03f;
					} 
					else {
						isRising = !isRising;
						power -= 0.03f;
					}
					 
				}
				else {
					if (power >= 0) {
						power -= 0.03f;
					}
					else {
						isRising = !isRising;
						power += 0.03f;
					}
				}
				kick = 25* power;	
			}
		}

	}

	if (foul && !gameEnded) {
		if (window->KeyHold(GLFW_KEY_W)) {
			if (whiteBallX + whiteBall->getRadius() < walls[1]->getX() - walls[1]->getWidth()/4) {
				whiteBallX += deltaTime * whiteBallSpeed;
			}
		}
		if (window->KeyHold(GLFW_KEY_S)) {
			if (whiteBallX - whiteBall->getRadius() > walls[0]->getX() + walls[0]->getWidth()/4) {
				whiteBallX -= deltaTime * whiteBallSpeed;
			}
		} 
		if (window->KeyHold(GLFW_KEY_A)) {
			if (whiteBallZ - whiteBall->getRadius() > walls[2]->getZ() + walls[2]->getWidth() / 4) {
				whiteBallZ -= deltaTime * whiteBallSpeed;
			}
		} 
		if (window->KeyHold(GLFW_KEY_D)) {
			if (whiteBallZ + whiteBall->getRadius() < walls[3]->getZ() - walls[3]->getWidth() / 4) {
				whiteBallZ += deltaTime * whiteBallSpeed;
			}
		}  
		if (window->KeyHold(GLFW_KEY_SPACE)) {
			if (checkEveryCollision(whiteBall) == 0) {
				paused = false;
				hitFoul = false;
				foul = false;
				whiteBallX = 0;
				whiteBallZ = 2.20;
			}
			else {
				printf("Locatie interzisa!\n");
			}
		}
	}
	
}

void Pool::OnKeyPress(int key, int mods){
}

void Pool::OnKeyRelease(int key, int mods){
}

void Pool::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	float sensivityOX = 0.001f;
	float sensivityOY = 0.001f;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && perspective)
	{
		camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
		cueAngle += (-deltaX * sensivityOY);
	}

}

void Pool::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && paused && !foul && !gameEnded) {
		power = 0;
		setPower = true;
	}
}

void Pool::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && paused && setPower && !gameEnded) {
		//printf("Am dat drumul la bila\n");
		whiteBall->setVelocity(glm::normalize(camera->forward) * glm::vec3((float) kick / 90.0f) );
		whiteBall->startMoving();
		paused = false;
		setPower = false;
		noScored = true;
		hitedBalls = false;
		isFirstBallHited = false;
		power = 0;

		camera->Set(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
		perspective = false;
	}
}

void Pool::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Pool::OnWindowResize(int width, int height)
{
}



