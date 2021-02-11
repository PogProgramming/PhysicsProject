#pragma once
#include "PhysicsObject.h"

// This is a one-sided object that extends infinitely along both its edge and backwards from its normal direction.

class Rigidbody;
class Plane : public PhysicsObject
{
public:
	Plane();
	Plane(glm::vec2 a_normal, float a_distance);
	~Plane();

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void Draw() {};
	virtual void Debug() {};
	virtual void ResetPosition() {};
	virtual void MakeGizmo();
	virtual bool IsInside(glm::vec2 a_point) { return false; }

	void ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact);

	glm::vec2 GetNormal() { return m_normal; }
	//void SetNormal(glm::vec2 a_normal) { m_normal = a_normal; }
	float GetDistance() { return m_distanceToOrigin; }
	glm::vec4 GetColor() { return m_color; }

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
	glm::vec4 m_color;

};

