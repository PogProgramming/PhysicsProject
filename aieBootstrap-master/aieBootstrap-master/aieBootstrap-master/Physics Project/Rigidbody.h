#pragma once
#include "PhysicsObject.h"
#include <list>
#include <functional>
#include <iostream>

class Rigidbody : public PhysicsObject
{
public:
	//Rigidbody();
	Rigidbody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass);
	~Rigidbody() {};

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void Debug() {};

	void ApplyForce(glm::vec2 a_force, glm::vec2 a_pos);

	void ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact, glm::vec2* a_collisionNormal = nullptr, float a_pen = 0);

	glm::vec2 GetPosition() const { return m_position; }
	glm::vec2 SetPosition(glm::vec2 a_position) { return m_position = a_position; }

	glm::vec2 GetVelocity() { return m_velocity; }
	void SetVelocity(glm::vec2 a_velocity) { m_velocity = a_velocity; }
	
	float GetRotation() { return m_rotation; }
	float SetRotation(float a_rotate) { return m_rotation = a_rotate; }

 	float GetMass() { return m_isKinematic ? INT_MAX : m_mass; }
	float GetMoment() { return m_isKinematic ? INT_MAX : m_moment; }

	float GetAngularVelocity() { return m_angularVelocity; }
	float GetLinearDraw() { return m_linearDrag; }
	float GetAngularDrag() { return m_angularDrag; }

	glm::vec2 ToWorld(glm::vec2 a_localPos);

	std::function<void(PhysicsObject*)> m_collisionCallback;

	void TriggerEntered(PhysicsObject* a_otherActor);
	std::function<void(PhysicsObject*)> triggerEnter;
	std::function<void(PhysicsObject*)> triggerExit;
	bool IsTrigger() { return m_isTrigger; }
	bool SetTrigger(bool a_state) { return m_isTrigger = a_state; }

protected:
	bool m_isTrigger = false;
	std::list<PhysicsObject*> m_objectInside;
	std::list<PhysicsObject*> m_objectInsideThisFrame;

	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;

	float m_rotation;
	float m_angularVelocity;
	float m_moment;

	float m_linearDrag;
	float m_angularDrag;

	glm::vec2 m_localX;
	glm::vec2 m_localY;
};

