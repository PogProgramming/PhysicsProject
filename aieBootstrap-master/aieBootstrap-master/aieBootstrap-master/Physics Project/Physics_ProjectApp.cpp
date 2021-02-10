#include "Physics_ProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

Physics_ProjectApp::Physics_ProjectApp() {

}

Physics_ProjectApp::~Physics_ProjectApp() {

}

bool Physics_ProjectApp::startup() {
	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

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

	SphereAndPlane();
	DrawRect();

	return true;
}

void Physics_ProjectApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void Physics_ProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();
	
	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_E))
		quit();

	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {
		Sphere* ball0;
		ball0 = new Sphere(glm::vec2(-31, 31), glm::vec2(0, 0), 1.0f, 7, glm::vec4(0, 0, 0, 1));
		ball0->ApplyForce({ 100, 0 }, glm::vec2(0));
		m_physicsScene->AddActor(ball0);
	}
}

void Physics_ProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// draw your stuff here!
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press E to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
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
	Sphere* ball7;


	ball = new Sphere(glm::vec2(-31, 31), glm::vec2(0, 0), 1.0f, 7, glm::vec4(1, 1, 1, 1));
	ball2 = new Sphere(glm::vec2(32, 29), glm::vec2(0, 0), 1.0f, 7, glm::vec4(1, 1, 0, 0));
	ball3 = new Sphere(glm::vec2(-33, 28), glm::vec2(0, 0), 1.0f, 7, glm::vec4(1, 1, 1, 0));
	ball4 = new Sphere(glm::vec2(34, 27), glm::vec2(0, 0), 1.0f, 7, glm::vec4(0, 0, 0, 1));
	ball5 = new Sphere(glm::vec2(-35, 26), glm::vec2(0, 0), 1.0f, 7, glm::vec4(1, 0, 0, 1));
	ball6 = new Sphere(glm::vec2(36, 25), glm::vec2(0, 0), 1.0f, 7, glm::vec4(1, 0, 1, 1));
	ball7 = new Sphere(glm::vec2(36, 25), glm::vec2(0, 0), 1.0f, 7, glm::vec4(1, 0, 0, 0));

	ball->ApplyForce({ 10, 0 }, glm::vec2(0));
	ball2->ApplyForce({ -10, 0 }, glm::vec2(0));
	ball3->ApplyForce({ 10, 0 }, glm::vec2(0));
	ball4->ApplyForce({ -10, 0 }, glm::vec2(0));
	ball5->ApplyForce({ 10, 0 }, glm::vec2(0));
	ball6->ApplyForce({ -10, 0 }, glm::vec2(0));
	ball7->ApplyForce({ -10, 0 }, glm::vec2(0));

	m_physicsScene->AddActor(ball);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(ball3);
	m_physicsScene->AddActor(ball4);
	m_physicsScene->AddActor(ball5);
	m_physicsScene->AddActor(ball6);
	m_physicsScene->AddActor(ball7);

	Plane* plane = new Plane();
	m_physicsScene->AddActor(plane);

	for (int i = 0; i < 50; i++) {
		Sphere* ball0;
		ball0 = new Sphere(glm::vec2(-31, 31), glm::vec2(0, 0), 1.0f, 7, glm::vec4(1, 1, 1, 1));
		ball0->ApplyForce({ 10, 0 }, glm::vec2(0));
		m_physicsScene->AddActor(ball0);
	}
}

// missed a public inheritance thingy
// missed a const in getgravity header
// missed draw in update