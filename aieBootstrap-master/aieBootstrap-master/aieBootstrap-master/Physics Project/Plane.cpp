#include "Plane.h"
#include <Gizmos.h>

Plane::Plane(glm::vec2 a_normal, float a_distance) : PhysicsObject(PLANE)
{
	m_normal = a_normal;
	m_distanceToOrigin = a_distance;
	m_color = glm::vec4(0, 1, 0, 1);

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
