#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include <list>
#include "Rigidbody.h"
#include <iostream>

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors) {
		delete pActor;
	}
}

void PhysicsScene::AddActor(PhysicsObject* a_actor)
{
	m_actors.push_back(a_actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* a_actor)
{
	auto it = std::find(m_actors.begin(), m_actors.end(), a_actor);
	
	if (it != m_actors.end()) {
		m_actors.erase(it);
	}
}


float borderCheckTimer = 0;
void PhysicsScene::Update(float dt)
{
	static std::list<PhysicsObject*> dirty; // MUST REMOVE
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;
	borderCheckTimer += dt;

	while (accumulatedTime >= m_timeStep) {
		for (auto pActor : m_actors) {
			pActor->FixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		for (auto pActor : m_actors) {
			for (auto pOther : m_actors) {
				if (pActor == pOther)
					continue;

				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
					continue;

				Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);
				if (pRigid->CheckCollision(pOther) == true) {
					pRigid->ApplyForceToOther(dynamic_cast<Rigidbody*>(pOther), pRigid->GetVelocity() * pRigid->GetMass());

					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}

				if (borderCheckTimer > 0.1f) { // THEY BOUNCE
					if (pRigid->CheckBorderCollision() == true) {
						pRigid->SetVelocity(-pRigid->GetVelocity());
					}

					pRigid = dynamic_cast<Rigidbody*>(pOther);
					if (pRigid->CheckBorderCollision() == true) {
						pRigid->SetVelocity(-pRigid->GetVelocity());
					}
					pRigid = dynamic_cast<Rigidbody*>(pActor);

					borderCheckTimer = 0;
				}


			}
		}

		dirty.clear();
	}
}

void PhysicsScene::Draw()
{
	for (auto pActor : m_actors) {
		pActor->MakeGizmo();
	}
}

void PhysicsScene::DebugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
		std::cout << count << " : ";
		pActor->Debug();
		count++;
	}
}
