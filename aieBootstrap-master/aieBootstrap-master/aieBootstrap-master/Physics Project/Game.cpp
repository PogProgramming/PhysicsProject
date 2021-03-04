#include "Game.h"
#include "Texture.h"
#include "Font.h"
#include "glm\ext.hpp"

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

	BuildMap();
	UpdateBuildMap();
}

void Game::Update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	if (!m_levelChanged) {
		m_levelChanged = true;

		if (m_activeLevel != m_maxLevel) m_activeLevel++;
		else m_activeLevel = 1;
		UpdateBuildMap();
	}

	if (m_physicsScene->m_actors.size() == 0)
		UpdateBuildMap();

	m_physicsScene->Update(deltaTime);
}

void Game::Draw()
{
	m_physicsScene->Draw();
}

void Game::Reset()
{
	for (auto p_actor : m_physicsScene->m_actors) {
		m_physicsScene->RemoveActor(p_actor, false);
	}
	//m_physicsScene->m_actors.clear();
}

void Game::ReachedGoal()
{
	//m_levelChanged = false;
	//Reset();
	m_strokes = 0;

	m_player->SetPosition(m_playerSpawnPoint);
	m_player->SetVelocity({ 0,0 });
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

	borderTop->SetProtectionFromDelete(true);
	borderBottom->SetProtectionFromDelete(true);
	borderLeft->SetProtectionFromDelete(true);
	borderRight->SetProtectionFromDelete(true);

	m_physicsScene->AddActor(borderTop);
	m_physicsScene->AddActor(borderBottom);
	m_physicsScene->AddActor(borderLeft);
	m_physicsScene->AddActor(borderRight);
}

void Game::UpdateBuildMap()
{
	if (m_physicsScene->m_actors.size() != 0)
		Reset(); // Safety - keep noted

	switch (m_activeLevel) {
	case 1:
		Build_Level1();
		break;
	case 2:
		Build_Level2();
		break;
	}
}

void Game::Build_Level1()
{
	m_playerSpawnPoint = { -85, -45 };

	Box* obstacle1 = new Box({ 0, 0 }, { 0, 0 }, 0, 175, 80, 2, { 0, 0, 1, 1 });
	obstacle1->SetKinematic(true);
	obstacle1->SetElasticity(0.6f);
	m_physicsScene->AddActor(obstacle1);

	Box* obstacle2 = new Box({ -80, 0 }, { 0, 0 }, 0, 0, 2, 20, { 0, 0, 1, 1 });
	obstacle2->SetKinematic(true);
	obstacle2->SetElasticity(0.6f);
	m_physicsScene->AddActor(obstacle2);

	Box* obstacle3 = new Box({ 80, 0 }, { 0, 0 }, 0, 0, 2, 20, { 0, 0, 1, 1 });
	obstacle3->SetKinematic(true);
	obstacle3->SetElasticity(0.6f);
	m_physicsScene->AddActor(obstacle3);

	Box* obstacle4 = new Box({ 0, 0 }, { 0, 0 }, 0, 175, 2, 40, { 0, 0, 1, 1 });
	obstacle4->SetKinematic(true);
	obstacle4->SetElasticity(0.6f);
	m_physicsScene->AddActor(obstacle4);

	Box* sand = new Box({ 70, 41 }, { 0, 0 }, 0, 175, 7, 12, { 1, 0.8f, 0, 1 });
	sand->SetKinematic(true);
	sand->SetTrigger(true);
	sand->SetElasticity(0.6f);
	m_physicsScene->AddActor(sand);

	sand->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl;
	if (other == m_player) {
		dynamic_cast<Rigidbody*>(other)->SetLinearDrag(2.0f);
		dynamic_cast<Rigidbody*>(other)->SetAngularDrag(2.0f);
	}};
	sand->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl;
	if (other == m_player) {
		dynamic_cast<Rigidbody*>(other)->SetLinearDrag(1.0f);
		dynamic_cast<Rigidbody*>(other)->SetAngularDrag(1.0f);
	}};

	Box* sand2 = new Box({ 79.5f, 30 }, { 0, 0 }, 0, 175, 17, 6, { 1, 0.8f, 0, 1 });
	sand2->SetKinematic(true);
	sand2->SetTrigger(true);
	sand2->SetElasticity(0.6f);
	m_physicsScene->AddActor(sand2);

	sand2->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl;
	if (other == m_player) {
		dynamic_cast<Rigidbody*>(other)->SetLinearDrag(2.0f);
		dynamic_cast<Rigidbody*>(other)->SetAngularDrag(2.0f);
	}};
	sand2->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl;
	if (other == m_player) {
		dynamic_cast<Rigidbody*>(other)->SetLinearDrag(1.0f);
		dynamic_cast<Rigidbody*>(other)->SetAngularDrag(1.0f);
	}};

	Box* sand3 = new Box({ 79.5f, -30 }, { 0, 0 }, 0, 175, 17, 10, { 1, 0.8f, 0, 1 });
	sand3->SetKinematic(true);
	sand3->SetTrigger(true);
	sand3->SetElasticity(0.6f);
	m_physicsScene->AddActor(sand3);

	sand3->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl;
	if (other == m_player) {
		dynamic_cast<Rigidbody*>(other)->SetLinearDrag(2.0f);
		dynamic_cast<Rigidbody*>(other)->SetAngularDrag(2.0f);
	}};
	sand3->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl;
	if (other == m_player) {
		dynamic_cast<Rigidbody*>(other)->SetLinearDrag(1.0f);
		dynamic_cast<Rigidbody*>(other)->SetAngularDrag(1.0f);
	}};

	m_player = new Sphere(m_playerSpawnPoint, { 0, 0 }, 2, 2, { 1, 1, 1, 1 });
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
	m_playerSpawnPoint = { -85, -45 };

	Box* obstacle1 = new Box({ 0, 0 }, { 0, 0 }, 0, 0, 60, 2, { 0, 0, 1, 1 });
	obstacle1->SetKinematic(true);
	obstacle1->SetElasticity(0.6f);
	m_physicsScene->AddActor(obstacle1);

	Box* obstacle2 = new Box({ 60, 0 }, { 0, 0 }, 0, 0, 2, 20, { 0, 0, 1, 1 });
	obstacle2->SetKinematic(true);
	obstacle2->SetElasticity(0.6f);
	m_physicsScene->AddActor(obstacle2);

	m_player = new Sphere(m_playerSpawnPoint, { 0, 0 }, 2, 2, { 0, 1, 0, 1 });
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