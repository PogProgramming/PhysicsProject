#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Sphere.h"
#include "Input.h"
#include "Box.h"

#include "PhysicsScene.h"
#include "Game.h"

class Physics_ProjectApp : public aie::Application {
public:

	Physics_ProjectApp();
	virtual ~Physics_ProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::vec2 ScreenToWorld(glm::vec2 a_screenPos);

protected:
	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;

	Game* m_game;
	PhysicsScene* m_physicsScene;

	const float m_aspectRatio = 16.0f / 9.0f;
	const float m_extents = 100;

public:
	void SpringTest(int a_amount);
	void DrawRect();
	void SphereAndPlane();
	void TriggerTest();
};