#include "Physics_ProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>
#include <string>

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Spring.h"

Physics_ProjectApp::Physics_ProjectApp() {
	m_2dRenderer = nullptr;
	m_font = nullptr;
	m_game = nullptr;
	m_physicsScene = nullptr;
}

Physics_ProjectApp::~Physics_ProjectApp() {
}

bool Physics_ProjectApp::startup() {
	aie::Gizmos::create(255U, 255U, 6553500U, 6500535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->SetGravity(glm::vec2(0, 0));

	// Lower the value, the more accuratethe simulation ill be;
	// but it will increase the processing time required. If it
	// is too high it can cause the simulation to stutter and reduce stability.
	m_physicsScene->SetTimeStep(0.01f);

	m_game = new Game(m_physicsScene);

	m_game->Init();

	//SphereAndPlane();
	//DrawRect();
	//SpringTest(10);
	//TriggerTest();

	return true;
}

void Physics_ProjectApp::shutdown() {
	delete m_font;
	delete m_2dRenderer;
	delete m_game;
	delete m_physicsScene;
}

float timer = 0.0f;
float waitTill = 0.5f;
bool velocityStopped = true;
void Physics_ProjectApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_game->Update(deltaTime);
	m_game->Draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_E))
		quit();

	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) timer += deltaTime;
	else waitTill = 0.5f;
	if (timer > waitTill) {
		Sphere* ball0;
		ball0 = new Sphere(glm::vec2(-31, 0), glm::vec2(0, 0), 5.0f, 1, glm::vec4(glm::linearRand(0, 100) / 100.0f, glm::linearRand(0, 100) / 100.0f, glm::linearRand(0, 100) / 100.0f, 1));
		ball0->ApplyForce({ deltaTime * 100000, 0 }, glm::vec2(0));
		m_physicsScene->AddActor(ball0);
		waitTill -= deltaTime * 2;

		if (waitTill < 0) waitTill = 0.0001f;
		timer = 0;
	}

	if (abs(m_game->m_player->GetPosition().x) > 200 || abs(m_game->m_player->GetPosition().y) > 200) { // RESET PLAYER
		m_game->m_player->SetPosition(m_game->GetSpawnPoint());
		m_game->m_player->SetVelocity({ 0, 0 });
	}

	//worldPos.x = (float)a_input->getMouseX();
	//worldPos.y = (float)a_input->getMouseY();

	if (m_game->m_player->GetVelocity().x < 0.5f && m_game->m_player->GetVelocity().y < 0.5f) {

		if (input->isMouseButtonDown(0)){
			int xScreen, yScreen;
			input->getMouseXY(&xScreen, &yScreen);
			m_game->worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));

			aie::Gizmos::add2DCircle(m_game->worldPos, 3, 32, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			aie::Gizmos::add2DLine(m_game->m_player->GetPosition(), m_game->worldPos, glm::vec4(1), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		if (input->wasMouseButtonReleased(0)){
			velocityStopped = false;
			glm::vec2 force((m_game->worldPos - m_game->m_player->GetPosition()));
			force.x *= 4;
			force.y *= 4;

			m_game->m_player->ApplyForce(force, glm::vec2(0));

			m_game->m_strokes++;
		}
	}

}

void Physics_ProjectApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	aie::Gizmos::draw2D(glm::ortho<float>(-m_extents, m_extents, -m_extents / m_aspectRatio, m_extents / m_aspectRatio, -1.0f, 1.0f));

	// draw your stuff here!

	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	// output some text, uses the last used colour
	/*char strokes[32];*/
	//sprintf_s(strokes, 32, "Strokes: %i", m_game->m_strokes);
	std::string strokes = std::to_string(m_game->m_strokes);
	m_2dRenderer->drawText(m_font, strokes.c_str(), 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

glm::vec2 Physics_ProjectApp::ScreenToWorld(glm::vec2 a_screenPos)
{
	glm::vec2 worldPos = a_screenPos;

	// We will move the centre of the screen to (0, 0)
	worldPos.x -= getWindowWidth() / 2;
	worldPos.y -= getWindowHeight() / 2;

	// Scale this according to the extents
	worldPos.x *= 2.0f * m_extents / getWindowWidth();
	worldPos.y *= 2.0f * m_extents / (m_aspectRatio * getWindowHeight());

	return worldPos;
}

void Physics_ProjectApp::SpringTest(int a_amount)
{
	Sphere* prev = nullptr;
	for (int i = 0; i < a_amount; i++) {
		// This will need to spawn the sphere at the bottom of the previous one, to make a pendulum that is effected by gravity
		Sphere* sphere = new Sphere(glm::vec2((i * 3), 100 - i * 5), glm::vec2(0), 10.0f, 2, glm::vec4(1, 1, 0, 1));
		if (i == 0) {
			sphere->SetKinematic(true);
		}
		m_physicsScene->AddActor(sphere);

		if (prev) {
			m_physicsScene->AddActor(new Spring(sphere, prev, 40, 500));
		}
		prev = sphere;
	}

	Box* box = new Box(glm::vec2(0, -20), glm::vec2(0), 0.3f, 20, 8, 2);
	box->SetKinematic(true);
	m_physicsScene->AddActor(box);
}

void Physics_ProjectApp::DrawRect()
{
	m_physicsScene->AddActor(new Sphere(glm::vec2(20, 10), glm::vec2(-10, -17), 1, 3, glm::vec4(1, 0, 0, 1)));
	m_physicsScene->AddActor(new Plane(glm::vec2(-0.65, 0.75), -25));

	Box* box1 = new Box(glm::vec2(-50, 40), glm::vec2(16, -4), 1, 3, 8, 4, glm::vec4(1, 0, 0, 1));
	box1->SetRotation(0.5);

	m_physicsScene->AddActor(box1);
}

void Physics_ProjectApp::SphereAndPlane()
{
	//ball = new Sphere(glm::vec2(-30, 20), glm::vec2(0, 0), 0.1f, 7, glm::vec4(1, 0, 0, 1));
	//ball2 = new Sphere(glm::vec2(40, 25), glm::vec2(0, 0), 0.1f, 7, glm::vec4(1, 0, 0, 1));
	//
	//ball->ApplyForce({ -20, -120 }, glm::vec2(0));
	//ball2->ApplyForce({ -240, 0 }, glm::vec2(0));

	Sphere* ball;
	Sphere* ball2;
	Sphere* ball3;
	Sphere* ball4;
	Sphere* ball5;
	Sphere* ball6;
	//Sphere* ball7;

	ball = new Sphere(glm::vec2(-31, 31), glm::vec2(0, 0), 1.0f, 3, glm::vec4(1, 1, 1, 1));
	ball2 = new Sphere(glm::vec2(32, 29), glm::vec2(0, 0), 1.0f, 3, glm::vec4(1, 1, 0, 1));
	ball3 = new Sphere(glm::vec2(-33, 28), glm::vec2(0, 0), 1.0f, 3, glm::vec4(1, 1, 1, 1));
	ball4 = new Sphere(glm::vec2(34, 27), glm::vec2(0, 0), 1.0f, 3, glm::vec4(0, 0, 0, 1));
	ball5 = new Sphere(glm::vec2(-35, 26), glm::vec2(0, 0), 1.0f, 3, glm::vec4(1, 0, 0, 1));
	ball6 = new Sphere(glm::vec2(36, 25), glm::vec2(0, 0), 1.0f, 3, glm::vec4(1, 0, 1, 1));
	//ball7 = new Sphere(glm::vec2(36, 25), glm::vec2(0, 0), 1.0f, 7, glm::vec4(1, 0, 0, 0));

	ball->ApplyForce({ 10, 0 }, glm::vec2(0));
	ball2->ApplyForce({ -10, 0 }, glm::vec2(0));
	ball3->ApplyForce({ 10, 0 }, glm::vec2(0));
	ball4->ApplyForce({ -10, 0 }, glm::vec2(0));
	ball5->ApplyForce({ 10, 0 }, glm::vec2(0));
	ball6->ApplyForce({ -10, 0 }, glm::vec2(0));
	//ball7->ApplyForce({ -10, 0 }, glm::vec2(0));

	m_physicsScene->AddActor(ball);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(ball3);
	m_physicsScene->AddActor(ball4);
	m_physicsScene->AddActor(ball5);
	m_physicsScene->AddActor(ball6);
	//m_physicsScene->AddActor(ball7);

	Plane* plane = new Plane();
	m_physicsScene->AddActor(plane);

	//for (int i = 0; i < 50; i++) {
	//	Sphere* ball0;
	//	ball0 = new Sphere(glm::vec2(-31, 31), glm::vec2(0, 0), 1.0f, 7, glm::vec4(1, 1, 1, 1));
	//	ball0->ApplyForce({ 10, 0 }, glm::vec2(0));
	//	m_physicsScene->AddActor(ball0);
	//}
}

void Physics_ProjectApp::TriggerTest()
{
	Sphere* ball1 = new Sphere(glm::vec2(-20, 0), glm::vec2(0), 4, 4, glm::vec4(1, 0, 0, 1));
	//Sphere* ball2 = new Sphere(glm::vec2(10, -20), glm::vec2(0), 4, 4, glm::vec4(0, 0.5f, 0.5f, 1));
	//ball2->SetKinematic(true);
	//ball2->SetTrigger(true);

	m_physicsScene->AddActor(ball1);
	//m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(new Plane(glm::vec2(0, 1), -30));
	m_physicsScene->AddActor(new Plane(glm::vec2(1, 0), -50));
	m_physicsScene->AddActor(new Plane(glm::vec2(-1, 0), -50));
	//m_physicsScene->AddActor(new Box(glm::vec2(20, 10), glm::vec2(10, 0), 0.5f, 4, 8, 4));
	//m_physicsScene->AddActor(new Box(glm::vec2(-40, 10), glm::vec2(10, 0), 0.5f, 4, 8, 4));
	//m_physicsScene->AddActor(new Box(glm::vec2(-40, 40), glm::vec2(10, 0), 0.5f, 4, 8, 4));

	//ball2->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl; };
	//ball2->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };
}

// missed a public inheritance thingy
// missed a const in getgravity header
// missed draw in update