#include "Rigidbody.h"
#include "PhysicsScene.h"

#define MIN_LINEAR_THRESHOLD 0.001f;
#define MIN_ANGULAR_THRESHOLD 0.001f;

Rigidbody::Rigidbody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass) : PhysicsObject(a_shapeID)
{
	m_position = a_position;
	m_velocity = a_velocity;
	m_mass = a_mass;
	m_rotation = a_rotation;
	m_angularVelocity = 0;
	m_isKinematic = false;
	m_elasticity = 0.8f;
	m_linearDrag = 0.3f;
	m_angularDrag = 0.3f;
}

void Rigidbody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	if (m_isKinematic) {
		m_velocity = glm::vec2(0);
		m_angularVelocity = 0.0f;
		return;
	}

	m_velocity -= m_velocity * m_linearDrag * a_timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * a_timeStep;

	if (glm::length(m_velocity) < 0.001f)
	{
		if (glm::length(m_velocity) < glm::length(a_gravity) * m_linearDrag * a_timeStep)
		{
			m_velocity = glm::vec2(0);
		}
	}
	if (abs(m_angularVelocity) < 0.001f)
	{
		m_angularVelocity = 0.0f;
	}

	ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0));
	m_position += GetVelocity() * a_timeStep;

	m_rotation += m_angularVelocity * a_timeStep;
}

void Rigidbody::ApplyForce(glm::vec2 a_force, glm::vec2 a_pos)
{
	m_velocity += a_force / GetMass();

	m_angularVelocity += (a_force.y * a_pos.x - a_force.x * a_pos.y) / GetMoment();
}

void Rigidbody::ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact, glm::vec2* a_collisionNormal, float a_pen)
{
	// Find the vector between their centres, or use the provided
	// direction of force and make sure its normalised

	glm::vec2 normal = glm::normalize(a_collisionNormal ?
		*a_collisionNormal : a_otherActor->GetPosition() - GetPosition());

	// Get the vector perpendicular to the collision normal
	glm::vec2 perpendicularColNorm(normal.y, -normal.x);

	// These are applied to the radius from axis to the application of force
	float radius1 = glm::dot(a_contact - m_position, -perpendicularColNorm);
	float radius2 = glm::dot(a_contact - a_otherActor->GetPosition(),
		perpendicularColNorm);

	// Velocity of the contact point on this object
	float cp_velocity1 = glm::dot(m_velocity, normal) - radius1 * m_angularVelocity;

	// Velocity of contact point of the other object
	float cp_velocity2 = glm::dot(a_otherActor->GetVelocity(), normal) +
		radius2 * a_otherActor->m_angularVelocity;

	if (cp_velocity1 > cp_velocity2) // they are moving closer
	{
		// This will calculate the effective mass at the contact point of each
		// object (How much it will move due to the forces applied)
		float mass1 = 1.f / (1.f / m_mass + (radius1 * radius1) / GetMoment());
		float mass2 = 1.f / (1.f / a_otherActor->m_mass + (radius2 * radius2)
			/ a_otherActor->GetMoment());

		float elasticity = (m_elasticity + a_otherActor->GetElasticity()) / 2.f;

		glm::vec2 impact = (1.f + elasticity) * mass1 * mass2 /
			(mass1 + mass2) * (cp_velocity1 - cp_velocity2) * normal;
		ApplyForce(-impact, a_contact - m_position);
		a_otherActor->ApplyForce(impact, a_contact - a_otherActor->GetPosition());
		if (a_pen > 0)
		{
			PhysicsScene::ApplyContactForces(this, a_otherActor, normal, a_pen);
		}

	}

}

glm::vec2 Rigidbody::ToWorld(glm::vec2 a_localPos)
{

	return m_position + m_localX * a_localPos.x + m_localY * a_localPos.y;
}
