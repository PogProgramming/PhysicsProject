#include "Game.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>

#include "Plane.h"
#include "Box.h"
#include "Spring.h"

#include <iostream>

Game::Game(PhysicsScene* a_physicsScene)
{
	m_physicsScene = a_physicsScene;
}

Game::~Game()
{
}

void Game::Init()
{
	m_physicsScene->SetGravity({ 0, 0 });
	Build_Level1();
}


void Game::Update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	if (!m_levelChanged) {
		m_levelChanged = true;

		m_activeLevel++;

		switch (m_activeLevel) {
		case 1:
			Build_Level1();
			break;
		case 2:
			Build_Level2();
			break;
		}
	}

	m_physicsScene->Update(deltaTime);
}

void Game::Draw()
{
	m_physicsScene->Draw();
}

void Game::Reset()
{
	m_strokes = 0;
	for (auto p_actor : m_physicsScene->m_actors) {
		delete p_actor;
	}
}

void Game::ReachedGoal()
{
	m_levelChanged = false;
	Reset();
}

void Game::BuildMap()
{
	Box* borderTop = new Box({ 0,55 }, { 0, 0 }, 0, 100, 100, 2, { 0, 0.5f, 0.5f, 1 }); // 200x110? maxY = 55
	Box* borderBottom = new Box({ 0, -55 }, { 0, 0 }, 0, 100, 100, 2, { 0, 0.5f, 0.5f, 1 }); // 200x110? minY = -55
	Box* borderLeft = new Box({ 98.5f, 0 }, { 0, 0 }, 0, 100, 2, 55, { 0, 0.5f, 0.5f, 1 });
	Box* borderRight = new Box({ -98.5f, 0 }, { 0, 0 }, 0, 100, 2, 55, { 0, 0.5f, 0.5f, 1 });

	borderTop->SetKinematic(true);
	borderBottom->SetKinematic(true);
	borderLeft->SetKinematic(true);
	borderRight->SetKinematic(true);

	borderTop->SetElasticity(0.6f);
	borderBottom->SetElasticity(0.6f);
	borderLeft->SetElasticity(0.6f);
	borderRight->SetElasticity(0.6f);

	m_physicsScene->AddActor(borderTop);
	m_physicsScene->AddActor(borderBottom);
	m_physicsScene->AddActor(borderLeft);
	m_physicsScene->AddActor(borderRight);
}

void Game::Build_Level1()
{
	BuildMap();

	Box* obstacle1 = new Box({ 0, 0 }, { 0, 0 }, 0, 175, 80, 2, { 0, 0, 1, 1 });
	obstacle1->SetKinematic(true);
	obstacle1->SetElasticity(0.6f);
	m_physicsScene->AddActor(obstacle1);

	m_player = new Sphere({ -85, -45 }, { 0, 0 }, 2, 2, { 0, 1, 0, 1 });
	m_player->SetElasticity(0.6f);
	m_player->SetKinematic(false);
	m_physicsScene->AddActor(m_player);

	m_endGoal = new Sphere({ 85, 45 }, { 0, 0 }, 2, 3, { 1, 0, 0, 1 });
	m_endGoal->SetElasticity(0.0f);
	m_endGoal->SetKinematic(true);
	m_endGoal->SetTrigger(true);
	m_physicsScene->AddActor(m_endGoal);

	m_endGoal->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl; ReachedGoal(); };
	m_endGoal->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };
}

void Game::Build_Level2()
{
	BuildMap();

	Box* obstacle1 = new Box({ 0, 0 }, { 0, 0 }, 0, 175, 2, 80, { 0, 0, 1, 1 });
	obstacle1->SetKinematic(true);
	obstacle1->SetElasticity(0.6f);
	m_physicsScene->AddActor(obstacle1);

	m_player = new Sphere({ -85, -45 }, { 0, 0 }, 2, 2, { 0, 1, 0, 1 });
	m_player->SetElasticity(0.6f);
	m_player->SetKinematic(false);
	m_physicsScene->AddActor(m_player);

	m_endGoal = new Sphere({ 85, 45 }, { 0, 0 }, 2, 3, { 1, 0, 0, 1 });
	m_endGoal->SetElasticity(0.0f);
	m_endGoal->SetKinematic(true);
	m_endGoal->SetTrigger(true);
	m_physicsScene->AddActor(m_endGoal);

	m_endGoal->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl; ReachedGoal(); };
	m_endGoal->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };

}

