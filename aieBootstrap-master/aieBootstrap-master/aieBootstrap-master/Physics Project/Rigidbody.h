#pragma once
#include "PhysicsObject.h"

class Rigidbody : public PhysicsObject
{
public:
	//Rigidbody();
	Rigidbody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass);
	~Rigidbody() {};

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void Debug() {};

	void ApplyForce(glm::vec2 a_force, glm::vec2 a_pos);

	void ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact, glm::vec2* a_collisionNormal = nullptr);

	glm::vec2 GetPosition() const { return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }

	void SetVelocity(glm::vec2 a_velocity) { m_velocity = a_velocity; }
	float GetMass() { return m_mass; }
	float GetRotation() { return m_rotation; }

	float GetMoment() { return m_moment; }
	float GetAngularVelocity() { return m_angularVelocity; }

	float SetRotation(float a_rotate) { return m_rotation = a_rotate; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;

	float m_rotation;
	float m_angularVelocity;
	float m_moment;
};

