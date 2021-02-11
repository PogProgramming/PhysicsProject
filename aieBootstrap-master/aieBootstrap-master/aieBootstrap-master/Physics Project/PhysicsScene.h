#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Rigidbody.h"

class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void AddActor(PhysicsObject* a_actor);
	void RemoveActor(PhysicsObject* a_actor);

	// This will call the update of each PhysicsObject and updates
	// internally. This will handle collision detection and resolution.
	void Update(float dt);

	// Called once per frame and handles the rendering of PhysicsObjects
	// Will add to a loop of Gizmo objects to render.
	void Draw();
	void DebugScene();

	void SetGravity(const glm::vec2 a_gravity) { m_gravity = a_gravity; }
	glm::vec2 GetGravity() const { return m_gravity; }

	void SetTimeStep(const float a_timeStep) { m_timeStep = a_timeStep; }
	float GetTimeStep() const { return m_timeStep; }

	void CheckForCollision();
	static void ApplyContactForces(Rigidbody* a_actor1, Rigidbody* a_actor2, glm::vec2 a_collisionNorm, float a_pen);


	static bool Plane2Plane (PhysicsObject*, PhysicsObject*);
	static bool Plane2Sphere (PhysicsObject*, PhysicsObject*);
	static bool Plane2Box(PhysicsObject*, PhysicsObject*);
	
	static bool Sphere2Plane (PhysicsObject*, PhysicsObject*);
	static bool Sphere2Sphere (PhysicsObject*, PhysicsObject*);
	static bool Sphere2Box(PhysicsObject*, PhysicsObject*);

	static bool Box2Plane (PhysicsObject*, PhysicsObject*);
	static bool Box2Sphere (PhysicsObject*, PhysicsObject*);
	static bool Box2Box(PhysicsObject*, PhysicsObject*);


protected:
	glm::vec2 m_gravity;
	float m_timeStep;

	std::vector<PhysicsObject*> m_actors;
	std::vector<PhysicsObject*> m_particles;

};

