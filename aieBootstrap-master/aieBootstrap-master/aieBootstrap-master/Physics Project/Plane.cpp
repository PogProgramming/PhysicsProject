#include "Plane.h"
#include <Gizmos.h>
#include "Rigidbody.h"
#include "PhysicsScene.h"

Plane::Plane() : PhysicsObject(ShapeType::PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::normalize(glm::vec2(0, 1));
	m_color = glm::vec4(0, 1, 0, 1);
	m_isKinematic = true;
	m_elasticity = 1.0f;
}

Plane::Plane(glm::vec2 a_normal, float a_distance) : PhysicsObject(ShapeType::PLANE)
{
	m_normal = glm::normalize(a_normal);
	m_distanceToOrigin = a_distance;
	m_color = glm::vec4(0, 1, 0, 1);
	m_isKinematic = true;
	m_elasticity = 1.f;
}

Plane::~Plane()
{
}

void Plane::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
}

void Plane::MakeGizmo()
{
	float lineSegmentLength = 300.0f;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colorFade = m_color;
	colorFade.a = 0;
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	aie::Gizmos::add2DTri(start, end, start - GetNormal() * 10.0f, GetColor(), GetColor(), colorFade);
	aie::Gizmos::add2DTri(end, end - GetNormal() * 10.0f, start - GetNormal() * 10.0f, GetColor(), colorFade, colorFade);
}

void Plane::ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact)
{
	// The position at which we'll apply the force, relative to the other objects centre of mass.
	glm::vec2 localContact = a_contact - a_otherActor->GetPosition();

	// The plane never moves, so the relative velocity is just the a_otherActor's velocity at the contact point
	glm::vec2 vRel = a_otherActor->GetVelocity() + a_otherActor->GetAngularVelocity() * glm::vec2(-localContact.y, localContact.x);
	float velocityIntoPlane = glm::dot(vRel, m_normal);

	// This canbe left as perfect elasticity for the moment
	float e = (m_elasticity + a_otherActor->GetElasticity()) / 2.0f;

	// This is the perpendicular distance we apply the force at relative to the
	// centre of mass; Torque = F * r
	float r = glm::dot(localContact, glm::vec2(m_normal.y, -m_normal.x));

	// This will work out the 'effective mass' - a combination of the moment of inertia and mass, it will tell
	// how much the contact point velocity will change the force we apply
	float mass0 = 1.0f / (1.0f / a_otherActor->GetMass() + (r * r) / a_otherActor->GetMoment());

	// The planedoes not move (static) so we only use the other actor's velocity
	float j = -(1 + e) * velocityIntoPlane * mass0;
	glm::vec2 force = m_normal * j;
	a_otherActor->ApplyForce(force, a_contact - a_otherActor->GetPosition());

	float pen = glm::dot(a_contact, m_normal) - m_distanceToOrigin;
	PhysicsScene::ApplyContactForces(a_otherActor, nullptr, m_normal, pen);
}
