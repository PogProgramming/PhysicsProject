#include "Physics_ProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>
#include "Sphere.h"

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

	Sphere* ball;
	ball = new Sphere(glm::vec2(0, 75), glm::vec2(0, -20), 3.0f, 1, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(ball);

	Sphere* secondBall;
	secondBall = new Sphere(glm::vec2(0, -75), glm::vec2(0, 10), 3.0f, 1, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(secondBall);

	Sphere* thirdBall;
	thirdBall = new Sphere(glm::vec2(100, 100), glm::vec2(-20, -10), 3.0f, 1, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(thirdBall);

	Sphere* fourthBall;
	fourthBall = new Sphere(glm::vec2(-100, -100), glm::vec2(10, 20), 3.0f, 1, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(fourthBall);

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

// missed a public inheritance thingy
// missed a const in getgravity header
// missed draw in update