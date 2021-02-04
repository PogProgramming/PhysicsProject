#include "Sphere.h"
#include <Gizmos.h>
#include <iostream>

Sphere::Sphere(glm::vec2 a_position, glm::vec2 a_velocity, float a_mass, float a_radius, glm::vec4 a_color) :
	Rigidbody(SPHERE, a_position, a_velocity, 0, a_mass)
{
	m_radius = a_radius;
	m_mass = a_mass;
	m_color = a_color;
}

void Sphere::MakeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_color);
	std::cout << std::endl << "x: " << m_position.x;
	std::cout << std::endl << "y: " << m_position.y << std::endl;
}

bool Sphere::CheckCollision(PhysicsObject* pOther)
{
	Sphere* pSphere = dynamic_cast<Sphere*>(pOther);

	if (pSphere != nullptr) {
		glm::vec2 pos = GetPosition();
		float dist = glm::distance(pos, pSphere->GetPosition());
		if (GetRadius() + pSphere->GetRadius() > dist)
			return true;
	}
	return false;
}
