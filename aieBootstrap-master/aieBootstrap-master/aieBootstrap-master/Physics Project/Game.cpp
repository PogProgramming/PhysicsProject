#include "Game.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>

#include "Sphere.h"
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
}


void Game::Update(float deltaTime)
{
	m_physicsScene->Update(deltaTime);

	//std::cout << m_physicsScene->m_act<< " : " << m_physicsScene->GetGravity().y << "\n";
}

void Game::Draw()
{
	m_physicsScene->Draw();
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

	borderTop->SetElasticity(1.0f);
	borderBottom->SetElasticity(1.0f);
	borderLeft->SetElasticity(1.0f);
	borderRight->SetElasticity(1.0f);

	m_physicsScene->AddActor(borderTop);
	m_physicsScene->AddActor(borderBottom);
	m_physicsScene->AddActor(borderLeft);
	m_physicsScene->AddActor(borderRight);

	Sphere* ball = new Sphere({ 0, 30 }, { 10, 10 }, 5, 4, { 0, 1, 0, 1 });
	ball->ApplyForce({ 100, 100 }, ball->GetPosition());
	ball->SetElasticity(1.0f);
	ball->SetKinematic(false);
	m_physicsScene->AddActor(ball);
}
