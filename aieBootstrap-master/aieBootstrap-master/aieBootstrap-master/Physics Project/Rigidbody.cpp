#include "Rigidbody.h"

Rigidbody::Rigidbody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass) : PhysicsObject(a_shapeID)
{
	m_position = a_position;
	m_velocity = a_velocity;
	m_mass = a_mass;
	m_rotation = a_rotation;
}

void Rigidbody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	ApplyForce(a_gravity * GetMass() * a_timeStep);
	m_position += GetVelocity() * a_timeStep;
}

void Rigidbody::ApplyForce(glm::vec2 a_force)
{
	m_velocity += a_force / GetMass();
}

void Rigidbody::ApplyForceToOther(Rigidbody* a_otherActor, glm::vec2 a_force)
{
	ApplyForce(-a_force);
	a_otherActor->ApplyForce(a_force);
}

void Rigidbody::ResolveCollision(Rigidbody* a_otherActor)
{
	glm::vec2 normal = glm::normalize(a_otherActor->GetPosition() - GetPosition());
	glm::vec2 relativeVelocity = a_otherActor->GetVelocity() - GetVelocity();

	float elasticity = 1.0f;
	float j = glm::dot(-(1.0f + elasticity) * (relativeVelocity), normal) / ((1.0f / GetMass()) + (1 / a_otherActor->GetMass()));

	glm::vec2 impulse = normal * j;
	ApplyForceToOther(a_otherActor, impulse);
}